#ifndef LV_USE_GUIBUILDER_SIMULATOR
#include "system/includes.h"
#include "os/os_api.h"
#include "play_animation.h"
#include "avi_parse.h"
#include "fs/fs.h"
#include "asm/jpeg_codec.h"
#include "yuv_to_rgb.h"
#include "video/fb.h"

/* 开机动画: 在LVGL启动【之前】同步播放avi。
 * 关键: LVGL未启动时jpeg硬解不与LVGL的GPU渲染抢硬件(否则卡死);
 *       系统堆此时有~7.7M, 直接malloc; fb_draw_open手动启动LCD推流直显, 不经LVGL。
 * 逐帧: 读chunk→jpeg硬解YUV420→fb取显存→yuv转RGB565直写→推屏。
 * 播完fb_draw_close, 之后LVGL正常接管, 完全不影响主屏滑动fps。 */

#define BOOT_VIDEO_PATH  "mnt/sdfile/EXT_RESERVED/uipackres/ui/1111.avi"
#define HEAD_BUF_SIZE    (64 * 1024)
#define FRAME_BUF_SIZE   (256 * 1024)
#define VIDEO_W          720
#define VIDEO_H          720
#define FRAME_DLY_TICK   5              //tick 帧间隔(~50ms,20fps)

void play_animation_start(void)
{
    FILE *file = fopen(BOOT_VIDEO_PATH, "r");
    if (!file) { printf("[boot_anim] open fail\n"); return; }

    int pix = VIDEO_W * VIDEO_H;
    int apix = ((VIDEO_W + 31) & ~31) * ((VIDEO_H + 31) & ~31);  //32对齐padding防解码越界
    u8 *head_buf  = malloc(HEAD_BUF_SIZE);
    u8 *frame_buf = malloc(FRAME_BUF_SIZE);
    u8 *yuv = malloc(apix + apix / 4 * 2);   //YUV420; LVGL前系统堆充足,普通malloc
    struct avi_parser_result parse;
    void *fb = NULL;
    int frame_idx = 0;

    if (!head_buf || !frame_buf || !yuv) { printf("[boot_anim] malloc fail\n"); goto exit; }

    u32 head_len = fread(head_buf, 1, HEAD_BUF_SIZE, file);
    if (avi_parse_header(head_buf, head_len, &parse)) { printf("[boot_anim] parse fail\n"); goto exit; }
    printf("[boot_anim] %dx%d frames=%d\n", parse.width, parse.height, parse.total_frames);

    jpeg_codec_init();

    /* 手动开fb0图层 → 启动LCD推流引擎(LVGL之前) */
    struct fb_draw_info info = {0};
    info.name        = "fb0";
    info.width       = VIDEO_W;
    info.height      = VIDEO_H;
    info.real_width  = VIDEO_W;
    info.real_height = VIDEO_H;
    info.format      = FB_COLOR_FORMAT_RGB888;
    info.z_order     = 253;
    info.fb_num      = 2;
    info.combine     = 1;
    info.out_id      = 0;
    fb = fb_draw_open(&info);
    if (!fb) { printf("[boot_anim] fb_draw_open fail\n"); goto exit; }

    /* 逐帧: 读MJPEG → 硬解YUV420 → 转RGB565写入fb显存 → 推屏 */
    u32 movi_end = parse.movi_offset + parse.movi_size;
    u32 pos = parse.movi_offset;
    fseek(file, pos, SEEK_SET);
    while (pos + 8 <= movi_end) {
        u8 cid[4]; u32 csz;
        if (fread(cid, 1, 4, file) != 4) break;
        if (fread(&csz, 1, 4, file) != 4) break;   //JL fread 返回字节数
        csz = (csz + 1) & ~1u;
        pos += 8;
        if (csz == 0 || csz > FRAME_BUF_SIZE || pos + csz > movi_end) break;
        fread(frame_buf, 1, csz, file);
        pos += csz;
        if (memcmp(cid, parse.video_chunk_id, 4) != 0) continue;

        u8 *jpeg = frame_buf; u32 jlen = csz;
        if (jpeg[0] != 0xFF || jpeg[1] != 0xD8) { if (jlen > 8) { jpeg += 8; jlen -= 8; } }

        struct jpeg_decode_req req = {0};
        req.input_type  = JPEG_INPUT_TYPE_DATA;
        req.input.data.buf = jpeg;
        req.input.data.len = jlen;
        req.buf_y = yuv;
        req.buf_u = yuv + pix;
        req.buf_v = yuv + pix + pix / 4;
        req.buf_width  = VIDEO_W;
        req.buf_height = VIDEO_H;
        req.out_width  = VIDEO_W;
        req.out_height = VIDEO_H;
        req.output_type = JPEG_DECODE_TYPE_DEFAULT;
        req.bits_mode   = BITS_MODE_UNCACHE;
        if (jpeg_decode_one_image(&req, JPEG_DEV_ID_0)) continue;

        struct fb_map_user map = {0};
        fb_draw_getmap(fb, &map);                //取一块fb显存
        if (map.baddr) {
            yuv420p_quto_rgb24(yuv, map.baddr, VIDEO_W, VIDEO_H);      //直接转到fb显存, RGB888
            fb_draw_putmap(fb, &map);            //推屏显示
        }
        frame_idx++;
        os_time_dly(FRAME_DLY_TICK);
    }

    printf("[boot_anim] played %d frames\n", frame_idx);
    os_time_dly(50);   //末帧停留0.5s

exit:
    if (fb)        fb_draw_close(fb);   //关闭fb, 之后LVGL重新接管fb0
    if (file)      fclose(file);
    if (head_buf)  free(head_buf);
    if (frame_buf) free(frame_buf);
    if (yuv)       free(yuv);
    printf("[boot_anim] done\n");
}
#endif
