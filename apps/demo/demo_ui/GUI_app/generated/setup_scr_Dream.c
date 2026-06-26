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



void setup_scr_Dream(lv_ui *ui)
{
    //Write codes Dream
    ui->Dream = lv_obj_create(NULL);
    lv_obj_set_size(ui->Dream, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Dream, LV_SCROLLBAR_MODE_OFF);

    //Write style for Dream, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_tabview_1
    ui->Dream_tabview_1 = lv_tabview_create(ui->Dream, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Dream_tabview_1, 0, 0);
    lv_obj_set_size(ui->Dream_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Dream_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Dream_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Dream_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Dream_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Dream_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Dream_tabview_1_extra_btnm_main_default
    static lv_style_t style_Dream_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Dream_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Dream_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Dream_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Dream_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Dream_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Dream_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Dream_tabview_1), &style_Dream_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Dream_tabview_1_extra_btnm_items_default
    static lv_style_t style_Dream_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Dream_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Dream_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Dream_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Dream_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Dream_tabview_1), &style_Dream_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Dream_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Dream_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Dream_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Dream_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Dream_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Dream_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Dream_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Dream_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Dream_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Dream_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Dream_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Dream_tabview_1), &style_Dream_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Dream_tabview_1_tab_1 = lv_tabview_add_tab(ui->Dream_tabview_1,"");
    lv_obj_t * Dream_tabview_1_tab_1_label = lv_label_create(ui->Dream_tabview_1_tab_1);
    lv_label_set_text(Dream_tabview_1_tab_1_label, "");

    //Write codes Dream_cont_1
    ui->Dream_cont_1 = lv_obj_create(ui->Dream);
    lv_obj_set_pos(ui->Dream_cont_1, 0, 85);
    lv_obj_set_size(ui->Dream_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->Dream_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Dream_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_btn_1
    ui->Dream_btn_1 = lv_btn_create(ui->Dream);
    ui->Dream_btn_1_label = lv_label_create(ui->Dream_btn_1);
    lv_label_set_text(ui->Dream_btn_1_label, "梦幻帘");
    lv_label_set_long_mode(ui->Dream_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Dream_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->Dream_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Dream_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Dream_btn_1, 70, 25);
    lv_obj_set_size(ui->Dream_btn_1, 125, 38);

    //Write style for Dream_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Dream_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianOpen
    ui->Dream_FabCurtianOpen = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianOpen, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianOpen, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCOpen.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianOpen, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCOpen.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianOpen, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianOpen, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianOpen, 63, 660);
    lv_obj_set_size(ui->Dream_FabCurtianOpen, 94, 95);

    //Write style for Dream_FabCurtianOpen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianOpen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianOpen, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianClose
    ui->Dream_FabCurtianClose = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianClose, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianClose, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCClose.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianClose, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCClose.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianClose, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianClose, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianClose, 560, 660);
    lv_obj_set_size(ui->Dream_FabCurtianClose, 95, 95);

    //Write style for Dream_FabCurtianClose, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianClose, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianClose, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPause
    ui->Dream_FabCurtianPause = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianPause, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianPause, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPause.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianPause, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPause.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianPause, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianPause, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianPause, 311, 660);
    lv_obj_set_size(ui->Dream_FabCurtianPause, 109, 110);

    //Write style for Dream_FabCurtianPause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianPause, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianPause, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianBg1
    ui->Dream_FabCurtianBg1 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianBg1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianBg1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg1.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianBg1, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg1.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianBg1, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianBg1, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianBg1, 232, 255);
    lv_obj_set_size(ui->Dream_FabCurtianBg1, 62, 60);

    //Write style for Dream_FabCurtianBg1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianBg1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianBg1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianBg2
    ui->Dream_FabCurtianBg2 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianBg2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianBg2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg2.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianBg2, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg2.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianBg2, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianBg2, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianBg2, 415, 272);
    lv_obj_set_size(ui->Dream_FabCurtianBg2, 34, 73);

    //Write style for Dream_FabCurtianBg2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianBg2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianBg2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianBg3
    ui->Dream_FabCurtianBg3 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianBg3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianBg3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg3.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianBg3, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg3.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianBg3, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianBg3, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianBg3, 252, 384);
    lv_obj_set_size(ui->Dream_FabCurtianBg3, 42, 14);

    //Write style for Dream_FabCurtianBg3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianBg3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianBg3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianLeft
    ui->Dream_FabCurtianLeft = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianLeft, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianLeft, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DreamLeft.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianLeft, "S:/sdfile/EXT_RESERVED/uipackres/ui/DreamLeft.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianLeft, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianLeft, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianLeft, 129, 193);
    lv_obj_set_size(ui->Dream_FabCurtianLeft, 230, 249);

    //Write style for Dream_FabCurtianLeft, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianLeft, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianLeft, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianright
    ui->Dream_FabCurtianright = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianright, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianright, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DreamRight.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianright, "S:/sdfile/EXT_RESERVED/uipackres/ui/DreamRight.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianright, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianright, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianright, 359, 193);
    lv_obj_set_size(ui->Dream_FabCurtianright, 230, 249);

    //Write style for Dream_FabCurtianright, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianright, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianright, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_cont_2
    ui->Dream_cont_2 = lv_obj_create(ui->Dream);
    lv_obj_set_pos(ui->Dream_cont_2, -8, 148);
    lv_obj_set_size(ui->Dream_cont_2, 134, 326);
    lv_obj_set_scrollbar_mode(ui->Dream_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for Dream_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_cont_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_cont_3
    ui->Dream_cont_3 = lv_obj_create(ui->Dream);
    lv_obj_set_pos(ui->Dream_cont_3, 592, 156);
    lv_obj_set_size(ui->Dream_cont_3, 140, 326);
    lv_obj_set_scrollbar_mode(ui->Dream_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for Dream_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_cont_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPull2
    ui->Dream_FabCurtianPull2 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianPull2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianPull2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPull.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianPull2, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPull.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianPull2, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianPull2, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianPull2, 369, 295);
    lv_obj_set_size(ui->Dream_FabCurtianPull2, 45, 45);

    //Write style for Dream_FabCurtianPull2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianPull2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianPull2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPull1
    ui->Dream_FabCurtianPull1 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianPull1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianPull1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPull.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianPull1, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPull.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianPull1, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianPull1, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianPull1, 304, 295);
    lv_obj_set_size(ui->Dream_FabCurtianPull1, 45, 45);

    //Write style for Dream_FabCurtianPull1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianPull1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianPull1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPole
    ui->Dream_FabCurtianPole = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_FabCurtianPole, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Dream_FabCurtianPole, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPole.png");
