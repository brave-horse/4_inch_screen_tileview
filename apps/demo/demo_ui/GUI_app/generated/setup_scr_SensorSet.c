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



void setup_scr_SensorSet(lv_ui *ui)
{
    //Write codes SensorSet
    ui->SensorSet = lv_obj_create(NULL);
    lv_obj_set_size(ui->SensorSet, 720, 720);
    lv_obj_set_scrollbar_mode(ui->SensorSet, LV_SCROLLBAR_MODE_OFF);

    //Write style for SensorSet, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_tabview_1
    ui->SensorSet_tabview_1 = lv_tabview_create(ui->SensorSet, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->SensorSet_tabview_1, 0, 0);
    lv_obj_set_size(ui->SensorSet_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->SensorSet_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for SensorSet_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->SensorSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_SensorSet_tabview_1_extra_btnm_main_default
    static lv_style_t style_SensorSet_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_SensorSet_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_SensorSet_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_SensorSet_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_SensorSet_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_SensorSet_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_SensorSet_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->SensorSet_tabview_1), &style_SensorSet_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_SensorSet_tabview_1_extra_btnm_items_default
    static lv_style_t style_SensorSet_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_SensorSet_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_SensorSet_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_SensorSet_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_SensorSet_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->SensorSet_tabview_1), &style_SensorSet_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_SensorSet_tabview_1_extra_btnm_items_checked
    static lv_style_t style_SensorSet_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_SensorSet_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_SensorSet_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_SensorSet_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_SensorSet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_SensorSet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_SensorSet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_SensorSet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_SensorSet_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_SensorSet_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->SensorSet_tabview_1), &style_SensorSet_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->SensorSet_tabview_1_tab_1 = lv_tabview_add_tab(ui->SensorSet_tabview_1,"");
    lv_obj_t * SensorSet_tabview_1_tab_1_label = lv_label_create(ui->SensorSet_tabview_1_tab_1);
    lv_label_set_text(SensorSet_tabview_1_tab_1_label, "");

    //Write codes SensorSet_cont_2
    ui->SensorSet_cont_2 = lv_obj_create(ui->SensorSet);
    lv_obj_set_pos(ui->SensorSet_cont_2, 11, 97);
    lv_obj_set_size(ui->SensorSet_cont_2, 720, 141);
    lv_obj_set_scrollbar_mode(ui->SensorSet_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for SensorSet_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_cont_2, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_cont_2, lv_color_hex(0x4a3a3a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_5
    ui->SensorSet_label_5 = lv_label_create(ui->SensorSet_cont_2);
    lv_label_set_text(ui->SensorSet_label_5, "温度");
    lv_label_set_long_mode(ui->SensorSet_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_5, 7, 8);
    lv_obj_set_size(ui->SensorSet_label_5, 108, 33);

    //Write style for SensorSet_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_cont_3
    ui->SensorSet_cont_3 = lv_obj_create(ui->SensorSet_cont_2);
    lv_obj_set_pos(ui->SensorSet_cont_3, 31, 54);
    lv_obj_set_size(ui->SensorSet_cont_3, 648, 49);
    lv_obj_set_scrollbar_mode(ui->SensorSet_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for SensorSet_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_cont_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->SensorSet_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->SensorSet_cont_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->SensorSet_cont_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_cont_3, lv_color_hex(0x8f8181), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_6
    ui->SensorSet_label_6 = lv_label_create(ui->SensorSet_cont_3);
    lv_label_set_text(ui->SensorSet_label_6, "型号");
    lv_label_set_long_mode(ui->SensorSet_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_6, 4, 8);
    lv_obj_set_size(ui->SensorSet_label_6, 100, 32);

    //Write style for SensorSet_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_btn_11
    ui->SensorSet_btn_11 = lv_btn_create(ui->SensorSet_cont_3);
    ui->SensorSet_btn_11_label = lv_label_create(ui->SensorSet_btn_11);
    lv_label_set_text(ui->SensorSet_btn_11_label, "");
    lv_label_set_long_mode(ui->SensorSet_btn_11_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->SensorSet_btn_11_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->SensorSet_btn_11, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->SensorSet_btn_11_label, LV_PCT(100));
    lv_obj_set_pos(ui->SensorSet_btn_11, 586, 11);
    lv_obj_set_size(ui->SensorSet_btn_11, 26, 24);

    //Write style for SensorSet_btn_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet_btn_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_btn_11, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_btn_11, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->SensorSet_btn_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_btn_11, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_btn_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_btn_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_btn_11, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_btn_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_btn_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_7
    ui->SensorSet_label_7 = lv_label_create(ui->SensorSet_cont_3);
    lv_label_set_text(ui->SensorSet_label_7, "温度");
    lv_label_set_long_mode(ui->SensorSet_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_7, 487, 13);
    lv_obj_set_size(ui->SensorSet_label_7, 100, 32);

    //Write style for SensorSet_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_cont_4
    ui->SensorSet_cont_4 = lv_obj_create(ui->SensorSet);
    lv_obj_set_pos(ui->SensorSet_cont_4, 11, 249);
    lv_obj_set_size(ui->SensorSet_cont_4, 720, 141);
    lv_obj_set_scrollbar_mode(ui->SensorSet_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for SensorSet_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_cont_4, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_cont_4, lv_color_hex(0x4a3a3a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_10
    ui->SensorSet_label_10 = lv_label_create(ui->SensorSet_cont_4);
    lv_label_set_text(ui->SensorSet_label_10, "湿度");
    lv_label_set_long_mode(ui->SensorSet_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_10, 8, 7);
    lv_obj_set_size(ui->SensorSet_label_10, 108, 33);

    //Write style for SensorSet_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_cont_5
    ui->SensorSet_cont_5 = lv_obj_create(ui->SensorSet_cont_4);
    lv_obj_set_pos(ui->SensorSet_cont_5, 31, 53);
    lv_obj_set_size(ui->SensorSet_cont_5, 648, 49);
    lv_obj_set_scrollbar_mode(ui->SensorSet_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for SensorSet_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_cont_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->SensorSet_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->SensorSet_cont_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->SensorSet_cont_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_cont_5, lv_color_hex(0x8f8181), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_9
    ui->SensorSet_label_9 = lv_label_create(ui->SensorSet_cont_5);
    lv_label_set_text(ui->SensorSet_label_9, "型号");
    lv_label_set_long_mode(ui->SensorSet_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_9, 4, 8);
    lv_obj_set_size(ui->SensorSet_label_9, 100, 32);

    //Write style for SensorSet_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_9, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_btn_12
    ui->SensorSet_btn_12 = lv_btn_create(ui->SensorSet_cont_5);
    ui->SensorSet_btn_12_label = lv_label_create(ui->SensorSet_btn_12);
    lv_label_set_text(ui->SensorSet_btn_12_label, "");
    lv_label_set_long_mode(ui->SensorSet_btn_12_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->SensorSet_btn_12_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->SensorSet_btn_12, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->SensorSet_btn_12_label, LV_PCT(100));
    lv_obj_set_pos(ui->SensorSet_btn_12, 586, 11);
    lv_obj_set_size(ui->SensorSet_btn_12, 26, 24);

    //Write style for SensorSet_btn_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet_btn_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->SensorSet_btn_12, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->SensorSet_btn_12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->SensorSet_btn_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_btn_12, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_btn_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_btn_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_btn_12, &lv_font_ZiTiQuanWeiJunHeiW22_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_btn_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_btn_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_label_8
    ui->SensorSet_label_8 = lv_label_create(ui->SensorSet_cont_5);
    lv_label_set_text(ui->SensorSet_label_8, "湿度");
    lv_label_set_long_mode(ui->SensorSet_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->SensorSet_label_8, 487, 13);
    lv_obj_set_size(ui->SensorSet_label_8, 100, 32);

    //Write style for SensorSet_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_label_8, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_btn_1
    ui->SensorSet_btn_1 = lv_btn_create(ui->SensorSet);
    ui->SensorSet_btn_1_label = lv_label_create(ui->SensorSet_btn_1);
    lv_label_set_text(ui->SensorSet_btn_1_label, "传感器配置");
    lv_label_set_long_mode(ui->SensorSet_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->SensorSet_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->SensorSet_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->SensorSet_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->SensorSet_btn_1, 70, 24);
    lv_obj_set_size(ui->SensorSet_btn_1, 186, 32);

    //Write style for SensorSet_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->SensorSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_img_1
    ui->SensorSet_img_1 = lv_img_create(ui->SensorSet);
    lv_obj_add_flag(ui->SensorSet_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->SensorSet_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->SensorSet_img_1, 50,50);
    lv_img_set_angle(ui->SensorSet_img_1, 0);
    lv_obj_set_pos(ui->SensorSet_img_1, 43, 28);
    lv_obj_set_size(ui->SensorSet_img_1, 14, 24);

    //Write style for SensorSet_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->SensorSet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->SensorSet_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->SensorSet_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes SensorSet_btn_13
    ui->SensorSet_btn_13 = lv_btn_create(ui->SensorSet);
    ui->SensorSet_btn_13_label = lv_label_create(ui->SensorSet_btn_13);
    lv_label_set_text(ui->SensorSet_btn_13_label, "");
    lv_label_set_long_mode(ui->SensorSet_btn_13_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->SensorSet_btn_13_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->SensorSet_btn_13, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->SensorSet_btn_13_label, LV_PCT(100));
    lv_obj_set_pos(ui->SensorSet_btn_13, -6, -15);
    lv_obj_set_size(ui->SensorSet_btn_13, 272, 111);

    //Write style for SensorSet_btn_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->SensorSet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->SensorSet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->SensorSet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->SensorSet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->SensorSet_btn_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->SensorSet_btn_13, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->SensorSet_btn_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->SensorSet_btn_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of SensorSet.


    //Update current screen layout.
    lv_obj_update_layout(ui->SensorSet);

    //Init events for screen.
    events_init_SensorSet(ui);
}
