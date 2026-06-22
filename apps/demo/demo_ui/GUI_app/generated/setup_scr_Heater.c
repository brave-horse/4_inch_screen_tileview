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



void setup_scr_Heater(lv_ui *ui)
{
    //Write codes Heater
    ui->Heater = lv_obj_create(NULL);
    lv_obj_set_size(ui->Heater, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Heater, LV_SCROLLBAR_MODE_OFF);

    //Write style for Heater, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_tabview_1
    ui->Heater_tabview_1 = lv_tabview_create(ui->Heater, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Heater_tabview_1, -1, 0);
    lv_obj_set_size(ui->Heater_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Heater_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Heater_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Heater_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Heater_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Heater_tabview_1_extra_btnm_main_default
    static lv_style_t style_Heater_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Heater_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Heater_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Heater_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Heater_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Heater_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Heater_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Heater_tabview_1), &style_Heater_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Heater_tabview_1_extra_btnm_items_default
    static lv_style_t style_Heater_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Heater_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Heater_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Heater_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Heater_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Heater_tabview_1), &style_Heater_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Heater_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Heater_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Heater_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Heater_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Heater_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Heater_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Heater_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Heater_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Heater_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Heater_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Heater_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Heater_tabview_1), &style_Heater_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Heater_tabview_1_tab_1 = lv_tabview_add_tab(ui->Heater_tabview_1,"");
    lv_obj_t * Heater_tabview_1_tab_1_label = lv_label_create(ui->Heater_tabview_1_tab_1);
    lv_label_set_text(Heater_tabview_1_tab_1_label, "");

    //Write codes Heater_btn_1
    ui->Heater_btn_1 = lv_btn_create(ui->Heater);
    ui->Heater_btn_1_label = lv_label_create(ui->Heater_btn_1);
    lv_label_set_text(ui->Heater_btn_1_label, "浴  霸");
    lv_label_set_long_mode(ui->Heater_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_btn_1, 70, 25);
    lv_obj_set_size(ui->Heater_btn_1, 93, 33);

    //Write style for Heater_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_HeatLight
    ui->Heater_HeatLight = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_HeatLight, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_HeatLight, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\light_on.png");
#else
    lv_img_set_src(ui->Heater_HeatLight, "S:/sdfile/EXT_RESERVED/uipackres/ui/light_on.png");
#endif
    lv_img_set_pivot(ui->Heater_HeatLight, 50,50);
    lv_img_set_angle(ui->Heater_HeatLight, 0);
    lv_obj_set_pos(ui->Heater_HeatLight, 213, 182);
    lv_obj_set_size(ui->Heater_HeatLight, 295, 164);

    //Write style for Heater_HeatLight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_HeatLight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_HeatLight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatLight, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_HeatLight, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_HeatDev
    ui->Heater_HeatDev = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_HeatDev, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_HeatDev, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\dev.png");
#else
    lv_img_set_src(ui->Heater_HeatDev, "S:/sdfile/EXT_RESERVED/uipackres/ui/dev.png");
#endif
    lv_img_set_pivot(ui->Heater_HeatDev, 50,50);
    lv_img_set_angle(ui->Heater_HeatDev, 0);
    lv_obj_set_pos(ui->Heater_HeatDev, 213, 182);
    lv_obj_set_size(ui->Heater_HeatDev, 295, 164);

    //Write style for Heater_HeatDev, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_HeatDev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_HeatDev, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatDev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_HeatDev, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_LightBtn
    ui->Heater_LightBtn = lv_btn_create(ui->Heater);
    ui->Heater_LightBtn_label = lv_label_create(ui->Heater_LightBtn);
    lv_label_set_text(ui->Heater_LightBtn_label, "");
    lv_label_set_long_mode(ui->Heater_LightBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_LightBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_LightBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_LightBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_LightBtn, 40, 569);
    lv_obj_set_size(ui->Heater_LightBtn, 310, 76);

    //Write style for Heater_LightBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_LightBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_LightBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_LightBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_LightBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_LightBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_LightBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_LightBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_LightBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_LightBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_LightBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_LightOffImg
    ui->Heater_LightOffImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_LightOffImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_LightOffImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\lightOffBtn.png");
