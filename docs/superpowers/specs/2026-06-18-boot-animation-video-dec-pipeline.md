# 开机动画移植: wifi_camera 的 video_dec 视频管线

**日期:** 2026-06-18  
**分支:** main (d09fa9c)  
**状态:** 设计已确认,待实施

## 目标

把当前 `fb_draw` 手写显存的开机动画替换成 wifi_camera 的 `video_dec` 硬件管线方案。消除手动摆显存带来的波纹,同时为以后 OTA 换视频铺路。

## 为什么要改

1. **波纹** — 手动 fb_draw 往显存写数据踩了 stride/对齐的坑,多次尝试未消。video_dec 管线让硬件自己管显存,避开这个问题。
2. **OTA 就绪** — 改为从文件系统(UIPACKRES)读 AVI 文件,不像现在编进固件。以后 OTA 更新只需替换 AVI 文件。
3. **换了新视频** — 新开机动画 `demo_ui_res/avi/333_4.avi`,720×720,25fps,160 帧,MJPEG+MP3,4.93MB。AVI 含 MP3 音频轨,**需要同步播放**。

## 整体架构

移植 wifi_camera 的 `avi_player` 完整方案:视频走 `dev_open("video_dec")` 硬解+硬件显示,音频走 `vir_source_player`→jlstream 解码输出,**音视频 PTS 同步**。

```
开机 (app_main, ~0.15s):
  thread_fork("boot_anim") ── 独立任务, 和 LVGL 并行跑

boot_anim_task():
  等 storage + video_dec 设备就绪 (~1s)
  fopen AVI 文件 (UIPACKRES flash 分区里)
  调用 avi_player 主循环 (音视频同步, 逐帧推进)
    ├─ 视频: avi_video_get_frame → video_dec_start → 硬件解码+fb2显示
    └─ 音频: avi_audio_get_frame → vir_source_player → jlstream → DAC
  avi 播完自动退出, 关 fb2 图层 + 设备

时间线:
  0.15s  任务启动, 等 storage
  ~1.0s  文件系统就绪, 开播(视频+音频)
  ~7.4s  播完, fb2 关闭 → 露出 LVGL 主屏(fb0, 早已在 3.2s 就绪)
```

## 加什么 / 删什么

### 新增

| 类型 | 内容 | 说明 |
|---|---|---|
| 库 | `video_dec_server.a` (307KB) | video_dec 设备驱动,提供 `dev_open("video_dec")` |
| 库 | `video_engine.a` (420KB) | video_dec_server 的依赖(视频引擎框架) |
| 库 | `stream_media_server.a` (1.8MB) | jlstream 音频流框架,vir_source_player 依赖 |
| 库 | `media.a` (8MB) | jlstream 符号(jlstream_start/stop 等)所在库 |
| 源文件 | `avi_player.c` | wifi_camera 的音视频同步播放器(循环取帧+同步) |
| 源文件 | `avi_parse.c` | wifi_camera 的 AVI 解析器(avi_player 依赖) |
| 源文件 | `vir_source_player.c` | 音频源播放器,avi_player 内部用 |
| -I | `apps/common/video/net_avi_player` | avi_player.h / avi_parse.h 路径 |
| -I | `audio/interface/includes` | vir_source_player.h 路径 |

### 不移植(明确排除)

| 不移植 | 原因 |
|---|---|
| `net_avi_player.c` / `curl_get_data.c` | 网络 HTTP 流式播放,不需要(我们播本地文件) |
| `pipeline_jpeg_dec.c` | pipeline_core 方案,avi_player 用的是 dev_open,不需要 |
| `play_demo.c` | 演示测试代码,不需要 |

### 删除

| 文件 | 原因 |
|---|---|
| `boot_avi_data.c` | 编进固件的 AVI C 数组(改回读文件) |
| `play_animation.c` | 当前 fb_draw 版(重写) |

## 改动清单

### 1. Makefile (`apps/demo/demo_ui/board/wl83/Makefile`)

库链接区增加:
```
video_dec_server.a
video_engine.a
```

源文件区增加:
```
apps/common/video/video_dec_demo.c
```

头文件路径增加:
```
-I apps/common/video
```

### 2. play_animation.c (重写)

改为薄封装:调用 wifi_camera 的 `avi_player` 主循环,传入 AVI 文件路径,avi_player 内部管理音视频同步。

```
play_animation_start():
  thread_fork 起独立任务

boot_anim_task (thread_fork 独立任务):
  找 UIPACKRES 里的 avi 文件 (mnt/sdfile/.../avi/333_4.avi)
  avi_player_open(文件路径) → 内部创建视频+音频管线
  avi_player_play() → 循环推帧+音频, PTS 同步
  播完回调 → avi_player_close → 关图层
```

### 3. isd_config.ini

UIPACKRES 分区扩到能装下 4.93MB AVI + ~1.3MB UI 图片:

```
UIPACKRES_LEN = 0x680000  (~6.5MB)
UIPACKRES_ADR = (8MB - 6.5MB - 4KB)
```

Flash 8MB 布局(改后):
```
0x000000 ┌──────────────┐
         │ bootloader    │  ~35KB(实际)
0x00.... ├──────────────┤
         │ app code      │  ~1.5MB(当前 ~1.3MB)
0x17F000 ├──────────────┤  ≈1.5MB
         │ UIPACKRES     │  6.5MB
         │ (UI图 + AVI)  │
0x7FF000 ├──────────────┤
         │ 预留 4KB      │
0x800000 └──────────────┘
```

### 4. AVI 文件放置

```
demo_ui_res/avi/333_4.avi  →  packres 打包进 UIPACKRES
```

播放时读文件路径(和现有 UI 图片一样走 packres/sdfile 虚拟文件系统)。

## 需在实施中验证的关键点

1. **链接依赖** — video_dec_server.a / video_engine.a / stream_media_server.a / media.a 可能拉出新的 undefined 符号(之前只试过 video_dec_server+video_engine→缺 jlstream→加 media.a → 缺 config_*/log_tag_*)。这次完整补上。
2. **avi_player 适配** — wifi_camera 的 avi_player 内含网络/HTTP 读取逻辑(net_avi_player),需要剥掉网络层,改成读 flash 本地文件。video_dec 的 private_data 改成 `"fb2"`。
3. **音频初始化** — avi_player 内部依赖 `audio_dec_server` / `audio_player` 等音频设备,需要确认这些 device 在 demo_ui 环境下已注册。
4. **fb 图层** — 直接用 `"fb2"`,不跟 LVGL(fb0)及之前 fb_draw(fb1)抢层,硬件 combine 叠。
5. **启动时机** — 独立任务,不等 LVGL,只等 storage+video_dec 设备就绪。目标 ~1s 后开播(比 LVGL 的 3.2s 快 2 秒以上),播完(约 7.4s)关图层露主屏(LVGL 在 3.2s 已就绪,不冲突)。

## 不做的事情

- OTA 升级机制本身(只保证文件方式可接 OTA)
- 波纹深度调试(如果 video_dec 管线也有波纹,另开任务排查)
- UX 优化(logo 过渡/淡入淡出)

## 验证标准

1. 编译链接通过,无 undefined symbol
2. 开机看到 720×720 视频播放(硬件管线,预期无波纹),**同步听到音频**
3. 播完干净露出 LVGL 主屏
4. 替换 demo_ui_res 里的 avi 文件能换开机动画
