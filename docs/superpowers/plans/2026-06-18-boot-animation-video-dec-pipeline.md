# 开机动画移植 video_dec 管线 — 实施计划

> **给执行者:** 使用 superpowers:subagent-driven-development 或 superpowers:executing-plans 按任务逐步执行。步骤用 `- [ ]` checkbox 追踪。

**目标:** 把开机动画从 fb_draw 手写显存改成 wifi_camera 的 video_dec 硬件管线 (avi_player 音视频同步)

**架构:** 移植 wifi_camera 的 avi_player (视频走 dev_open("video_dec")+fb2,音频走 vir_source_player+jlstream),替换 curl 网络读取为 fopen 本地文件读取。独立任务 ~1s 后开播

**涉及技术栈:** video_dec_server.a / video_engine.a / stream_media_server.a / media.a / avi_parse.c / avi_player.c / pipeline_jpeg_dec.c / vir_source_player.c

## 全局约束

- demo_ui 工程,不能动 wifi_camera 和 SDK 公共代码
- 必须播 AVI 里的 MP3 音频(同步)
- fb2 图层,不跟 LVGL(fb0)抢
- ~1s 后开播,不等 LVGL
- 编译通过,无 undefined symbol

---

### 前置: avi_player 的接口说明(给执行者)

avi_player 内部已经管理了音视频同步。我们需要做的是:

1. **读 AVI 文件,解析头** → 用 avi_parse.c 的 `avi_parse_header(buf, size, result)`
2. **创建帧队列,启动 avi_player** → `avi_player_init(info, frame_queue, callback, priv)`
3. **后台任务读 AVI 数据,往队列塞帧** → avi_player 内部从队列消费帧,自动播
4. **播完回调** → `AVI_PLAYER_EVENT_END` → 清理

avi_player 依赖的组件:
- **视频:** pipeline_jpeg_dec.c (内部用 video_dec_start 推 fb2)
- **音频:** vir_source_player.c → jlstream (在 stream_media_server.a / media.a 里)
- **AVI 解析:** avi_parse.c (纯 buffer 解析,不依赖网络)

---

### Task 1: 删除不需要的文件

**文件:**
- 删除: `apps/demo/demo_ui/boot_avi_data.c`

- [ ] 删掉编进固件的 AVI 数组文件

```bash
rm apps/demo/demo_ui/boot_avi_data.c
```

---

### Task 2: Makefile 改动(库、源、头文件路径)

**文件:**
- 修改: `apps/demo/demo_ui/board/wl83/Makefile`

- [ ] 在库链接区 (`--start-group` 到 `--end-group` 之间,`video.a` 后面) 增加:

```makefile
	../../../../../cpu/wl83/liba/video_dec_server.a \
	../../../../../cpu/wl83/liba/video_engine.a \
	../../../../../cpu/wl83/liba/stream_media_server.a \
	../../../../../cpu/wl83/liba/media.a \
```

- [ ] 在源文件区 (DEMO_UI_AUTO_SRCS 后面) 增加 wifi_camera 移植文件:

```makefile
	../../../../../apps/common/video/net_avi_player/avi_parse.c \
	../../../../../apps/common/video/net_avi_player/avi_player.c \
	../../../../../apps/common/video/net_avi_player/pipeline_jpeg_dec.c \
	../../../../../audio/interface/player/vir_source_player.c \
```

- [ ] 在 include 路径区 (`-I` 列表末尾) 增加:

```makefile
	-I../../../../../apps/common/video/net_avi_player \
	-I../../../../../audio/interface \
	-I../../../../../audio/interface/includes \
	-I../../../../../include_lib/media/framework/include \
```

注意:已有的 `-I../../../../../apps/common/video` 保留。play_animation.c 和 local_avi.c 在 demo_ui 根,被 wildcard 自动收集,不用手动加。

---

### Task 3: 写 local_avi.c (本地文件版 AVI 播放器,替换 net_avi_player.c)

**文件:**
- 创建: `apps/demo/demo_ui/local_avi.c`
- 创建: `apps/demo/demo_ui/include/local_avi.h`

#### local_avi.h

```c
#ifndef LOCAL_AVI_H
#define LOCAL_AVI_H

#include "system/includes.h"

/* 播放本地 AVI 文件(音视频同步)。播完回调 on_end,之后自动清理 */
int local_avi_play(const char *path,
                   void (*on_end)(void *priv),
                   void *priv);

/* 停止并清理 */
void local_avi_stop(void);

#endif
```