#else
    lv_img_set_src(ui->Dream_FabCurtianPole, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPole.png");
#endif
    lv_img_set_pivot(ui->Dream_FabCurtianPole, 50,50);
    lv_img_set_angle(ui->Dream_FabCurtianPole, 0);
    lv_obj_set_pos(ui->Dream_FabCurtianPole, 112, 178);
    lv_obj_set_size(ui->Dream_FabCurtianPole, 494, 34);

    //Write style for Dream_FabCurtianPole, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_FabCurtianPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_FabCurtianPole, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_FabCurtianPole, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_slider_1
    ui->Dream_slider_1 = lv_slider_create(ui->Dream);
    lv_slider_set_range(ui->Dream_slider_1, 0, 100);
    lv_slider_set_mode(ui->Dream_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->Dream_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->Dream_slider_1, 191, 502);
    lv_obj_set_size(ui->Dream_slider_1, 330, 8);

    //Write style for Dream_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_slider_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Dream_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Dream_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_slider_1, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for Dream_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Dream_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Dream_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_slider_1, 8, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Dream_label_1
    ui->Dream_label_1 = lv_label_create(ui->Dream);
    lv_label_set_text(ui->Dream_label_1, "0%");
    lv_label_set_long_mode(ui->Dream_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Dream_label_1, 307, 455);
    lv_obj_set_size(ui->Dream_label_1, 73, 31);

    //Write style for Dream_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_label_1, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_label_2
    ui->Dream_label_2 = lv_label_create(ui->Dream);
    lv_label_set_text(ui->Dream_label_2, "0°");
    lv_label_set_long_mode(ui->Dream_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Dream_label_2, 183, 527);
    lv_obj_set_size(ui->Dream_label_2, 73, 31);

    //Write style for Dream_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_label_2, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_label_3
    ui->Dream_label_3 = lv_label_create(ui->Dream);
    lv_label_set_text(ui->Dream_label_3, "90°");
    lv_label_set_long_mode(ui->Dream_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Dream_label_3, 307, 527);
    lv_obj_set_size(ui->Dream_label_3, 73, 31);

    //Write style for Dream_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_label_3, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_label_4
    ui->Dream_label_4 = lv_label_create(ui->Dream);
    lv_label_set_text(ui->Dream_label_4, "180°");
    lv_label_set_long_mode(ui->Dream_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Dream_label_4, 461, 527);
    lv_obj_set_size(ui->Dream_label_4, 73, 31);

    //Write style for Dream_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_label_4, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_img_1
    ui->Dream_img_1 = lv_img_create(ui->Dream);
    lv_obj_add_flag(ui->Dream_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Dream_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Dream_img_1, 50,50);
    lv_img_set_angle(ui->Dream_img_1, 0);
    lv_obj_set_pos(ui->Dream_img_1, 43, 28);
    lv_obj_set_size(ui->Dream_img_1, 14, 24);

    //Write style for Dream_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Dream_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Dream_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Dream_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_btn_2
    ui->Dream_btn_2 = lv_btn_create(ui->Dream);
    ui->Dream_btn_2_label = lv_label_create(ui->Dream_btn_2);
    lv_label_set_text(ui->Dream_btn_2_label, "");
    lv_label_set_long_mode(ui->Dream_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Dream_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Dream_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Dream_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Dream_btn_2, -6, -12);
    lv_obj_set_size(ui->Dream_btn_2, 238, 101);

    //Write style for Dream_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Dream_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPull3
    ui->Dream_FabCurtianPull3 = lv_btn_create(ui->Dream);
    ui->Dream_FabCurtianPull3_label = lv_label_create(ui->Dream_FabCurtianPull3);
    lv_label_set_text(ui->Dream_FabCurtianPull3_label, "");
    lv_label_set_long_mode(ui->Dream_FabCurtianPull3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Dream_FabCurtianPull3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Dream_FabCurtianPull3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Dream_FabCurtianPull3_label, LV_PCT(100));
    lv_obj_set_pos(ui->Dream_FabCurtianPull3, 290, 205);
    lv_obj_set_size(ui->Dream_FabCurtianPull3, 65, 254);

    //Write style for Dream_FabCurtianPull3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_FabCurtianPull3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Dream_FabCurtianPull3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPull3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_FabCurtianPull3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_FabCurtianPull3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_FabCurtianPull3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_FabCurtianPull3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_FabCurtianPull3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Dream_FabCurtianPull4
    ui->Dream_FabCurtianPull4 = lv_btn_create(ui->Dream);
    ui->Dream_FabCurtianPull4_label = lv_label_create(ui->Dream_FabCurtianPull4);
    lv_label_set_text(ui->Dream_FabCurtianPull4_label, "");
    lv_label_set_long_mode(ui->Dream_FabCurtianPull4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Dream_FabCurtianPull4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Dream_FabCurtianPull4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Dream_FabCurtianPull4_label, LV_PCT(100));
    lv_obj_set_pos(ui->Dream_FabCurtianPull4, 362, 205);
    lv_obj_set_size(ui->Dream_FabCurtianPull4, 65, 246);

    //Write style for Dream_FabCurtianPull4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Dream_FabCurtianPull4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Dream_FabCurtianPull4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Dream_FabCurtianPull4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Dream_FabCurtianPull4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Dream_FabCurtianPull4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Dream_FabCurtianPull4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Dream_FabCurtianPull4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Dream_FabCurtianPull4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Dream.


    //Update current screen layout.
    lv_obj_update_layout(ui->Dream);

    //Init events for screen.
    events_init_Dream(ui);
}