#else
    lv_img_set_src(ui->Heater_LightOffImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/lightOffBtn.png");
#endif
    lv_img_set_pivot(ui->Heater_LightOffImg, 50,50);
    lv_img_set_angle(ui->Heater_LightOffImg, 0);
    lv_obj_set_pos(ui->Heater_LightOffImg, 174, 575);
    lv_obj_set_size(ui->Heater_LightOffImg, 50, 67);

    //Write style for Heater_LightOffImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_LightOffImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_LightOffImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_LightOffImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_LightOffImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_LightOnImg
    ui->Heater_LightOnImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_LightOnImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_LightOnImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\lightOnBtn.png");
#else
    lv_img_set_src(ui->Heater_LightOnImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/lightOnBtn.png");
#endif
    lv_img_set_pivot(ui->Heater_LightOnImg, 50,50);
    lv_img_set_angle(ui->Heater_LightOnImg, 0);
    lv_obj_set_pos(ui->Heater_LightOnImg, 174, 575);
    lv_obj_set_size(ui->Heater_LightOnImg, 50, 67);

    //Write style for Heater_LightOnImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_LightOnImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_LightOnImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_LightOnImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_LightOnImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_IdleBtn
    ui->Heater_IdleBtn = lv_btn_create(ui->Heater);
    ui->Heater_IdleBtn_label = lv_label_create(ui->Heater_IdleBtn);
    lv_label_set_text(ui->Heater_IdleBtn_label, "");
    lv_label_set_long_mode(ui->Heater_IdleBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_IdleBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_IdleBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_IdleBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_IdleBtn, 370, 569);
    lv_obj_set_size(ui->Heater_IdleBtn, 310, 76);

    //Write style for Heater_IdleBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_IdleBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_IdleBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_IdleBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_IdleBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_IdleBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_IdleBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_IdleBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_IdleBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Heater_IdleBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->Heater_IdleBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->Heater_IdleBtn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_IdleBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->Heater_IdleBtn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Heater_IdleBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Heater_IdleBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Heater_IdleBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for Heater_IdleBtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Heater_IdleBtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Heater_IdleBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_IdleBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->Heater_IdleBtn, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Heater_IdleBtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Heater_IdleBtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Heater_IdleBtn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->Heater_IdleBtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes Heater_IdleImg
    ui->Heater_IdleImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_IdleImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_IdleImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\idle_btn.png");
#else
    lv_img_set_src(ui->Heater_IdleImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/idle_btn.png");
#endif
    lv_img_set_pivot(ui->Heater_IdleImg, 50,50);
    lv_img_set_angle(ui->Heater_IdleImg, 0);
    lv_obj_set_pos(ui->Heater_IdleImg, 501, 569);
    lv_obj_set_size(ui->Heater_IdleImg, 50, 67);

    //Write style for Heater_IdleImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_IdleImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_IdleImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_IdleImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_IdleImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_VentilateBtn
    ui->Heater_VentilateBtn = lv_btn_create(ui->Heater);
    ui->Heater_VentilateBtn_label = lv_label_create(ui->Heater_VentilateBtn);
    lv_label_set_text(ui->Heater_VentilateBtn_label, "");
    lv_label_set_long_mode(ui->Heater_VentilateBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_VentilateBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_VentilateBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_VentilateBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_VentilateBtn, 370, 476);
    lv_obj_set_size(ui->Heater_VentilateBtn, 145, 76);

    //Write style for Heater_VentilateBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_VentilateBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_VentilateBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_VentilateBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_VentilateBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_VentilateBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_VentilateBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_VentilateBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_VentilateBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_VentilateBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_VentilateBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Heater_VentilateBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->Heater_VentilateBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->Heater_VentilateBtn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_VentilateBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->Heater_VentilateBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->Heater_VentilateBtn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Heater_VentilateBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Heater_VentilateBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Heater_VentilateBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Heater_VentilateBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes Heater_VentilateImg
    ui->Heater_VentilateImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_VentilateImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_VentilateImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\venBtn.png");
#else
    lv_img_set_src(ui->Heater_VentilateImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/venBtn.png");
#endif
    lv_img_set_pivot(ui->Heater_VentilateImg, 50,50);
    lv_img_set_angle(ui->Heater_VentilateImg, 0);
    lv_obj_set_pos(ui->Heater_VentilateImg, 419, 481);
    lv_obj_set_size(ui->Heater_VentilateImg, 50, 67);

    //Write style for Heater_VentilateImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_VentilateImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_VentilateImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_VentilateImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_VentilateImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_HeatLowBtn
    ui->Heater_HeatLowBtn = lv_btn_create(ui->Heater);
    ui->Heater_HeatLowBtn_label = lv_label_create(ui->Heater_HeatLowBtn);
    lv_label_set_text(ui->Heater_HeatLowBtn_label, "");
    lv_label_set_long_mode(ui->Heater_HeatLowBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_HeatLowBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_HeatLowBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_HeatLowBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_HeatLowBtn, 204, 473);
    lv_obj_set_size(ui->Heater_HeatLowBtn, 145, 76);

    //Write style for Heater_HeatLowBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_HeatLowBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_HeatLowBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_HeatLowBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_HeatLowBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatLowBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_HeatLowBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_HeatLowBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_HeatLowBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_HeatLowBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_HeatLowBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Heater_HeatLowBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->Heater_HeatLowBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->Heater_HeatLowBtn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_HeatLowBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->Heater_HeatLowBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->Heater_HeatLowBtn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Heater_HeatLowBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Heater_HeatLowBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Heater_HeatLowBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Heater_HeatLowBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes Heater_HeatLowImg
    ui->Heater_HeatLowImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_HeatLowImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_HeatLowImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\HeatLBtn.png");
#else
    lv_img_set_src(ui->Heater_HeatLowImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/HeatLBtn.png");
#endif
    lv_img_set_pivot(ui->Heater_HeatLowImg, 50,50);
    lv_img_set_angle(ui->Heater_HeatLowImg, 0);
    lv_obj_set_pos(ui->Heater_HeatLowImg, 260, 476);
    lv_obj_set_size(ui->Heater_HeatLowImg, 50, 67);

    //Write style for Heater_HeatLowImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_HeatLowImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_HeatLowImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatLowImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_HeatLowImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_WindBtn
    ui->Heater_WindBtn = lv_btn_create(ui->Heater);
    ui->Heater_WindBtn_label = lv_label_create(ui->Heater_WindBtn);
    lv_label_set_text(ui->Heater_WindBtn_label, "");
    lv_label_set_long_mode(ui->Heater_WindBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_WindBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_WindBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_WindBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_WindBtn, 535, 476);
    lv_obj_set_size(ui->Heater_WindBtn, 145, 76);

    //Write style for Heater_WindBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_WindBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_WindBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_WindBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_WindBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_WindBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_WindBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_WindBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_WindBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_WindBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_WindBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Heater_WindBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->Heater_WindBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->Heater_WindBtn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_WindBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->Heater_WindBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->Heater_WindBtn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Heater_WindBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Heater_WindBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Heater_WindBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Heater_WindBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes Heater_WindImg
    ui->Heater_WindImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_WindImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_WindImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\fan_btn.png");
#else
    lv_img_set_src(ui->Heater_WindImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/fan_btn.png");
#endif
    lv_img_set_pivot(ui->Heater_WindImg, 50,50);
    lv_img_set_angle(ui->Heater_WindImg, 0);
    lv_obj_set_pos(ui->Heater_WindImg, 585, 476);
    lv_obj_set_size(ui->Heater_WindImg, 50, 67);

    //Write style for Heater_WindImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_WindImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_WindImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_WindImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_WindImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_HeatHighBtn
    ui->Heater_HeatHighBtn = lv_btn_create(ui->Heater);
    ui->Heater_HeatHighBtn_label = lv_label_create(ui->Heater_HeatHighBtn);
    lv_label_set_text(ui->Heater_HeatHighBtn_label, "");
    lv_label_set_long_mode(ui->Heater_HeatHighBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_HeatHighBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_HeatHighBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_HeatHighBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_HeatHighBtn, 40, 473);
    lv_obj_set_size(ui->Heater_HeatHighBtn, 145, 76);

    //Write style for Heater_HeatHighBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_HeatHighBtn, 244, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Heater_HeatHighBtn, lv_color_hex(0x2f2d31), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Heater_HeatHighBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_HeatHighBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatHighBtn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_HeatHighBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_HeatHighBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_HeatHighBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_HeatHighBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_HeatHighBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Heater_HeatHighBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->Heater_HeatHighBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->Heater_HeatHighBtn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->Heater_HeatHighBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->Heater_HeatHighBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->Heater_HeatHighBtn, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Heater_HeatHighBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Heater_HeatHighBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Heater_HeatHighBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Heater_HeatHighBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes Heater_HeatHighImg
    ui->Heater_HeatHighImg = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_HeatHighImg, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_HeatHighImg, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\HeatHbtn.png");
#else
    lv_img_set_src(ui->Heater_HeatHighImg, "S:/sdfile/EXT_RESERVED/uipackres/ui/HeatHbtn.png");
#endif
    lv_img_set_pivot(ui->Heater_HeatHighImg, 50,50);
    lv_img_set_angle(ui->Heater_HeatHighImg, 0);
    lv_obj_set_pos(ui->Heater_HeatHighImg, 88, 476);
    lv_obj_set_size(ui->Heater_HeatHighImg, 60, 67);

    //Write style for Heater_HeatHighImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_HeatHighImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_HeatHighImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatHighImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_HeatHighImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_VentilateMode
    ui->Heater_VentilateMode = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_VentilateMode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_VentilateMode, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\venMode.png");
#else
    lv_img_set_src(ui->Heater_VentilateMode, "S:/sdfile/EXT_RESERVED/uipackres/ui/venMode.png");
#endif
    lv_img_set_pivot(ui->Heater_VentilateMode, 50,50);
    lv_img_set_angle(ui->Heater_VentilateMode, 0);
    lv_obj_set_pos(ui->Heater_VentilateMode, 210, 180);
    lv_obj_set_size(ui->Heater_VentilateMode, 295, 164);

    //Write style for Heater_VentilateMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_VentilateMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_VentilateMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_VentilateMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_VentilateMode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_heaterlowMode
    ui->Heater_heaterlowMode = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_heaterlowMode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_heaterlowMode, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\HeatLMode.png");
#else
    lv_img_set_src(ui->Heater_heaterlowMode, "S:/sdfile/EXT_RESERVED/uipackres/ui/HeatLMode.png");
#endif
    lv_img_set_pivot(ui->Heater_heaterlowMode, 50,50);
    lv_img_set_angle(ui->Heater_heaterlowMode, 0);
    lv_obj_set_pos(ui->Heater_heaterlowMode, 210, 180);
    lv_obj_set_size(ui->Heater_heaterlowMode, 295, 164);

    //Write style for Heater_heaterlowMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_heaterlowMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_heaterlowMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_heaterlowMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_heaterlowMode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_HeatHighMode
    ui->Heater_HeatHighMode = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_HeatHighMode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_HeatHighMode, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\HeatHMode.png");
#else
    lv_img_set_src(ui->Heater_HeatHighMode, "S:/sdfile/EXT_RESERVED/uipackres/ui/HeatHMode.png");
#endif
    lv_img_set_pivot(ui->Heater_HeatHighMode, 50,50);
    lv_img_set_angle(ui->Heater_HeatHighMode, 0);
    lv_obj_set_pos(ui->Heater_HeatHighMode, 210, 180);
    lv_obj_set_size(ui->Heater_HeatHighMode, 295, 164);

    //Write style for Heater_HeatHighMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_HeatHighMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_HeatHighMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_HeatHighMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_HeatHighMode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_WindMode
    ui->Heater_WindMode = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_WindMode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_WindMode, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\fan_mode.png");
#else
    lv_img_set_src(ui->Heater_WindMode, "S:/sdfile/EXT_RESERVED/uipackres/ui/fan_mode.png");
#endif
    lv_img_set_pivot(ui->Heater_WindMode, 50,50);
    lv_img_set_angle(ui->Heater_WindMode, 0);
    lv_obj_set_pos(ui->Heater_WindMode, 210, 180);
    lv_obj_set_size(ui->Heater_WindMode, 295, 164);

    //Write style for Heater_WindMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_WindMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_WindMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_WindMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_WindMode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_idleMode
    ui->Heater_idleMode = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_idleMode, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Heater_idleMode, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\idle_mode.png");
#else
    lv_img_set_src(ui->Heater_idleMode, "S:/sdfile/EXT_RESERVED/uipackres/ui/idle_mode.png");
#endif
    lv_img_set_pivot(ui->Heater_idleMode, 50,50);
    lv_img_set_angle(ui->Heater_idleMode, 0);
    lv_obj_set_pos(ui->Heater_idleMode, 210, 180);
    lv_obj_set_size(ui->Heater_idleMode, 295, 164);

    //Write style for Heater_idleMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_idleMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_idleMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_idleMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_idleMode, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_btn_2
    ui->Heater_btn_2 = lv_btn_create(ui->Heater);
    ui->Heater_btn_2_label = lv_label_create(ui->Heater_btn_2);
    lv_label_set_text(ui->Heater_btn_2_label, "");
    lv_label_set_long_mode(ui->Heater_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Heater_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Heater_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Heater_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Heater_btn_2, -8, -11);
    lv_obj_set_size(ui->Heater_btn_2, 238, 106);

    //Write style for Heater_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Heater_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Heater_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Heater_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Heater_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Heater_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Heater_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Heater_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Heater_img_1
    ui->Heater_img_1 = lv_img_create(ui->Heater);
    lv_obj_add_flag(ui->Heater_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Heater_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Heater_img_1, 50,50);
    lv_img_set_angle(ui->Heater_img_1, 0);
    lv_obj_set_pos(ui->Heater_img_1, 43, 28);
    lv_obj_set_size(ui->Heater_img_1, 14, 24);

    //Write style for Heater_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Heater_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Heater_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Heater_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Heater_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Heater.


    //Update current screen layout.
    lv_obj_update_layout(ui->Heater);

    //Init events for screen.
    events_init_Heater(ui);
}
