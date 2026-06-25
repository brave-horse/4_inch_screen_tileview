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



void setup_scr_AirCondition(lv_ui *ui)
{
    //Write codes AirCondition
    ui->AirCondition = lv_obj_create(NULL);
    lv_obj_set_size(ui->AirCondition, 720, 720);
    lv_obj_set_scrollbar_mode(ui->AirCondition, LV_SCROLLBAR_MODE_OFF);

    //Write style for AirCondition, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->AirCondition, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->AirCondition, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->AirCondition, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_tabview_1
    ui->AirCondition_tabview_1 = lv_tabview_create(ui->AirCondition, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->AirCondition_tabview_1, 0, 0);
    lv_obj_set_size(ui->AirCondition_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->AirCondition_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for AirCondition_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->AirCondition_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->AirCondition_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->AirCondition_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->AirCondition_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->AirCondition_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->AirCondition_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->AirCondition_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->AirCondition_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->AirCondition_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->AirCondition_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_AirCondition_tabview_1_extra_btnm_main_default
    static lv_style_t style_AirCondition_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_AirCondition_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_AirCondition_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_AirCondition_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_AirCondition_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_AirCondition_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_AirCondition_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->AirCondition_tabview_1), &style_AirCondition_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_AirCondition_tabview_1_extra_btnm_items_default
    static lv_style_t style_AirCondition_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_AirCondition_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_AirCondition_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_AirCondition_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_AirCondition_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->AirCondition_tabview_1), &style_AirCondition_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_AirCondition_tabview_1_extra_btnm_items_checked
    static lv_style_t style_AirCondition_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_AirCondition_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_AirCondition_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_AirCondition_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_AirCondition_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_AirCondition_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_AirCondition_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_AirCondition_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_AirCondition_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_AirCondition_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->AirCondition_tabview_1), &style_AirCondition_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->AirCondition_tabview_1_tab_1 = lv_tabview_add_tab(ui->AirCondition_tabview_1,"");
    lv_obj_t * AirCondition_tabview_1_tab_1_label = lv_label_create(ui->AirCondition_tabview_1_tab_1);
    lv_label_set_text(AirCondition_tabview_1_tab_1_label, "");

    //Write codes AirCondition_cont_1
    ui->AirCondition_cont_1 = lv_obj_create(ui->AirCondition);
    lv_obj_set_pos(ui->AirCondition_cont_1, 0, 85);
    lv_obj_set_size(ui->AirCondition_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->AirCondition_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for AirCondition_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->AirCondition_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->AirCondition_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->AirCondition_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->AirCondition_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_btn_1
    ui->AirCondition_btn_1 = lv_btn_create(ui->AirCondition);
    ui->AirCondition_btn_1_label = lv_label_create(ui->AirCondition_btn_1);
    lv_label_set_text(ui->AirCondition_btn_1_label, "空  调");
    lv_label_set_long_mode(ui->AirCondition_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->AirCondition_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->AirCondition_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->AirCondition_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->AirCondition_btn_1, 71, 25);
    lv_obj_set_size(ui->AirCondition_btn_1, 92, 32);

    //Write style for AirCondition_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->AirCondition_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->AirCondition_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->AirCondition_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->AirCondition_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->AirCondition_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->AirCondition_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->AirCondition_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_FabCurtianLeft
    ui->AirCondition_FabCurtianLeft = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_FabCurtianLeft, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_FabCurtianLeft, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\AirCondiImg.png");
#else
    lv_img_set_src(ui->AirCondition_FabCurtianLeft, "S:/sdfile/EXT_RESERVED/uipackres/ui/AirCondiImg.png");
#endif
    lv_img_set_pivot(ui->AirCondition_FabCurtianLeft, 50,50);
    lv_img_set_angle(ui->AirCondition_FabCurtianLeft, 0);
    lv_obj_set_pos(ui->AirCondition_FabCurtianLeft, 201, 138);
    lv_obj_set_size(ui->AirCondition_FabCurtianLeft, 332, 140);

    //Write style for AirCondition_FabCurtianLeft, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_FabCurtianLeft, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_FabCurtianLeft, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_FabCurtianLeft, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACBtn
    ui->AirCondition_ACBtn = lv_imgbtn_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACBtn, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->AirCondition_ACBtn, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACOff.png", NULL);
    lv_imgbtn_set_src(ui->AirCondition_ACBtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACOn.png", NULL);
#else
    lv_imgbtn_set_src(ui->AirCondition_ACBtn, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACOff.png", NULL);
    lv_imgbtn_set_src(ui->AirCondition_ACBtn, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACOn.png", NULL);
#endif
    ui->AirCondition_ACBtn_label = lv_label_create(ui->AirCondition_ACBtn);
    lv_label_set_text(ui->AirCondition_ACBtn_label, "");
    lv_label_set_long_mode(ui->AirCondition_ACBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->AirCondition_ACBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->AirCondition_ACBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->AirCondition_ACBtn, 310, 534);
    lv_obj_set_size(ui->AirCondition_ACBtn, 109, 109);

    //Write style for AirCondition_ACBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->AirCondition_ACBtn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->AirCondition_ACBtn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->AirCondition_ACBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACBtn, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for AirCondition_ACBtn, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->AirCondition_ACBtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->AirCondition_ACBtn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for AirCondition_ACBtn, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->AirCondition_ACBtn, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->AirCondition_ACBtn, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for AirCondition_ACBtn, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACBtn, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->AirCondition_ACBtn, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes AirCondition_ACSpeedAuto
    ui->AirCondition_ACSpeedAuto = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACSpeedAuto, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACSpeedAuto, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeedAuto.png");
#else
    lv_img_set_src(ui->AirCondition_ACSpeedAuto, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeedAuto.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACSpeedAuto, 50,50);
    lv_img_set_angle(ui->AirCondition_ACSpeedAuto, 0);
    lv_obj_set_pos(ui->AirCondition_ACSpeedAuto, 574, 534);
    lv_obj_set_size(ui->AirCondition_ACSpeedAuto, 109, 109);

    //Write style for AirCondition_ACSpeedAuto, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACSpeedAuto, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACSpeedAuto, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACSpeedAuto, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACSpeedAuto, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACSpeed3
    ui->AirCondition_ACSpeed3 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACSpeed3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACSpeed3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed3.png");
#else
    lv_img_set_src(ui->AirCondition_ACSpeed3, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed3.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACSpeed3, 50,50);
    lv_img_set_angle(ui->AirCondition_ACSpeed3, 0);
    lv_obj_set_pos(ui->AirCondition_ACSpeed3, 574, 534);
    lv_obj_set_size(ui->AirCondition_ACSpeed3, 109, 109);

    //Write style for AirCondition_ACSpeed3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACSpeed3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACSpeed3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACSpeed3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACSpeed3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACSpeed2
    ui->AirCondition_ACSpeed2 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACSpeed2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACSpeed2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed2.png");
#else
    lv_img_set_src(ui->AirCondition_ACSpeed2, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed2.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACSpeed2, 50,50);
    lv_img_set_angle(ui->AirCondition_ACSpeed2, 0);
    lv_obj_set_pos(ui->AirCondition_ACSpeed2, 574, 534);
    lv_obj_set_size(ui->AirCondition_ACSpeed2, 109, 109);

    //Write style for AirCondition_ACSpeed2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACSpeed2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACSpeed2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACSpeed2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACSpeed2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACSpeed1
    ui->AirCondition_ACSpeed1 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACSpeed1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACSpeed1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACSpeed1.png");
#else
    lv_img_set_src(ui->AirCondition_ACSpeed1, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACSpeed1.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACSpeed1, 50,50);
    lv_img_set_angle(ui->AirCondition_ACSpeed1, 0);
    lv_obj_set_pos(ui->AirCondition_ACSpeed1, 574, 534);
    lv_obj_set_size(ui->AirCondition_ACSpeed1, 109, 109);

    //Write style for AirCondition_ACSpeed1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACSpeed1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACSpeed1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACSpeed1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACSpeed1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_AcCool
    ui->AirCondition_AcCool = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_AcCool, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_AcCool, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\AcCool.png");
#else
    lv_img_set_src(ui->AirCondition_AcCool, "S:/sdfile/EXT_RESERVED/uipackres/ui/AcCool.png");
#endif
    lv_img_set_pivot(ui->AirCondition_AcCool, 50,50);
    lv_img_set_angle(ui->AirCondition_AcCool, 0);
    lv_obj_set_pos(ui->AirCondition_AcCool, 50, 538);
    lv_obj_set_size(ui->AirCondition_AcCool, 109, 109);

    //Write style for AirCondition_AcCool, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_AcCool, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_AcCool, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_AcCool, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_AcCool, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACFan
    ui->AirCondition_ACFan = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACFan, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACFan, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACFan.png");
#else
    lv_img_set_src(ui->AirCondition_ACFan, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACFan.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACFan, 50,50);
    lv_img_set_angle(ui->AirCondition_ACFan, 0);
    lv_obj_set_pos(ui->AirCondition_ACFan, 50, 538);
    lv_obj_set_size(ui->AirCondition_ACFan, 109, 109);

    //Write style for AirCondition_ACFan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACFan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACFan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACFan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACFan, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACHot
    ui->AirCondition_ACHot = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACHot, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACHot, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACHot.png");
#else
    lv_img_set_src(ui->AirCondition_ACHot, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACHot.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACHot, 50,50);
    lv_img_set_angle(ui->AirCondition_ACHot, 0);
    lv_obj_set_pos(ui->AirCondition_ACHot, 50, 538);
    lv_obj_set_size(ui->AirCondition_ACHot, 109, 109);

    //Write style for AirCondition_ACHot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACHot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACHot, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACHot, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACHot, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_ACDry
    ui->AirCondition_ACDry = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_ACDry, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_ACDry, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ACDry.png");
#else
    lv_img_set_src(ui->AirCondition_ACDry, "S:/sdfile/EXT_RESERVED/uipackres/ui/ACDry.png");
#endif
    lv_img_set_pivot(ui->AirCondition_ACDry, 50,50);
    lv_img_set_angle(ui->AirCondition_ACDry, 0);
    lv_obj_set_pos(ui->AirCondition_ACDry, 50, 538);
    lv_obj_set_size(ui->AirCondition_ACDry, 109, 109);

    //Write style for AirCondition_ACDry, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_ACDry, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_ACDry, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_ACDry, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_ACDry, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_AcSpd3
    ui->AirCondition_AcSpd3 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_AcSpd3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_AcSpd3, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\AcSpd3.png");
#else
    lv_img_set_src(ui->AirCondition_AcSpd3, "S:/sdfile/EXT_RESERVED/uipackres/ui/AcSpd3.png");
#endif
    lv_img_set_pivot(ui->AirCondition_AcSpd3, 50,50);
    lv_img_set_angle(ui->AirCondition_AcSpd3, 0);
    lv_obj_set_pos(ui->AirCondition_AcSpd3, 192, 267);
    lv_obj_set_size(ui->AirCondition_AcSpd3, 349, 94);

    //Write style for AirCondition_AcSpd3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_AcSpd3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_AcSpd3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_AcSpd3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_AcSpd3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_AcSpd2
    ui->AirCondition_AcSpd2 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_AcSpd2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_AcSpd2, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\AcSpd2.png");
#else
    lv_img_set_src(ui->AirCondition_AcSpd2, "S:/sdfile/EXT_RESERVED/uipackres/ui/AcSpd2.png");
#endif
    lv_img_set_pivot(ui->AirCondition_AcSpd2, 50,50);
    lv_img_set_angle(ui->AirCondition_AcSpd2, 0);
    lv_obj_set_pos(ui->AirCondition_AcSpd2, 192, 267);
    lv_obj_set_size(ui->AirCondition_AcSpd2, 349, 94);

    //Write style for AirCondition_AcSpd2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_AcSpd2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_AcSpd2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_AcSpd2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_AcSpd2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_AcSpd1
    ui->AirCondition_AcSpd1 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_AcSpd1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->AirCondition_AcSpd1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\AcSpd1.png");
#else
    lv_img_set_src(ui->AirCondition_AcSpd1, "S:/sdfile/EXT_RESERVED/uipackres/ui/AcSpd1.png");
#endif
    lv_img_set_pivot(ui->AirCondition_AcSpd1, 50,50);
    lv_img_set_angle(ui->AirCondition_AcSpd1, 0);
    lv_obj_set_pos(ui->AirCondition_AcSpd1, 192, 267);
    lv_obj_set_size(ui->AirCondition_AcSpd1, 349, 94);

    //Write style for AirCondition_AcSpd1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_AcSpd1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_AcSpd1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_AcSpd1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_AcSpd1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_img_1
    ui->AirCondition_img_1 = lv_img_create(ui->AirCondition);
    lv_obj_add_flag(ui->AirCondition_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->AirCondition_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->AirCondition_img_1, 50,50);
    lv_img_set_angle(ui->AirCondition_img_1, 0);
    lv_obj_set_pos(ui->AirCondition_img_1, 43, 28);
    lv_obj_set_size(ui->AirCondition_img_1, 14, 24);

    //Write style for AirCondition_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->AirCondition_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->AirCondition_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->AirCondition_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes AirCondition_btn_2
    ui->AirCondition_btn_2 = lv_btn_create(ui->AirCondition);
    ui->AirCondition_btn_2_label = lv_label_create(ui->AirCondition_btn_2);
    lv_label_set_text(ui->AirCondition_btn_2_label, "");
    lv_label_set_long_mode(ui->AirCondition_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->AirCondition_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->AirCondition_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->AirCondition_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->AirCondition_btn_2, -8, -10);
    lv_obj_set_size(ui->AirCondition_btn_2, 241, 103);

    //Write style for AirCondition_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->AirCondition_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->AirCondition_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->AirCondition_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->AirCondition_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->AirCondition_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->AirCondition_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->AirCondition_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->AirCondition_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of AirCondition.


    //Update current screen layout.
    lv_obj_update_layout(ui->AirCondition);

    //Init events for screen.
    events_init_AirCondition(ui);
}
