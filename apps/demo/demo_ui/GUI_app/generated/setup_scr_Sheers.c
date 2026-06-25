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



void setup_scr_Sheers(lv_ui *ui)
{
    //Write codes Sheers
    ui->Sheers = lv_obj_create(NULL);
    lv_obj_set_size(ui->Sheers, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Sheers, LV_SCROLLBAR_MODE_OFF);

    //Write style for Sheers, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Sheers, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Sheers, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Sheers, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_tabview_1
    ui->Sheers_tabview_1 = lv_tabview_create(ui->Sheers, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Sheers_tabview_1, 0, 0);
    lv_obj_set_size(ui->Sheers_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Sheers_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Sheers_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Sheers_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Sheers_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Sheers_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Sheers_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Sheers_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Sheers_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Sheers_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Sheers_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Sheers_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Sheers_tabview_1_extra_btnm_main_default
    static lv_style_t style_Sheers_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Sheers_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Sheers_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Sheers_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Sheers_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Sheers_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Sheers_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Sheers_tabview_1), &style_Sheers_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Sheers_tabview_1_extra_btnm_items_default
    static lv_style_t style_Sheers_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Sheers_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Sheers_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Sheers_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Sheers_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Sheers_tabview_1), &style_Sheers_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Sheers_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Sheers_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Sheers_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Sheers_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Sheers_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Sheers_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Sheers_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Sheers_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Sheers_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Sheers_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Sheers_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Sheers_tabview_1), &style_Sheers_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Sheers_tabview_1_tab_1 = lv_tabview_add_tab(ui->Sheers_tabview_1,"");
    lv_obj_t * Sheers_tabview_1_tab_1_label = lv_label_create(ui->Sheers_tabview_1_tab_1);
    lv_label_set_text(Sheers_tabview_1_tab_1_label, "");

    //Write codes Sheers_cont_1
    ui->Sheers_cont_1 = lv_obj_create(ui->Sheers);
    lv_obj_set_pos(ui->Sheers_cont_1, 0, 85);
    lv_obj_set_size(ui->Sheers_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->Sheers_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Sheers_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Sheers_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Sheers_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Sheers_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_btn_1
    ui->Sheers_btn_1 = lv_btn_create(ui->Sheers);
    ui->Sheers_btn_1_label = lv_label_create(ui->Sheers_btn_1);
    lv_label_set_text(ui->Sheers_btn_1_label, "纱  帘");
    lv_label_set_long_mode(ui->Sheers_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Sheers_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->Sheers_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Sheers_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Sheers_btn_1, 70, 25);
    lv_obj_set_size(ui->Sheers_btn_1, 94, 34);

    //Write style for Sheers_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Sheers_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Sheers_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Sheers_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Sheers_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Sheers_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Sheers_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianOpen
    ui->Sheers_FabCurtianOpen = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianOpen, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianOpen, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCOpen.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianOpen, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCOpen.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianOpen, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianOpen, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianOpen, 69, 670);
    lv_obj_set_size(ui->Sheers_FabCurtianOpen, 94, 95);

    //Write style for Sheers_FabCurtianOpen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianOpen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianOpen, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianClose
    ui->Sheers_FabCurtianClose = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianClose, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianClose, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCClose.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianClose, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCClose.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianClose, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianClose, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianClose, 567, 670);
    lv_obj_set_size(ui->Sheers_FabCurtianClose, 95, 95);

    //Write style for Sheers_FabCurtianClose, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianClose, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianClose, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianPause
    ui->Sheers_FabCurtianPause = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianPause, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianPause, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPause.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianPause, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPause.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianPause, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianPause, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianPause, 317, 670);
    lv_obj_set_size(ui->Sheers_FabCurtianPause, 109, 110);

    //Write style for Sheers_FabCurtianPause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianPause, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianPause, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianBg1
    ui->Sheers_FabCurtianBg1 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianBg1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianBg1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg1.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianBg1, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg1.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianBg1, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianBg1, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianBg1, 232, 255);
    lv_obj_set_size(ui->Sheers_FabCurtianBg1, 62, 60);

    //Write style for Sheers_FabCurtianBg1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianBg1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianBg1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianBg2
    ui->Sheers_FabCurtianBg2 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianBg2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianBg2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg2.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianBg2, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg2.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianBg2, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianBg2, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianBg2, 415, 272);
    lv_obj_set_size(ui->Sheers_FabCurtianBg2, 34, 73);

    //Write style for Sheers_FabCurtianBg2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianBg2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianBg2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianBg3
    ui->Sheers_FabCurtianBg3 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianBg3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianBg3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg3.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianBg3, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg3.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianBg3, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianBg3, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianBg3, 252, 384);
    lv_obj_set_size(ui->Sheers_FabCurtianBg3, 42, 14);

    //Write style for Sheers_FabCurtianBg3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianBg3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianBg3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianLeft
    ui->Sheers_FabCurtianLeft = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianLeft, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianLeft, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\SheersLeft.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianLeft, "S:/sdfile/EXT_RESERVED/uipackres/ui/SheersLeft.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianLeft, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianLeft, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianLeft, 129, 202);
    lv_obj_set_size(ui->Sheers_FabCurtianLeft, 230, 282);

    //Write style for Sheers_FabCurtianLeft, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianLeft, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianLeft, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianright
    ui->Sheers_FabCurtianright = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianright, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianright, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\SheersRight.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianright, "S:/sdfile/EXT_RESERVED/uipackres/ui/SheersRight.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianright, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianright, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianright, 359, 202);
    lv_obj_set_size(ui->Sheers_FabCurtianright, 230, 282);

    //Write style for Sheers_FabCurtianright, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianright, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianright, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianright, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_cont_2
    ui->Sheers_cont_2 = lv_obj_create(ui->Sheers);
    lv_obj_set_pos(ui->Sheers_cont_2, -2, 164);
    lv_obj_set_size(ui->Sheers_cont_2, 130, 336);
    lv_obj_set_scrollbar_mode(ui->Sheers_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for Sheers_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Sheers_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Sheers_cont_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Sheers_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_cont_3
    ui->Sheers_cont_3 = lv_obj_create(ui->Sheers);
    lv_obj_set_pos(ui->Sheers_cont_3, 591, 174);
    lv_obj_set_size(ui->Sheers_cont_3, 130, 336);
    lv_obj_set_scrollbar_mode(ui->Sheers_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for Sheers_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Sheers_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Sheers_cont_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Sheers_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianPull2
    ui->Sheers_FabCurtianPull2 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianPull2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianPull2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPull.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianPull2, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPull.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianPull2, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianPull2, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianPull2, 361, 321);
    lv_obj_set_size(ui->Sheers_FabCurtianPull2, 45, 45);

    //Write style for Sheers_FabCurtianPull2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianPull2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianPull2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianPull1
    ui->Sheers_FabCurtianPull1 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianPull1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianPull1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPull.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianPull1, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPull.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianPull1, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianPull1, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianPull1, 311, 321);
    lv_obj_set_size(ui->Sheers_FabCurtianPull1, 45, 45);

    //Write style for Sheers_FabCurtianPull1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianPull1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianPull1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_FabCurtianPole
    ui->Sheers_FabCurtianPole = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_FabCurtianPole, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Sheers_FabCurtianPole, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPole.png");
