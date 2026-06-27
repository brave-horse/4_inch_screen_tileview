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



void setup_scr_DryRack(lv_ui *ui)
{
    //Write codes DryRack
    ui->DryRack = lv_obj_create(NULL);
    lv_obj_set_size(ui->DryRack, 720, 720);
    lv_obj_set_scrollbar_mode(ui->DryRack, LV_SCROLLBAR_MODE_OFF);

    //Write style for DryRack, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DryRack, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DryRack, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DryRack, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_tabview_1
    ui->DryRack_tabview_1 = lv_tabview_create(ui->DryRack, LV_DIR_TOP, 70);
    lv_obj_set_pos(ui->DryRack_tabview_1, 0, 0);
    lv_obj_set_size(ui->DryRack_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->DryRack_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for DryRack_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DryRack_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DryRack_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DryRack_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DryRack_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DryRack_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DryRack_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DryRack_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_DryRack_tabview_1_extra_btnm_main_default
    static lv_style_t style_DryRack_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_DryRack_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_DryRack_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_DryRack_tabview_1_extra_btnm_main_default, lv_color_hex(0x4f3f3f));
    lv_style_set_bg_grad_dir(&style_DryRack_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_DryRack_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_DryRack_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->DryRack_tabview_1), &style_DryRack_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_DryRack_tabview_1_extra_btnm_items_default
    static lv_style_t style_DryRack_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_DryRack_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_DryRack_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_DryRack_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_DryRack_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->DryRack_tabview_1), &style_DryRack_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_DryRack_tabview_1_extra_btnm_items_checked
    static lv_style_t style_DryRack_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_DryRack_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_DryRack_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_DryRack_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_DryRack_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_DryRack_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_DryRack_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_DryRack_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_DryRack_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_DryRack_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->DryRack_tabview_1), &style_DryRack_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->DryRack_tabview_1_tab_1 = lv_tabview_add_tab(ui->DryRack_tabview_1,"");
    lv_obj_t * DryRack_tabview_1_tab_1_label = lv_label_create(ui->DryRack_tabview_1_tab_1);
    lv_label_set_text(DryRack_tabview_1_tab_1_label, "");

    //Write codes DryRack_cont_1
    ui->DryRack_cont_1 = lv_obj_create(ui->DryRack);
    lv_obj_set_pos(ui->DryRack_cont_1, 0, 85);
    lv_obj_set_size(ui->DryRack_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->DryRack_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for DryRack_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DryRack_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DryRack_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DryRack_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_FabCurtianOpen
    ui->DryRack_FabCurtianOpen = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_FabCurtianOpen, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_FabCurtianOpen, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RollBlindUp.png");
#else
    lv_img_set_src(ui->DryRack_FabCurtianOpen, "S:/sdfile/EXT_RESERVED/uipackres/ui/RollBlindUp.png");
#endif
    lv_img_set_pivot(ui->DryRack_FabCurtianOpen, 50,50);
    lv_img_set_angle(ui->DryRack_FabCurtianOpen, 0);
    lv_obj_set_pos(ui->DryRack_FabCurtianOpen, 61, 665);
    lv_obj_set_size(ui->DryRack_FabCurtianOpen, 94, 95);

    //Write style for DryRack_FabCurtianOpen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_FabCurtianOpen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_FabCurtianOpen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_FabCurtianOpen, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_FabCurtianClose
    ui->DryRack_FabCurtianClose = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_FabCurtianClose, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_FabCurtianClose, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RBDown.png");
#else
    lv_img_set_src(ui->DryRack_FabCurtianClose, "S:/sdfile/EXT_RESERVED/uipackres/ui/RBDown.png");
#endif
    lv_img_set_pivot(ui->DryRack_FabCurtianClose, 50,50);
    lv_img_set_angle(ui->DryRack_FabCurtianClose, 0);
    lv_obj_set_pos(ui->DryRack_FabCurtianClose, 558, 665);
    lv_obj_set_size(ui->DryRack_FabCurtianClose, 94, 95);

    //Write style for DryRack_FabCurtianClose, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_FabCurtianClose, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_FabCurtianClose, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_FabCurtianClose, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_FabCurtianPause
    ui->DryRack_FabCurtianPause = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_FabCurtianPause, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_FabCurtianPause, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DRPause.png");
#else
    lv_img_set_src(ui->DryRack_FabCurtianPause, "S:/sdfile/EXT_RESERVED/uipackres/ui/DRPause.png");
#endif
    lv_img_set_pivot(ui->DryRack_FabCurtianPause, 50,50);
    lv_img_set_angle(ui->DryRack_FabCurtianPause, 0);
    lv_obj_set_pos(ui->DryRack_FabCurtianPause, 302, 651);
    lv_obj_set_size(ui->DryRack_FabCurtianPause, 109, 109);

    //Write style for DryRack_FabCurtianPause, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_FabCurtianPause, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_FabCurtianPause, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_FabCurtianPause, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_img_1
    ui->DryRack_img_1 = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_img_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_img_1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DryRackPole.png");
#else
    lv_img_set_src(ui->DryRack_img_1, "S:/sdfile/EXT_RESERVED/uipackres/ui/DryRackPole.png");
#endif
    lv_img_set_pivot(ui->DryRack_img_1, 50,50);
    lv_img_set_angle(ui->DryRack_img_1, 0);
    lv_obj_set_pos(ui->DryRack_img_1, 162, -110);
    lv_obj_set_size(ui->DryRack_img_1, 405, 319);

    //Write style for DryRack_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_DRLightImg
    ui->DryRack_DRLightImg = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_DRLightImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_DRLightImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DryRackL.png");
#else
    lv_img_set_src(ui->DryRack_DRLightImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/DryRackL.png");
#endif
    lv_img_set_pivot(ui->DryRack_DRLightImg, 50,50);
    lv_img_set_angle(ui->DryRack_DRLightImg, 0);
    lv_obj_set_pos(ui->DryRack_DRLightImg, 284, 154);
    lv_obj_set_size(ui->DryRack_DRLightImg, 163, 30);

    //Write style for DryRack_DRLightImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_DRLightImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_DRLightImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_DRLightImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_DRLightImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_RollBlindPole
    ui->DryRack_RollBlindPole = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_RollBlindPole, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->DryRack_RollBlindPole, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DryRackTop.png");
#else
    lv_img_set_src(ui->DryRack_RollBlindPole, "S:/sdfile/EXT_RESERVED/uipackres/ui/DryRackTop.png");
#endif
    lv_img_set_pivot(ui->DryRack_RollBlindPole, 50,50);
    lv_img_set_angle(ui->DryRack_RollBlindPole, 0);
    lv_obj_set_pos(ui->DryRack_RollBlindPole, 230, 146);
    lv_obj_set_size(ui->DryRack_RollBlindPole, 272, 26);

    //Write style for DryRack_RollBlindPole, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_RollBlindPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_RollBlindPole, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_RollBlindPole, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_RollBlindPole, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_cont_2
    ui->DryRack_cont_2 = lv_obj_create(ui->DryRack);
    lv_obj_set_pos(ui->DryRack_cont_2, 0, 64);
    lv_obj_set_size(ui->DryRack_cont_2, 720, 82);
    lv_obj_set_scrollbar_mode(ui->DryRack_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for DryRack_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DryRack_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DryRack_cont_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DryRack_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_cont_3
    ui->DryRack_cont_3 = lv_obj_create(ui->DryRack);
    lv_obj_set_pos(ui->DryRack_cont_3, 0, -5);
    lv_obj_set_size(ui->DryRack_cont_3, 720, 90);
    lv_obj_set_scrollbar_mode(ui->DryRack_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for DryRack_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DryRack_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->DryRack_cont_3, lv_color_hex(0x243241), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->DryRack_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_imgbtn_1
    ui->DryRack_imgbtn_1 = lv_imgbtn_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->DryRack_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DRLightOff.png", NULL);
    lv_imgbtn_set_src(ui->DryRack_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DRLightOn.png", NULL);
#else
    lv_imgbtn_set_src(ui->DryRack_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/DRLightOff.png", NULL);
    lv_imgbtn_set_src(ui->DryRack_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/DRLightOn.png", NULL);
#endif
    ui->DryRack_imgbtn_1_label = lv_label_create(ui->DryRack_imgbtn_1);
    lv_label_set_text(ui->DryRack_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->DryRack_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->DryRack_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DryRack_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->DryRack_imgbtn_1, 29, 97);
    lv_obj_set_size(ui->DryRack_imgbtn_1, 109, 109);

    //Write style for DryRack_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->DryRack_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DryRack_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for DryRack_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->DryRack_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->DryRack_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for DryRack_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->DryRack_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->DryRack_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for DryRack_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->DryRack_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes DryRack_btn_1
    ui->DryRack_btn_1 = lv_btn_create(ui->DryRack);
    ui->DryRack_btn_1_label = lv_label_create(ui->DryRack_btn_1);
    lv_label_set_text(ui->DryRack_btn_1_label, "晾衣机");
    lv_label_set_long_mode(ui->DryRack_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->DryRack_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->DryRack_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DryRack_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->DryRack_btn_1, 70, 25);
    lv_obj_set_size(ui->DryRack_btn_1, 123, 36);

    //Write style for DryRack_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DryRack_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DryRack_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DryRack_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DryRack_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_label_1
    ui->DryRack_label_1 = lv_label_create(ui->DryRack);
    lv_label_set_text(ui->DryRack_label_1, "100%");
    lv_label_set_long_mode(ui->DryRack_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->DryRack_label_1, 314, 230);
    lv_obj_set_size(ui->DryRack_label_1, 100, 32);

    //Write style for DryRack_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DryRack_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_label_1, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DryRack_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_img_2
    ui->DryRack_img_2 = lv_img_create(ui->DryRack);
    lv_obj_add_flag(ui->DryRack_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->DryRack_img_2, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->DryRack_img_2, 50,50);
    lv_img_set_angle(ui->DryRack_img_2, 0);
    lv_obj_set_pos(ui->DryRack_img_2, 43, 28);
    lv_obj_set_size(ui->DryRack_img_2, 14, 24);

    //Write style for DryRack_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->DryRack_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->DryRack_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->DryRack_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_btn_2
    ui->DryRack_btn_2 = lv_btn_create(ui->DryRack);
    ui->DryRack_btn_2_label = lv_label_create(ui->DryRack_btn_2);
    lv_label_set_text(ui->DryRack_btn_2_label, "");
    lv_label_set_long_mode(ui->DryRack_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->DryRack_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DryRack_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DryRack_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->DryRack_btn_2, -5, -15);
    lv_obj_set_size(ui->DryRack_btn_2, 234, 103);

    //Write style for DryRack_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DryRack_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DryRack_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DryRack_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DryRack_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes DryRack_dry_rack_pull
    ui->DryRack_dry_rack_pull = lv_btn_create(ui->DryRack);
    ui->DryRack_dry_rack_pull_label = lv_label_create(ui->DryRack_dry_rack_pull);
    lv_label_set_text(ui->DryRack_dry_rack_pull_label, "");
    lv_label_set_long_mode(ui->DryRack_dry_rack_pull_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->DryRack_dry_rack_pull_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->DryRack_dry_rack_pull, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->DryRack_dry_rack_pull_label, LV_PCT(100));
    lv_obj_set_pos(ui->DryRack_dry_rack_pull, 145, 176);
    lv_obj_set_size(ui->DryRack_dry_rack_pull, 445, 82);

    //Write style for DryRack_dry_rack_pull, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->DryRack_dry_rack_pull, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->DryRack_dry_rack_pull, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->DryRack_dry_rack_pull, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->DryRack_dry_rack_pull, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->DryRack_dry_rack_pull, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->DryRack_dry_rack_pull, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->DryRack_dry_rack_pull, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->DryRack_dry_rack_pull, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of DryRack.


    //Update current screen layout.
    lv_obj_update_layout(ui->DryRack);

    //Init events for screen.
    events_init_DryRack(ui);
}
