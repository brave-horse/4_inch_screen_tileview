/*
 * 历史文件：原先在此定义 jl_gui_init() 调用 lv_demo_music()。
 * 现已迁移到 apps/my_project/music_ui/ui_action.c，
 * 走 GUI Guider 生成的 setup_ui / events_init / custom_init 流程。
 * 本文件仅保留 bt_album_manager 需要的 lv_album_img_show 桩函数。
 */
#include "app_config.h"

#ifdef CONFIG_UI_ENABLE

#include "lvgl.h"

void lv_album_img_show(const uint8_t *jpg_buf, uint32_t jpg_buf_len)
{
    (void)jpg_buf;
    (void)jpg_buf_len;
}

#endif
