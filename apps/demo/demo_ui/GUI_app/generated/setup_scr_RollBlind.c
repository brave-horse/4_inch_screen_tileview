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



void setup_scr_RollBlind(lv_ui *ui)
{
    //Write codes RollBlind
    ui->RollBlind = lv_obj_create(NULL);
    lv_obj_set_size(ui->RollBlind, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RollBlind, LV_SCROLLBAR_MODE_OFF);

    //Write style for RollBlind, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RollBlind, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RollBlind, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RollBlind, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_tabview_1
    ui->RollBlind_tabview_1 = lv_tabview_create(ui->RollBlind, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->RollBlind_tabview_1, 0, 0);
    lv_obj_set_size(ui->RollBlind_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RollBlind_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for RollBlind_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RollBlind_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RollBlind_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RollBlind_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RollBlind_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RollBlind_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RollBlind_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RollBlind_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RollBlind_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RollBlind_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RollBlind_tabview_1_extra_btnm_main_default
    static lv_style_t style_RollBlind_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_RollBlind_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_RollBlind_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_RollBlind_tabview_1_extra_btnm_main_default, lv_color_hex(0x4f3f3f));
    lv_style_set_bg_grad_dir(&style_RollBlind_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_RollBlind_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_RollBlind_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RollBlind_tabview_1), &style_RollBlind_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RollBlind_tabview_1_extra_btnm_items_default
    static lv_style_t style_RollBlind_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_RollBlind_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_RollBlind_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_RollBlind_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_RollBlind_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RollBlind_tabview_1), &style_RollBlind_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_RollBlind_tabview_1_extra_btnm_items_checked
    static lv_style_t style_RollBlind_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_RollBlind_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_RollBlind_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_RollBlind_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_RollBlind_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_RollBlind_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_RollBlind_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_RollBlind_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_RollBlind_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_RollBlind_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RollBlind_tabview_1), &style_RollBlind_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->RollBlind_tabview_1_tab_1 = lv_tabview_add_tab(ui->RollBlind_tabview_1,"");
    lv_obj_t * RollBlind_tabview_1_tab_1_label = lv_label_create(ui->RollBlind_tabview_1_tab_1);
    lv_label_set_text(RollBlind_tabview_1_tab_1_label, "");

    //Write codes RollBlind_cont_1
    ui->RollBlind_cont_1 = lv_obj_create(ui->RollBlind);
    lv_obj_set_pos(ui->RollBlind_cont_1, 0, 72);
    lv_obj_set_size(ui->RollBlind_cont_1, 720, 645);
    lv_obj_set_scrollbar_mode(ui->RollBlind_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for RollBlind_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RollBlind_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RollBlind_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RollBlind_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianOpen
    ui->RollBlind_FabCurtianOpen = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianOpen, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianOpen, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RollBlindUp.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianOpen, "S:/sdfile/EXT_RESERVED/uipackres/ui/RollBlindUp.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianOpen, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianOpen, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianOpen, 57, 662);
    lv_obj_set_size(ui->RollBlind_FabCurtianOpen, 94, 95);

    //Write style for RollBlind_FabCurtianOpen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianOpen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianOpen, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianClose
    ui->RollBlind_FabCurtianClose = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianClose, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianClose, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RBDown.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianClose, "S:/sdfile/EXT_RESERVED/uipackres/ui/RBDown.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianClose, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianClose, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianClose, 554, 662);
    lv_obj_set_size(ui->RollBlind_FabCurtianClose, 94, 95);

    //Write style for RollBlind_FabCurtianClose, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianClose, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianClose, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_cont_2
    ui->RollBlind_cont_2 = lv_obj_create(ui->RollBlind);
    lv_obj_set_pos(ui->RollBlind_cont_2, 147, 112);
    lv_obj_set_size(ui->RollBlind_cont_2, 435, 353);
    lv_obj_set_scrollbar_mode(ui->RollBlind_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for RollBlind_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RollBlind_cont_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->RollBlind_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->RollBlind_cont_2, lv_color_hex(0x2c2424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->RollBlind_cont_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianPause
    ui->RollBlind_FabCurtianPause = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianPause, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianPause, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCPause.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianPause, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCPause.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianPause, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianPause, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianPause, 305, 662);
    lv_obj_set_size(ui->RollBlind_FabCurtianPause, 95, 95);

    //Write style for RollBlind_FabCurtianPause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianPause, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianPause, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianBg1
    ui->RollBlind_FabCurtianBg1 = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianBg1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianBg1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg1.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianBg1, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg1.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianBg1, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianBg1, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianBg1, 237, 186);
    lv_obj_set_size(ui->RollBlind_FabCurtianBg1, 62, 60);

    //Write style for RollBlind_FabCurtianBg1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianBg1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianBg1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianBg1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianBg2
    ui->RollBlind_FabCurtianBg2 = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianBg2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianBg2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg2.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianBg2, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg2.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianBg2, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianBg2, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianBg2, 420, 203);
    lv_obj_set_size(ui->RollBlind_FabCurtianBg2, 34, 73);

    //Write style for RollBlind_FabCurtianBg2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianBg2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianBg2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianBg2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianBg3
    ui->RollBlind_FabCurtianBg3 = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianBg3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianBg3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\FCBg3.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianBg3, "S:/sdfile/EXT_RESERVED/uipackres/ui/FCBg3.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianBg3, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianBg3, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianBg3, 257, 315);
    lv_obj_set_size(ui->RollBlind_FabCurtianBg3, 42, 14);

    //Write style for RollBlind_FabCurtianBg3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianBg3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianBg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianBg3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianLeft
    ui->RollBlind_FabCurtianLeft = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianLeft, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianLeft, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RBCloth.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianLeft, "S:/sdfile/EXT_RESERVED/uipackres/ui/RBCloth.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianLeft, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianLeft, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianLeft, 147, 112);
    lv_obj_set_size(ui->RollBlind_FabCurtianLeft, 435, 353);

    //Write style for RollBlind_FabCurtianLeft, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianLeft, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianLeft, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_cont_3
    ui->RollBlind_cont_3 = lv_obj_create(ui->RollBlind);
    lv_obj_set_pos(ui->RollBlind_cont_3, 138, 83);
    lv_obj_set_size(ui->RollBlind_cont_3, 456, 28);
    lv_obj_set_scrollbar_mode(ui->RollBlind_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for RollBlind_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RollBlind_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RollBlind_cont_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RollBlind_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_cont_4
    ui->RollBlind_cont_4 = lv_obj_create(ui->RollBlind);
    lv_obj_set_pos(ui->RollBlind_cont_4, 0, 0);
    lv_obj_set_size(ui->RollBlind_cont_4, 720, 85);
    lv_obj_set_scrollbar_mode(ui->RollBlind_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for RollBlind_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RollBlind_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RollBlind_cont_4, lv_color_hex(0x243241), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RollBlind_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianPull1
    ui->RollBlind_FabCurtianPull1 = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_FabCurtianPull1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_FabCurtianPull1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CurtainPull.png");
#else
    lv_img_set_src(ui->RollBlind_FabCurtianPull1, "S:/sdfile/EXT_RESERVED/uipackres/ui/CurtainPull.png");
#endif
    lv_img_set_pivot(ui->RollBlind_FabCurtianPull1, 50,50);
    lv_img_set_angle(ui->RollBlind_FabCurtianPull1, 0);
    lv_obj_set_pos(ui->RollBlind_FabCurtianPull1, 345, 411);
    lv_obj_set_size(ui->RollBlind_FabCurtianPull1, 39, 39);

    //Write style for RollBlind_FabCurtianPull1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_FabCurtianPull1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianPull1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_FabCurtianPull1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_RollBlindPole
    ui->RollBlind_RollBlindPole = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_RollBlindPole, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RollBlind_RollBlindPole, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RBPole.png");
#else
    lv_img_set_src(ui->RollBlind_RollBlindPole, "S:/sdfile/EXT_RESERVED/uipackres/ui/RBPole.png");
#endif
    lv_img_set_pivot(ui->RollBlind_RollBlindPole, 50,50);
    lv_img_set_angle(ui->RollBlind_RollBlindPole, 0);
    lv_obj_set_pos(ui->RollBlind_RollBlindPole, 134, 109);
    lv_obj_set_size(ui->RollBlind_RollBlindPole, 462, 26);

    //Write style for RollBlind_RollBlindPole, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_RollBlindPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_RollBlindPole, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_RollBlindPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_RollBlindPole, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_btn_1
    ui->RollBlind_btn_1 = lv_btn_create(ui->RollBlind);
    ui->RollBlind_btn_1_label = lv_label_create(ui->RollBlind_btn_1);
    lv_label_set_text(ui->RollBlind_btn_1_label, "卷  帘");
    lv_label_set_long_mode(ui->RollBlind_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RollBlind_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->RollBlind_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RollBlind_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->RollBlind_btn_1, 70, 25);
    lv_obj_set_size(ui->RollBlind_btn_1, 95, 36);

    //Write style for RollBlind_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RollBlind_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RollBlind_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RollBlind_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RollBlind_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RollBlind_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RollBlind_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_img_1
    ui->RollBlind_img_1 = lv_img_create(ui->RollBlind);
    lv_obj_add_flag(ui->RollBlind_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RollBlind_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->RollBlind_img_1, 50,50);
    lv_img_set_angle(ui->RollBlind_img_1, 0);
    lv_obj_set_pos(ui->RollBlind_img_1, 43, 28);
    lv_obj_set_size(ui->RollBlind_img_1, 14, 24);

    //Write style for RollBlind_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RollBlind_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RollBlind_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RollBlind_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_btn_2
    ui->RollBlind_btn_2 = lv_btn_create(ui->RollBlind);
    ui->RollBlind_btn_2_label = lv_label_create(ui->RollBlind_btn_2);
    lv_label_set_text(ui->RollBlind_btn_2_label, "");
    lv_label_set_long_mode(ui->RollBlind_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RollBlind_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RollBlind_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RollBlind_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->RollBlind_btn_2, -5, -7);
    lv_obj_set_size(ui->RollBlind_btn_2, 230, 102);

    //Write style for RollBlind_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RollBlind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RollBlind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RollBlind_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RollBlind_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RollBlind_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RollBlind_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RollBlind_FabCurtianPull2
    ui->RollBlind_FabCurtianPull2 = lv_btn_create(ui->RollBlind);
    ui->RollBlind_FabCurtianPull2_label = lv_label_create(ui->RollBlind_FabCurtianPull2);
    lv_label_set_text(ui->RollBlind_FabCurtianPull2_label, "");
    lv_label_set_long_mode(ui->RollBlind_FabCurtianPull2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RollBlind_FabCurtianPull2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RollBlind_FabCurtianPull2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RollBlind_FabCurtianPull2_label, LV_PCT(100));
    lv_obj_set_pos(ui->RollBlind_FabCurtianPull2, 142, 394);
    lv_obj_set_size(ui->RollBlind_FabCurtianPull2, 445, 134);

    //Write style for RollBlind_FabCurtianPull2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RollBlind_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RollBlind_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RollBlind_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RollBlind_FabCurtianPull2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RollBlind_FabCurtianPull2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RollBlind_FabCurtianPull2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RollBlind_FabCurtianPull2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RollBlind_FabCurtianPull2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of RollBlind.


    //Update current screen layout.
    lv_obj_update_layout(ui->RollBlind);

    //Init events for screen.
    events_init_RollBlind(ui);
}