#### local_avi.c

```c
#include "local_avi.h"
#include "avi_parse.h"
#include "avi_player.h"
#include "os/os_api.h"
#include "fs/fs.h"

#define HEAD_BUF_SIZE  (64 * 1024)      //AVI头解析缓冲
#define DATA_BUF_SIZE  (256 * 1024)     //单次读AVI数据缓冲
#define AUDIO_QUEUE_SIZE (256 * 1024)   //音频帧队列
#define VIDEO_QUEUE_SIZE (512 * 1024)   //视频帧队列

struct local_avi {
    FILE *file;
    struct avi_player *player;
    struct avi_frame_queue frame_queue;
    struct avi_parser_result parse_result;
    struct avi_info avi_info;
    u8  *head_buf;
    u8  *data_buf;
    int  data_task_pid;
    int  data_task_exit;
    void (*on_end)(void *priv);
    void *on_end_priv;
};

static struct local_avi *g_avi;   //单例

/* avi_player 回调: 播完通知 */
static void avi_event_cb(int event, int arg, void *priv)
{
    struct local_avi *lavi = (struct local_avi *)priv;
    if (event == AVI_PLAYER_EVENT_END) {
        if (lavi->on_end) {
            lavi->on_end(lavi->on_end_priv);
        }
    }
}

/* 后台任务: 从本地文件读AVI数据, 拆音视频帧塞进队列 */
static void avi_read_task(void *priv)
{
    struct local_avi *lavi = (struct local_avi *)priv;
    u8  chunk_id[4];
    u32 chunk_size;
    u32 movi_end = lavi->parse_result.movi_offset + lavi->parse_result.movi_size;
    u32 pos = lavi->parse_result.movi_offset;

    fseek(lavi->file, pos, SEEK_SET);
    while (!lavi->data_task_exit && pos < movi_end) {
        if (fread(chunk_id, 1, 4, lavi->file) != 4) break;
        if (fread(&chunk_size, 4, 1, lavi->file) != 1) break;
        chunk_size = (chunk_size + 1) & ~1u;   //AVI chunk 对齐偶数
        pos += 8;
        if (chunk_size > DATA_BUF_SIZE || pos + chunk_size > movi_end) break;

        fread(lavi->data_buf, 1, chunk_size, lavi->file);
        pos += chunk_size;

        /* 分发到视频/音频队列 */
        if (memcmp(chunk_id, lavi->parse_result.video_chunk_id, 4) == 0) {
            /* 视频帧: 检查JPEG头, 跳过非JPEG数据 */
            u8 *jpeg_ptr = lavi->data_buf;
            u32 jpeg_len = chunk_size;
            if (jpeg_ptr[0] != 0xFF || jpeg_ptr[1] != 0xD8) {
                jpeg_ptr += 8; jpeg_len -= 8;   //跳过AVI包装头
            }
            if (lavi->frame_queue.video_lbuf_handle) {
                void *node = lbuf_alloc(lavi->frame_queue.video_lbuf_handle, jpeg_len);
                if (node) {
                    memcpy(node, jpeg_ptr, jpeg_len);
                    lbuf_push(node);
                }
            }
        } else if (memcmp(chunk_id, lavi->parse_result.audio_chunk_id, 4) == 0) {
            /* 音频帧 */
            if (lavi->frame_queue.audio_lbuf_handle) {
                void *node = lbuf_alloc(lavi->frame_queue.audio_lbuf_handle, chunk_size);
                if (node) {
                    memcpy(node, lavi->data_buf, chunk_size);
                    lbuf_push(node);
                }
            }
        }
        /* 其他chunk类型(如idx1)跳过 */
    }
    /* 读完后不再塞帧, avi_player 消费完队列后自行回调 on_end */
}

/* 初始化帧队列(lbuf) */
static int frame_queue_init(struct local_avi *lavi)
{
    lavi->frame_queue.video_lbuf_handle = lbuf_create("avi_v", lavi->frame_queue.video_buf_size, 1);
    lavi->frame_queue.audio_lbuf_handle = lbuf_create("avi_a", lavi->frame_queue.audio_buf_size, 1);
    if (!lavi->frame_queue.video_lbuf_handle && !lavi->frame_queue.audio_lbuf_handle) {
        return -1;
    }
    return 0;
}

int local_avi_play(const char *path,
                   void (*on_end)(void *priv),
                   void *priv)
{
    struct local_avi *lavi = calloc(1, sizeof(struct local_avi));
    if (!lavi) return -1;
    g_avi = lavi;
    lavi->on_end = on_end;
    lavi->on_end_priv = priv;

    lavi->file = fopen(path, "r");
    if (!lavi->file) { printf("[local_avi] open fail: %s\n", path); goto err; }

    /* 读头, avi_parse 解析 */
    lavi->head_buf = malloc(HEAD_BUF_SIZE);
    if (!lavi->head_buf) goto err;
    u32 head_len = fread(lavi->head_buf, 1, HEAD_BUF_SIZE, lavi->file);
    if (avi_parse_header(lavi->head_buf, head_len, &lavi->parse_result)) {
        printf("[local_avi] parse header fail\n"); goto err;
    }
    avi_parser_result_dump(&lavi->parse_result);

    /* 填 avi_info */
    lavi->avi_info.width    = lavi->parse_result.width;
    lavi->avi_info.height   = lavi->parse_result.height;
    lavi->avi_info.fps      = lavi->parse_result.fps;
    lavi->avi_info.has_video = lavi->parse_result.has_video;
    lavi->avi_info.has_audio = lavi->parse_result.has_audio;
    lavi->avi_info.audio_coding_type = lavi->parse_result.audio_coding_type;
    lavi->avi_info.audio_channels = lavi->parse_result.audio_channels;
    lavi->avi_info.audio_sample_rate = lavi->parse_result.audio_sample_rate;
    lavi->avi_info.total_time_ms = (lavi->parse_result.total_frames * 1000) / lavi->avi_info.fps;
    lavi->avi_info.video_coding_type = lavi->parse_result.video_coding_type;

    /* 帧队列 */
    lavi->frame_queue.video_buf_size = VIDEO_QUEUE_SIZE;
    lavi->frame_queue.audio_buf_size = AUDIO_QUEUE_SIZE;
    if (frame_queue_init(lavi)) { printf("[local_avi] q init fail\n"); goto err; }

    /* avi_player */
    lavi->player = avi_player_init(&lavi->avi_info, &lavi->frame_queue,
                                   avi_event_cb, lavi);
    if (!lavi->player) { printf("[local_avi] player init fail\n"); goto err; }

    /* 后台读文件任务 */
    lavi->data_buf = malloc(DATA_BUF_SIZE);
    if (!lavi->data_buf) goto err;
    lavi->data_task_exit = 0;
    thread_fork("avi_read", 5, 1024 * 4, 0, &lavi->data_task_pid, avi_read_task, lavi);

    avi_player_control(lavi->player, AVI_PLAYER_CMD_PLAY, 0);
    printf("[local_avi] playing: %s %dx%d %dfps\n", path,
           lavi->avi_info.width, lavi->avi_info.height, lavi->avi_info.fps);
    return 0;

err:
    if (lavi) {
        if (lavi->head_buf) free(lavi->head_buf);
        if (lavi->file) fclose(lavi->file);
        free(lavi);
    }
    g_avi = NULL;
    return -1;
}

void local_avi_stop(void)
{
    if (!g_avi) return;
    g_avi->data_task_exit = 1;
    if (g_avi->player) avi_player_exit(g_avi->player);
    if (g_avi->data_buf) free(g_avi->data_buf);
    if (g_avi->head_buf) free(g_avi->head_buf);
    if (g_avi->file) fclose(g_avi->file);
    /* lbuf 清理: avi_player_exit 内部已清 */
    free(g_avi);
    g_avi = NULL;
    printf("[local_avi] stopped\n");
}
```

