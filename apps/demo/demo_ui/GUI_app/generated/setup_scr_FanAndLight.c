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



void setup_scr_FanAndLight(lv_ui *ui)
{
    //Write codes FanAndLight
    ui->FanAndLight = lv_obj_create(NULL);
    lv_obj_set_size(ui->FanAndLight, 720, 720);
    lv_obj_set_scrollbar_mode(ui->FanAndLight, LV_SCROLLBAR_MODE_OFF);

    //Write style for FanAndLight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->FanAndLight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->FanAndLight, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->FanAndLight, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_tabview_1
    ui->FanAndLight_tabview_1 = lv_tabview_create(ui->FanAndLight, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->FanAndLight_tabview_1, 0, 0);
    lv_obj_set_size(ui->FanAndLight_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->FanAndLight_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for FanAndLight_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->FanAndLight_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->FanAndLight_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->FanAndLight_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->FanAndLight_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->FanAndLight_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->FanAndLight_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->FanAndLight_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->FanAndLight_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->FanAndLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->FanAndLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_FanAndLight_tabview_1_extra_btnm_main_default
    static lv_style_t style_FanAndLight_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_FanAndLight_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_FanAndLight_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_FanAndLight_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_FanAndLight_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_FanAndLight_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_FanAndLight_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->FanAndLight_tabview_1), &style_FanAndLight_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_FanAndLight_tabview_1_extra_btnm_items_default
    static lv_style_t style_FanAndLight_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_FanAndLight_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_FanAndLight_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_FanAndLight_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_FanAndLight_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->FanAndLight_tabview_1), &style_FanAndLight_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_FanAndLight_tabview_1_extra_btnm_items_checked
    static lv_style_t style_FanAndLight_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_FanAndLight_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_FanAndLight_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_FanAndLight_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_FanAndLight_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_FanAndLight_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_FanAndLight_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_FanAndLight_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_FanAndLight_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_FanAndLight_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->FanAndLight_tabview_1), &style_FanAndLight_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->FanAndLight_tabview_1_tab_1 = lv_tabview_add_tab(ui->FanAndLight_tabview_1,"");
    lv_obj_t * FanAndLight_tabview_1_tab_1_label = lv_label_create(ui->FanAndLight_tabview_1_tab_1);
    lv_label_set_text(FanAndLight_tabview_1_tab_1_label, "");

    //Write codes FanAndLight_cont_1
    ui->FanAndLight_cont_1 = lv_obj_create(ui->FanAndLight);
    lv_obj_set_pos(ui->FanAndLight_cont_1, 0, 85);
    lv_obj_set_size(ui->FanAndLight_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->FanAndLight_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for FanAndLight_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->FanAndLight_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->FanAndLight_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->FanAndLight_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->FanAndLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_fLight_off
    ui->FanAndLight_fLight_off = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_fLight_off, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_fLight_off, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DRLightOff.png");
#else
    lv_img_set_src(ui->FanAndLight_fLight_off, "S:/sdfile/EXT_RESERVED/uipackres/ui/DRLightOff.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_fLight_off, 50,50);
    lv_img_set_angle(ui->FanAndLight_fLight_off, 0);
    lv_obj_set_pos(ui->FanAndLight_fLight_off, 51, 552);
    lv_obj_set_size(ui->FanAndLight_fLight_off, 109, 109);

    //Write style for FanAndLight_fLight_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_fLight_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_fLight_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_fLight_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_fLight_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_fLight_on
    ui->FanAndLight_fLight_on = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_fLight_on, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_fLight_on, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\DRLightOn.png");
#else
    lv_img_set_src(ui->FanAndLight_fLight_on, "S:/sdfile/EXT_RESERVED/uipackres/ui/DRLightOn.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_fLight_on, 50,50);
    lv_img_set_angle(ui->FanAndLight_fLight_on, 0);
    lv_obj_set_pos(ui->FanAndLight_fLight_on, 51, 552);
    lv_obj_set_size(ui->FanAndLight_fLight_on, 109, 110);

    //Write style for FanAndLight_fLight_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_fLight_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_fLight_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_fLight_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_fLight_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_fan
    ui->FanAndLight_fan = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_fan, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_fan, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\fan.png");
#else
    lv_img_set_src(ui->FanAndLight_fan, "S:/sdfile/EXT_RESERVED/uipackres/ui/fan.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_fan, 103,102);
    lv_img_set_angle(ui->FanAndLight_fan, 0);
    lv_obj_set_pos(ui->FanAndLight_fan, 257, 210);
    lv_obj_set_size(ui->FanAndLight_fan, 206, 204);

    //Write style for FanAndLight_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_fan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_fan, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FanSpeed4
    ui->FanAndLight_FanSpeed4 = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FanSpeed4, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FanSpeed4, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed4.png");
#else
    lv_img_set_src(ui->FanAndLight_FanSpeed4, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed4.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FanSpeed4, 50,50);
    lv_img_set_angle(ui->FanAndLight_FanSpeed4, 0);
    lv_obj_set_pos(ui->FanAndLight_FanSpeed4, 533, 545);
    lv_obj_set_size(ui->FanAndLight_FanSpeed4, 109, 109);

    //Write style for FanAndLight_FanSpeed4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FanSpeed4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FanSpeed4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FanSpeed4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FanSpeed4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FanSpeed3
    ui->FanAndLight_FanSpeed3 = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FanSpeed3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FanSpeed3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed3.png");
#else
    lv_img_set_src(ui->FanAndLight_FanSpeed3, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed3.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FanSpeed3, 50,50);
    lv_img_set_angle(ui->FanAndLight_FanSpeed3, 0);
    lv_obj_set_pos(ui->FanAndLight_FanSpeed3, 536, 545);
    lv_obj_set_size(ui->FanAndLight_FanSpeed3, 109, 109);

    //Write style for FanAndLight_FanSpeed3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FanSpeed3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FanSpeed3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FanSpeed3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FanSpeed3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FanSpeed2
    ui->FanAndLight_FanSpeed2 = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FanSpeed2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FanSpeed2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed2.png");
#else
    lv_img_set_src(ui->FanAndLight_FanSpeed2, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed2.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FanSpeed2, 50,50);
    lv_img_set_angle(ui->FanAndLight_FanSpeed2, 0);
    lv_obj_set_pos(ui->FanAndLight_FanSpeed2, 536, 545);
    lv_obj_set_size(ui->FanAndLight_FanSpeed2, 105, 109);

    //Write style for FanAndLight_FanSpeed2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FanSpeed2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FanSpeed2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FanSpeed2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FanSpeed2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FanSpeed1
    ui->FanAndLight_FanSpeed1 = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FanSpeed1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FanSpeed1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed1.png");
#else
    lv_img_set_src(ui->FanAndLight_FanSpeed1, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed1.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FanSpeed1, 50,50);
    lv_img_set_angle(ui->FanAndLight_FanSpeed1, 0);
    lv_obj_set_pos(ui->FanAndLight_FanSpeed1, 536, 545);
    lv_obj_set_size(ui->FanAndLight_FanSpeed1, 109, 109);

    //Write style for FanAndLight_FanSpeed1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FanSpeed1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FanSpeed1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FanSpeed1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FanSpeed1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_Fan_on
    ui->FanAndLight_Fan_on = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_Fan_on, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_Fan_on, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\fanon.png");
#else
    lv_img_set_src(ui->FanAndLight_Fan_on, "S:/sdfile/EXT_RESERVED/uipackres/ui/fanon.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_Fan_on, 50,50);
    lv_img_set_angle(ui->FanAndLight_Fan_on, 0);
    lv_obj_set_pos(ui->FanAndLight_Fan_on, 296, 552);
    lv_obj_set_size(ui->FanAndLight_Fan_on, 109, 109);

    //Write style for FanAndLight_Fan_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_Fan_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_Fan_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_Fan_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_Fan_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_Fan_off
    ui->FanAndLight_Fan_off = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_Fan_off, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_Fan_off, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\fanoff.png");
#else
    lv_img_set_src(ui->FanAndLight_Fan_off, "S:/sdfile/EXT_RESERVED/uipackres/ui/fanoff.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_Fan_off, 50,50);
    lv_img_set_angle(ui->FanAndLight_Fan_off, 0);
    lv_obj_set_pos(ui->FanAndLight_Fan_off, 296, 552);
    lv_obj_set_size(ui->FanAndLight_Fan_off, 109, 109);

    //Write style for FanAndLight_Fan_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_Fan_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_Fan_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_Fan_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_Fan_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FLightOnImg
    ui->FanAndLight_FLightOnImg = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FLightOnImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FLightOnImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\lightOn.png");
#else
    lv_img_set_src(ui->FanAndLight_FLightOnImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/lightOn.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FLightOnImg, 50,50);
    lv_img_set_angle(ui->FanAndLight_FLightOnImg, 0);
    lv_obj_set_pos(ui->FanAndLight_FLightOnImg, 320, 277);
    lv_obj_set_size(ui->FanAndLight_FLightOnImg, 82, 82);

    //Write style for FanAndLight_FLightOnImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FLightOnImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FLightOnImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FLightOnImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FLightOnImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_FLightOffImg
    ui->FanAndLight_FLightOffImg = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_FLightOffImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->FanAndLight_FLightOffImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\lightOff.png");
#else
    lv_img_set_src(ui->FanAndLight_FLightOffImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/lightOff.png");
#endif
    lv_img_set_pivot(ui->FanAndLight_FLightOffImg, 50,50);
    lv_img_set_angle(ui->FanAndLight_FLightOffImg, 0);
    lv_obj_set_pos(ui->FanAndLight_FLightOffImg, 320, 277);
    lv_obj_set_size(ui->FanAndLight_FLightOffImg, 82, 82);

    //Write style for FanAndLight_FLightOffImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_FLightOffImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_FLightOffImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_FLightOffImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_FLightOffImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_btn_1
    ui->FanAndLight_btn_1 = lv_btn_create(ui->FanAndLight);
    ui->FanAndLight_btn_1_label = lv_label_create(ui->FanAndLight_btn_1);
    lv_label_set_text(ui->FanAndLight_btn_1_label, "风扇灯");
    lv_label_set_long_mode(ui->FanAndLight_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->FanAndLight_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->FanAndLight_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->FanAndLight_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->FanAndLight_btn_1, 70, 25);
    lv_obj_set_size(ui->FanAndLight_btn_1, 124, 32);

    //Write style for FanAndLight_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->FanAndLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->FanAndLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->FanAndLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->FanAndLight_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->FanAndLight_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->FanAndLight_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->FanAndLight_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_imgbtn_1
    ui->FanAndLight_imgbtn_1 = lv_imgbtn_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->FanAndLight_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_ACOff_alpha_100x96, NULL);
    lv_imgbtn_set_src(ui->FanAndLight_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_ACOn_alpha_100x96, NULL);
    ui->FanAndLight_imgbtn_1_label = lv_label_create(ui->FanAndLight_imgbtn_1);
    lv_label_set_text(ui->FanAndLight_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->FanAndLight_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->FanAndLight_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->FanAndLight_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->FanAndLight_imgbtn_1, 40, 120);
    lv_obj_set_size(ui->FanAndLight_imgbtn_1, 100, 96);

    //Write style for FanAndLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->FanAndLight_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->FanAndLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->FanAndLight_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for FanAndLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->FanAndLight_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->FanAndLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for FanAndLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->FanAndLight_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->FanAndLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for FanAndLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->FanAndLight_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes FanAndLight_btn_2
    ui->FanAndLight_btn_2 = lv_btn_create(ui->FanAndLight);
    ui->FanAndLight_btn_2_label = lv_label_create(ui->FanAndLight_btn_2);
    lv_label_set_text(ui->FanAndLight_btn_2_label, "");
    lv_label_set_long_mode(ui->FanAndLight_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->FanAndLight_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->FanAndLight_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->FanAndLight_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->FanAndLight_btn_2, -5, -7);
    lv_obj_set_size(ui->FanAndLight_btn_2, 238, 101);

    //Write style for FanAndLight_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->FanAndLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->FanAndLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->FanAndLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->FanAndLight_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->FanAndLight_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->FanAndLight_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->FanAndLight_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes FanAndLight_img_1
    ui->FanAndLight_img_1 = lv_img_create(ui->FanAndLight);
    lv_obj_add_flag(ui->FanAndLight_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->FanAndLight_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->FanAndLight_img_1, 50,50);
    lv_img_set_angle(ui->FanAndLight_img_1, 0);
    lv_obj_set_pos(ui->FanAndLight_img_1, 43, 28);
    lv_obj_set_size(ui->FanAndLight_img_1, 14, 24);

    //Write style for FanAndLight_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->FanAndLight_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->FanAndLight_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->FanAndLight_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->FanAndLight_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of FanAndLight.


    //Update current screen layout.
    lv_obj_update_layout(ui->FanAndLight);

    //Init events for screen.
    events_init_FanAndLight(ui);
}