#else
    lv_img_set_src(ui->Sheers_FabCurtianPole, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPole.png");
#endif
    lv_img_set_pivot(ui->Sheers_FabCurtianPole, 50,50);
    lv_img_set_angle(ui->Sheers_FabCurtianPole, 0);
    lv_obj_set_pos(ui->Sheers_FabCurtianPole, 112, 178);
    lv_obj_set_size(ui->Sheers_FabCurtianPole, 494, 34);

    //Write style for Sheers_FabCurtianPole, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_FabCurtianPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_FabCurtianPole, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_FabCurtianPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_FabCurtianPole, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_img_1
    ui->Sheers_img_1 = lv_img_create(ui->Sheers);
    lv_obj_add_flag(ui->Sheers_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Sheers_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Sheers_img_1, 50,50);
    lv_img_set_angle(ui->Sheers_img_1, 0);
    lv_obj_set_pos(ui->Sheers_img_1, 43, 28);
    lv_obj_set_size(ui->Sheers_img_1, 14, 24);

    //Write style for Sheers_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Sheers_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Sheers_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Sheers_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Sheers_btn_2
    ui->Sheers_btn_2 = lv_btn_create(ui->Sheers);
    ui->Sheers_btn_2_label = lv_label_create(ui->Sheers_btn_2);
    lv_label_set_text(ui->Sheers_btn_2_label, "");
    lv_label_set_long_mode(ui->Sheers_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Sheers_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Sheers_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Sheers_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Sheers_btn_2, -6, -10);
    lv_obj_set_size(ui->Sheers_btn_2, 232, 103);

    //Write style for Sheers_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Sheers_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Sheers_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Sheers_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Sheers_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Sheers_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Sheers_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Sheers_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Sheers_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Sheers.


    //Update current screen layout.
    lv_obj_update_layout(ui->Sheers);

    //Init events for screen.
    events_init_Sheers(ui);
}
