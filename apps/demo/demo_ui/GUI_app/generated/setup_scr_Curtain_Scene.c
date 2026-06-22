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



void setup_scr_Curtain_Scene(lv_ui *ui)
{
    //Write codes Curtain_Scene
    ui->Curtain_Scene = lv_obj_create(NULL);
    lv_obj_set_size(ui->Curtain_Scene, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Curtain_Scene, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_tabview_1
    ui->Curtain_Scene_tabview_1 = lv_tabview_create(ui->Curtain_Scene, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Curtain_Scene_tabview_1, 0, 0);
    lv_obj_set_size(ui->Curtain_Scene_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Curtain_Scene_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Curtain_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Curtain_Scene_tabview_1_extra_btnm_main_default
    static lv_style_t style_Curtain_Scene_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Curtain_Scene_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Curtain_Scene_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Curtain_Scene_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Curtain_Scene_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Curtain_Scene_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Curtain_Scene_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Curtain_Scene_tabview_1), &style_Curtain_Scene_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Curtain_Scene_tabview_1_extra_btnm_items_default
    static lv_style_t style_Curtain_Scene_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Curtain_Scene_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Curtain_Scene_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Curtain_Scene_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Curtain_Scene_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Curtain_Scene_tabview_1), &style_Curtain_Scene_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Curtain_Scene_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Curtain_Scene_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Curtain_Scene_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Curtain_Scene_tabview_1), &style_Curtain_Scene_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Curtain_Scene_tabview_1_tab_1 = lv_tabview_add_tab(ui->Curtain_Scene_tabview_1,"");
    lv_obj_t * Curtain_Scene_tabview_1_tab_1_label = lv_label_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_label_set_text(Curtain_Scene_tabview_1_tab_1_label, "");

    //Write codes Curtain_Scene_cont_12
    ui->Curtain_Scene_cont_12 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_12, 345, 400);
    lv_obj_set_size(ui->Curtain_Scene_cont_12, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_12, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_12, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_12, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_16
    ui->Curtain_Scene_label_16 = lv_label_create(ui->Curtain_Scene_cont_12);
    lv_label_set_text(ui->Curtain_Scene_label_16, "80%");
    lv_label_set_long_mode(ui->Curtain_Scene_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_16, 140, 130);
    lv_obj_set_size(ui->Curtain_Scene_label_16, 70, 35);

    //Write style for Curtain_Scene_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_16, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_12
    ui->Curtain_Scene_img_12 = lv_img_create(ui->Curtain_Scene_cont_12);
    lv_obj_add_flag(ui->Curtain_Scene_img_12, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_12, &_CuratianS4_alpha_59x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_12, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_12, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_12, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_12, 59, 31);

    //Write style for Curtain_Scene_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_cont_11
    ui->Curtain_Scene_cont_11 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_11, 0, 400);
    lv_obj_set_size(ui->Curtain_Scene_cont_11, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_11, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_11, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_11, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_15
    ui->Curtain_Scene_label_15 = lv_label_create(ui->Curtain_Scene_cont_11);
    lv_label_set_text(ui->Curtain_Scene_label_15, "60%");
    lv_label_set_long_mode(ui->Curtain_Scene_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_15, 140, 130);
    lv_obj_set_size(ui->Curtain_Scene_label_15, 65, 30);

    //Write style for Curtain_Scene_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_15, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_15, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_11
    ui->Curtain_Scene_img_11 = lv_img_create(ui->Curtain_Scene_cont_11);
    lv_obj_add_flag(ui->Curtain_Scene_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_11, &_CuratianS3_alpha_59x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_11, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_11, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_11, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_11, 59, 31);

    //Write style for Curtain_Scene_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_cont_10
    ui->Curtain_Scene_cont_10 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_10, 0, 200);
    lv_obj_set_size(ui->Curtain_Scene_cont_10, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_10, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_10, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_10, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_14
    ui->Curtain_Scene_label_14 = lv_label_create(ui->Curtain_Scene_cont_10);
    lv_label_set_text(ui->Curtain_Scene_label_14, "20%");
    lv_label_set_long_mode(ui->Curtain_Scene_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_14, 140, 130);
    lv_obj_set_size(ui->Curtain_Scene_label_14, 61, 35);

    //Write style for Curtain_Scene_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_14, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_14, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_10
    ui->Curtain_Scene_img_10 = lv_img_create(ui->Curtain_Scene_cont_10);
    lv_obj_add_flag(ui->Curtain_Scene_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_10, &_CuratianS1_alpha_59x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_10, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_10, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_10, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_10, 59, 31);

    //Write style for Curtain_Scene_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_cont_9
    ui->Curtain_Scene_cont_9 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_9, 344, 200);
    lv_obj_set_size(ui->Curtain_Scene_cont_9, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_9, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_9, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_9, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_13
    ui->Curtain_Scene_label_13 = lv_label_create(ui->Curtain_Scene_cont_9);
    lv_label_set_text(ui->Curtain_Scene_label_13, "40%");
    lv_label_set_long_mode(ui->Curtain_Scene_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_13, 140, 128);
    lv_obj_set_size(ui->Curtain_Scene_label_13, 67, 40);

    //Write style for Curtain_Scene_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_13, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_9
    ui->Curtain_Scene_img_9 = lv_img_create(ui->Curtain_Scene_cont_9);
    lv_obj_add_flag(ui->Curtain_Scene_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_9, &_CuratianS2_alpha_59x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_9, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_9, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_9, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_9, 59, 31);

    //Write style for Curtain_Scene_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_cont_8
    ui->Curtain_Scene_cont_8 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_8, 344, 1);
    lv_obj_set_size(ui->Curtain_Scene_cont_8, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_8, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_8, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_12
    ui->Curtain_Scene_label_12 = lv_label_create(ui->Curtain_Scene_cont_8);
    lv_label_set_text(ui->Curtain_Scene_label_12, "窗帘全关");
    lv_label_set_long_mode(ui->Curtain_Scene_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_12, 85, 127);
    lv_obj_set_size(ui->Curtain_Scene_label_12, 150, 40);

    //Write style for Curtain_Scene_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_12, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_8
    ui->Curtain_Scene_img_8 = lv_img_create(ui->Curtain_Scene_cont_8);
    lv_obj_add_flag(ui->Curtain_Scene_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_8, &_CurAllClose_alpha_53x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_8, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_8, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_8, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_8, 53, 31);

    //Write style for Curtain_Scene_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_cont_7
    ui->Curtain_Scene_cont_7 = lv_obj_create(ui->Curtain_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Curtain_Scene_cont_7, 0, 1);
    lv_obj_set_size(ui->Curtain_Scene_cont_7, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Curtain_Scene_cont_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for Curtain_Scene_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_cont_7, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Curtain_Scene_cont_7, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Curtain_Scene_cont_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_11
    ui->Curtain_Scene_label_11 = lv_label_create(ui->Curtain_Scene_cont_7);
    lv_label_set_text(ui->Curtain_Scene_label_11, "窗帘全开");
    lv_label_set_long_mode(ui->Curtain_Scene_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_11, 85, 130);
    lv_obj_set_size(ui->Curtain_Scene_label_11, 150, 40);

    //Write style for Curtain_Scene_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_11, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_img_7
    ui->Curtain_Scene_img_7 = lv_img_create(ui->Curtain_Scene_cont_7);
    lv_obj_add_flag(ui->Curtain_Scene_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Curtain_Scene_img_7, &_CurAllOpen_alpha_53x31);
    lv_img_set_pivot(ui->Curtain_Scene_img_7, 50,50);
    lv_img_set_angle(ui->Curtain_Scene_img_7, 0);
    lv_obj_set_pos(ui->Curtain_Scene_img_7, 135, 40);
    lv_obj_set_size(ui->Curtain_Scene_img_7, 53, 31);

    //Write style for Curtain_Scene_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Curtain_Scene_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Curtain_Scene_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Curtain_Scene_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Curtain_Scene_label_10
    ui->Curtain_Scene_label_10 = lv_label_create(ui->Curtain_Scene);
    lv_label_set_text(ui->Curtain_Scene_label_10, "窗帘情景");
    lv_label_set_long_mode(ui->Curtain_Scene_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Curtain_Scene_label_10, 43, 25);
    lv_obj_set_size(ui->Curtain_Scene_label_10, 125, 32);

    //Write style for Curtain_Scene_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Curtain_Scene_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Curtain_Scene_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Curtain_Scene_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Curtain_Scene_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Curtain_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Curtain_Scene.


    //Update current screen layout.
    lv_obj_update_layout(ui->Curtain_Scene);

}
