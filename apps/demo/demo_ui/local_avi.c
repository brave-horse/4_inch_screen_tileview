#include "local_avi.h"
#include "avi_parse.h"
#include "pipeline_jpeg_dec.h"
#include "os/os_api.h"
#include "fs/fs.h"

#define HEAD_BUF_SIZE    (64 * 1024)     //AVI头解析缓冲
#define FRAME_BUF_SIZE   (256 * 1024)    //单帧JPEG缓冲(与旧avi_player版一致)

struct local_avi {
    FILE *file;
    pipe_core_t *pipe;
    struct avi_parser_result parse;
    struct video_format fmt;
    u8  *head_buf;
    u8  *frame_buf;
    int  total_frames;
    int  frame_idx;
};

static struct local_avi *g_avi;

/* 同步播放: 解析AVI头→初始化管线→逐帧推JPEG→清理。不依赖avi_player/lbuf。 */
int local_avi_play(const char *path,
                   void (*on_end)(void *priv),
                   void *priv)
{
    struct local_avi *lavi = calloc(1, sizeof(*lavi));
    if (!lavi) return -1;
    g_avi = lavi;
    (void)on_end;
    (void)priv;

    /* 1. 打开文件 */
    lavi->file = fopen(path, "r");
    if (!lavi->file) {
        printf("[local_avi] open fail: %s\n", path);
        goto err;
    }

    /* 2. 读+解析AVI头部 */
    lavi->head_buf = malloc(HEAD_BUF_SIZE);
    if (!lavi->head_buf) goto err;
    u32 head_len = fread(lavi->head_buf, 1, HEAD_BUF_SIZE, lavi->file);
    if (avi_parse_header(lavi->head_buf, head_len, &lavi->parse)) {
        printf("[local_avi] parse fail\n");
        goto err;
    }
    avi_parser_result_dump(&lavi->parse);

    /* 3. 管线: 输出720x720到fb2, IMC自动缩放256→720 */
    struct video_window win;
    memset(&win, 0, sizeof(win));
    win.width  = 720;
    win.height = 720;

    pipeline_jpeg_dec_format_init(&lavi->fmt, &win,
                                   lavi->parse.width,
                                   lavi->parse.height,
                                   (char *)"fb2");

    if (pipeline_jpeg_dec_init(&lavi->pipe, &lavi->fmt)) {
        printf("[local_avi] pipeline init fail\n");
        goto err;
    }

    lavi->total_frames = lavi->parse.total_frames;
    printf("[local_avi] playing: %dx%d %dfps frames=%d\n",
           lavi->parse.width, lavi->parse.height,
           lavi->parse.fps, lavi->total_frames);

    /* 4. 帧缓冲 */
    lavi->frame_buf = malloc(FRAME_BUF_SIZE);
    if (!lavi->frame_buf) goto err;

    /* 5. 逐帧: 读chunk→推管线→等50ms(20fps) */
    u32 movi_end = lavi->parse.movi_offset + lavi->parse.movi_size;
    u32 pos = lavi->parse.movi_offset;
    int tick = 5;   //50ms

    fseek(lavi->file, pos, SEEK_SET);
    while (pos + 8 <= movi_end) {
        u8  cid[4];
        u32 csz;
        /* JL fs 的 fread 返回字节数(非item数), 一律按字节判 */
        if (fread(cid, 1, 4, lavi->file) != 4) { printf("[local_avi] read cid fail\n"); break; }
        if (fread(&csz, 1, 4, lavi->file) != 4) { printf("[local_avi] read csz fail\n"); break; }
        csz = (csz + 1) & ~1u;
        pos += 8;
        if (csz == 0 || csz > FRAME_BUF_SIZE || pos + csz > movi_end) {
            printf("[local_avi] break: cid=%c%c%c%c csz=%u movi_end=%u pos=%u\n",
                   cid[0], cid[1], cid[2], cid[3], csz, movi_end, pos);
            break;
        }

        fread(lavi->frame_buf, 1, csz, lavi->file);
        pos += csz;

        /* 视频帧: 跳过8字节AVI包装头(如果有) */
        if (memcmp(cid, lavi->parse.video_chunk_id, 4) == 0) {
            u8  *jpeg = lavi->frame_buf;
            u32  jlen = csz;
            if (jpeg[0] != 0xFF || jpeg[1] != 0xD8) {
                if (jlen > 8) { jpeg += 8; jlen -= 8; }
            }
            pipeline_jpeg_dec_one_frame(lavi->pipe, jpeg, jlen);
            lavi->frame_idx++;
            os_time_dly(tick);
        }
    }

    /* 6. 排空管线→清理 */
    os_time_dly(10);    //100ms drain
    pipeline_jpeg_dec_exit(&lavi->pipe);
    printf("[local_avi] done: %d/%d frames\n", lavi->frame_idx, lavi->total_frames);

    free(lavi->frame_buf);
    free(lavi->head_buf);
    fclose(lavi->file);
    free(lavi);
    g_avi = NULL;
    return 0;

err:
    if (lavi) {
        if (lavi->frame_buf) free(lavi->frame_buf);
        if (lavi->head_buf) free(lavi->head_buf);
        if (lavi->file)     fclose(lavi->file);
        if (lavi->pipe)     pipeline_jpeg_dec_exit(&lavi->pipe);
        free(lavi);
    }
    g_avi = NULL;
    return -1;
}

void local_avi_stop(void)
{
    if (!g_avi) return;
    if (g_avi->pipe)     pipeline_jpeg_dec_exit(&g_avi->pipe);
    if (g_avi->frame_buf) free(g_avi->frame_buf);
    if (g_avi->head_buf) free(g_avi->head_buf);
    if (g_avi->file)     fclose(g_avi->file);
    free(g_avi);
    g_avi = NULL;
    printf("[local_avi] stopped\n");
}