---

### Task 4: 重写 play_animation.c (薄封装 local_avi)

**文件:**
- 修改: `apps/demo/demo_ui/play_animation.c`

全部替换为:

```c
#ifndef LV_USE_GUIBUILDER_SIMULATOR
#include "system/includes.h"
#include "os/os_api.h"
#include "play_animation.h"
#include "local_avi.h"

#define BOOT_VIDEO_PATH  "mnt/sdfile/EXT_RESERVED/uipackres/ui/333_4.avi"

static void on_anim_end(void *priv)
{
    (void)priv;
    printf("[boot_anim] play done\n");
    /* fb2 图层由 avi_player 内部关闭,不需要额外操作 */
}

static void boot_anim_task(void *arg)
{
    (void)arg;

    /* 等文件系统挂载(uipackres) */
    FILE *probe = NULL;
    do {
        probe = fopen(BOOT_VIDEO_PATH, "r");
        if (probe) { fclose(probe); break; }
        os_time_dly(30);   //300ms
    } while (1);

    printf("[boot_anim] file ready, starting\n");
    local_avi_play(BOOT_VIDEO_PATH, on_anim_end, NULL);
    /* local_avi_play 返回后已经在播, 异步。播完回调 on_anim_end */
}

void play_animation_start(void)
{
    thread_fork("boot_anim", 10, 1024 * 4, 0, NULL, boot_anim_task, NULL);
}
#endif
```

