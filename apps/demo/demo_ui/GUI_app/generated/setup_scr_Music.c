/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_Music(lv_ui *ui)
{
    //Write codes Music
    ui->Music = lv_obj_create(NULL);
    lv_obj_set_size(ui->Music, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Music, LV_SCROLLBAR_MODE_OFF);

    //Write style for Music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Music, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Music, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_tabview_1
    ui->Music_tabview_1 = lv_tabview_create(ui->Music, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Music_tabview_1, 0, 0);
    lv_obj_set_size(ui->Music_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Music_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Music_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Music_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Music_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Music_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Music_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Music_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Music_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Music_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Music_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Music_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Music_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Music_tabview_1_extra_btnm_main_default
    static lv_style_t style_Music_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Music_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Music_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Music_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Music_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Music_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Music_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Music_tabview_1), &style_Music_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Music_tabview_1_extra_btnm_items_default
    static lv_style_t style_Music_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Music_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Music_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Music_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Music_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Music_tabview_1), &style_Music_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Music_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Music_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Music_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Music_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Music_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Music_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Music_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Music_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Music_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Music_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Music_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Music_tabview_1), &style_Music_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Music_tabview_1_tab_1 = lv_tabview_add_tab(ui->Music_tabview_1,"");
    lv_obj_t * Music_tabview_1_tab_1_label = lv_label_create(ui->Music_tabview_1_tab_1);
    lv_label_set_text(Music_tabview_1_tab_1_label, "");

    //Write codes Music_cont_1
    ui->Music_cont_1 = lv_obj_create(ui->Music);
    lv_obj_set_pos(ui->Music_cont_1, 0, 85);
    lv_obj_set_size(ui->Music_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->Music_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Music_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Music_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Music_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Music_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Music_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_btn_1
    ui->Music_btn_1 = lv_btn_create(ui->Music);
    ui->Music_btn_1_label = lv_label_create(ui->Music_btn_1);
    lv_label_set_text(ui->Music_btn_1_label, "音  乐");
    lv_label_set_long_mode(ui->Music_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Music_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->Music_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Music_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Music_btn_1, 70, 25);
    lv_obj_set_size(ui->Music_btn_1, 102, 32);

    //Write style for Music_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Music_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Music_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Music_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Music_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Music_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Music_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Music_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_prev
    ui->Music_prev = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_prev, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_prev, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\prev.png");
#else
    lv_img_set_src(ui->Music_prev, "S:/sdfile/EXT_RESERVED/uipackres/ui/prev.png");
#endif
    lv_img_set_pivot(ui->Music_prev, 50,50);
    lv_img_set_angle(ui->Music_prev, 0);
    lv_obj_set_pos(ui->Music_prev, 66, 554);
    lv_obj_set_size(ui->Music_prev, 94, 94);

    //Write style for Music_prev, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_prev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_prev, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_prev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_prev, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_next
    ui->Music_next = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_next, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_next, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\next.png");
#else
    lv_img_set_src(ui->Music_next, "S:/sdfile/EXT_RESERVED/uipackres/ui/next.png");
#endif
    lv_img_set_pivot(ui->Music_next, 50,50);
    lv_img_set_angle(ui->Music_next, 0);
    lv_obj_set_pos(ui->Music_next, 557, 553);
    lv_obj_set_size(ui->Music_next, 94, 94);

    //Write style for Music_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_next, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_volume_dec
    ui->Music_volume_dec = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_volume_dec, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_volume_dec, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\volume_dec.png");
#else
    lv_img_set_src(ui->Music_volume_dec, "S:/sdfile/EXT_RESERVED/uipackres/ui/volume_dec.png");
#endif
    lv_img_set_pivot(ui->Music_volume_dec, 50,50);
    lv_img_set_angle(ui->Music_volume_dec, 0);
    lv_obj_set_pos(ui->Music_volume_dec, 582, 316);
    lv_obj_set_size(ui->Music_volume_dec, 94, 94);

    //Write style for Music_volume_dec, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_volume_dec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_volume_dec, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_volume_dec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_volume_dec, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_disc
    ui->Music_disc = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_disc, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_disc, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\disc.png");
#else
    lv_img_set_src(ui->Music_disc, "S:/sdfile/EXT_RESERVED/uipackres/ui/disc.png");
#endif
    lv_img_set_pivot(ui->Music_disc, 122,122);
    lv_img_set_angle(ui->Music_disc, 0);
    lv_obj_set_pos(ui->Music_disc, 227, 247);
    lv_obj_set_size(ui->Music_disc, 245, 245);

    //Write style for Music_disc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_disc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_disc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_disc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_disc, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_volume_add
    ui->Music_volume_add = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_volume_add, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_volume_add, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\volume_add.png");
#else
    lv_img_set_src(ui->Music_volume_add, "S:/sdfile/EXT_RESERVED/uipackres/ui/volume_add.png");
#endif
    lv_img_set_pivot(ui->Music_volume_add, 50,50);
    lv_img_set_angle(ui->Music_volume_add, 0);
    lv_obj_set_pos(ui->Music_volume_add, 578, 123);
    lv_obj_set_size(ui->Music_volume_add, 94, 94);

    //Write style for Music_volume_add, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_volume_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_volume_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_volume_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_volume_add, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_play
    ui->Music_play = lv_imgbtn_create(ui->Music);
    lv_obj_add_flag(ui->Music_play, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->Music_play, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\play.png", NULL);
    lv_imgbtn_set_src(ui->Music_play, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\pause.png", NULL);
#else
    lv_imgbtn_set_src(ui->Music_play, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/play.png", NULL);
    lv_imgbtn_set_src(ui->Music_play, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/pause.png", NULL);
#endif
    ui->Music_play_label = lv_label_create(ui->Music_play);
    lv_label_set_text(ui->Music_play_label, "");
    lv_label_set_long_mode(ui->Music_play_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Music_play_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Music_play, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Music_play, 304, 546);
    lv_obj_set_size(ui->Music_play, 109, 109);

    //Write style for Music_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Music_play, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Music_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Music_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Music_play, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_play, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Music_play, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->Music_play, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Music_play, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Music_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Music_play, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for Music_play, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->Music_play, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Music_play, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Music_play, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->Music_play, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Music_play, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for Music_play, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->Music_play, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->Music_play, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes Music_rack
    ui->Music_rack = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_rack, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Music_rack, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\rack.png");
#else
    lv_img_set_src(ui->Music_rack, "S:/sdfile/EXT_RESERVED/uipackres/ui/rack.png");
#endif
    lv_img_set_pivot(ui->Music_rack, 80,40);
    lv_img_set_angle(ui->Music_rack, 0);
    lv_obj_set_pos(ui->Music_rack, 405, 128);
    lv_obj_set_size(ui->Music_rack, 124, 195);

    //Write style for Music_rack, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_rack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_rack, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_rack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_rack, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_img_1
    ui->Music_img_1 = lv_img_create(ui->Music);
    lv_obj_add_flag(ui->Music_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Music_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Music_img_1, 50,50);
    lv_img_set_angle(ui->Music_img_1, 0);
    lv_obj_set_pos(ui->Music_img_1, 43, 28);
    lv_obj_set_size(ui->Music_img_1, 14, 24);

    //Write style for Music_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Music_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Music_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Music_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Music_btn_2
    ui->Music_btn_2 = lv_btn_create(ui->Music);
    ui->Music_btn_2_label = lv_label_create(ui->Music_btn_2);
    lv_label_set_text(ui->Music_btn_2_label, "");
    lv_label_set_long_mode(ui->Music_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Music_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Music_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Music_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Music_btn_2, -6, -9);
    lv_obj_set_size(ui->Music_btn_2, 229, 107);

    //Write style for Music_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Music_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Music_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Music_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Music_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Music_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Music_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Music_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Music_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Music.


    //Update current screen layout.
    lv_obj_update_layout(ui->Music);

    //Init events for screen.
    events_init_Music(ui);
}