---

### Task 5: 复制并修改 pipeline_jpeg_dec.c(fb1→fb2)

**文件:**
- 复制: `apps/common/video/net_avi_player/pipeline_jpeg_dec.c` → `apps/demo/demo_ui/pipeline_jpeg_dec.c`
- 修改: `apps/demo/demo_ui/pipeline_jpeg_dec.c` (private_data 改成 "fb2")
- 修改: Makefile 源文件列表(`pipeline_jpeg_dec.c` 路径改为 demo_ui 下的副本)

- [ ] 复制文件
- [ ] 找到 `f.private_data = (void *)"fb1"`,改成 `(void *)"fb2"`
- [ ] Makefile 里 pipeline_jpeg_dec.c 的路径改为 `../../../../../apps/demo/demo_ui/pipeline_jpeg_dec.c`(不引用 SDK 公共文件,避免改公共代码)

---

### Task 6: 扩展 UIPACKRES 分区

**文件:**
- 修改: `cpu/wl83/tools/isd_config.ini`

```ini
UIPACKRES_LEN=0x680000;
UIPACKRES_ADR=(((8 * 1024 * 1024)) - (0x680000) - 0x1000);
```

- [ ] 改 UIPACKRES_LEN: `0x200000` → `0x680000` (~6.5MB)
- [ ] 改 UIPACKRES_ADR:对应前移

确认 LOGOPACKRES 分区不冲突:当前 LOGOPACKRES_ADR = UIPACKRES_ADR - LOGOPACKRES_LEN,随着 UIPACKRES_ADR 前移,需要同步更新 LOGOPACKRES_ADR。

LOGOPACKRES_ADR 改为: `(((8*1024*1024)) - (0x680000) - 0x1000 - 0 - 0x70000)`

---

### Task 7: app_main.c 确认

**文件:**
- 不需要改(已确认)

`play_animation_start()` 已经在 `app_main()` 开头调用,独立任务起法不变。

---

### Task 8: 编译 + 解决 undefined symbol

- [ ] 编译:

```powershell
$env:Path = "C:\JL\pi32\bin;E:\...\sdk\tools\utils;" + $env:Path
cd apps/demo/demo_ui/board/wl83
make -f Makefile SHELL=cmd.exe
```

- [ ] 如果报 undefined,按以下优先级补:

| 报缺失的符号模式 | 补什么 |
|---|---|
| `jlstream_*` | media.a 已在链,检查链接顺序 |
| `vir_source_player_*` | vir_source_player.c 已在编 |
| `lbuf_*` | media.a (jlstream 的 buffer 管理) |
| `audio_dec_*` / `audio_player_*` | 补 audio 相关库(需查 wifi_camera 链的) |
| `config_*` / `log_tag_const_*` | 在 app_config.h 里 define 对应宏(按 wifi_camera 的值) |

- [ ] 处理 _WEAK_ 覆盖:如果某些符号由多个库提供(如 `_WEAK_ jl_gui_init`),确保不冲突。

---

### Task 9: 打包 + 烧录验证

- [ ] 重跑 packres(确保 demo_ui_res/avi/333_4.avi 被打进 UIPACKRES)
- [ ] 编译生成完整烧录包
- [ ] 烧录,看开机: ~1s 后 720×720 视频+音频开播 → 播完露出主屏
- [ ] 串口关注:
  - `[local_avi] playing: ...` — 正常启动
  - `[local_avi] open fail` — 路径/打包问题
  - `[local_avi] player init fail` — avi_player 初始化失败(音频/视频设备未就绪)
  - `[boot_anim] play done` — 播放完成
