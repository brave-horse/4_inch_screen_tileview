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



void setup_scr_LanguageSet(lv_ui *ui)
{
    //Write codes LanguageSet
    ui->LanguageSet = lv_obj_create(NULL);
    lv_obj_set_size(ui->LanguageSet, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LanguageSet, LV_SCROLLBAR_MODE_OFF);

    //Write style for LanguageSet, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LanguageSet, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_tabview_1
    ui->LanguageSet_tabview_1 = lv_tabview_create(ui->LanguageSet, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->LanguageSet_tabview_1, 0, 0);
    lv_obj_set_size(ui->LanguageSet_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LanguageSet_tabview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for LanguageSet_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LanguageSet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LanguageSet_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LanguageSet_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LanguageSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LanguageSet_tabview_1_extra_btnm_main_default
    static lv_style_t style_LanguageSet_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_LanguageSet_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_LanguageSet_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_LanguageSet_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_LanguageSet_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_LanguageSet_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_LanguageSet_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LanguageSet_tabview_1), &style_LanguageSet_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LanguageSet_tabview_1_extra_btnm_items_default
    static lv_style_t style_LanguageSet_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_LanguageSet_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_LanguageSet_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_LanguageSet_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_LanguageSet_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LanguageSet_tabview_1), &style_LanguageSet_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_LanguageSet_tabview_1_extra_btnm_items_checked
    static lv_style_t style_LanguageSet_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_LanguageSet_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_LanguageSet_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_LanguageSet_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_LanguageSet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_LanguageSet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_LanguageSet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_LanguageSet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_LanguageSet_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_LanguageSet_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LanguageSet_tabview_1), &style_LanguageSet_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->LanguageSet_tabview_1_tab_1 = lv_tabview_add_tab(ui->LanguageSet_tabview_1,"       ");
    lv_obj_t * LanguageSet_tabview_1_tab_1_label = lv_label_create(ui->LanguageSet_tabview_1_tab_1);
    lv_label_set_text(LanguageSet_tabview_1_tab_1_label, "");

    //Write codes LanguageSet_cont_3
    ui->LanguageSet_cont_3 = lv_obj_create(ui->LanguageSet_tabview_1_tab_1);
    lv_obj_set_pos(ui->LanguageSet_cont_3, 12, -15);
    lv_obj_set_size(ui->LanguageSet_cont_3, 658, 90);
    lv_obj_set_scrollbar_mode(ui->LanguageSet_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for LanguageSet_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_cont_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->LanguageSet_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->LanguageSet_cont_3, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->LanguageSet_cont_3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_cont_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_label_16
    ui->LanguageSet_label_16 = lv_label_create(ui->LanguageSet_cont_3);
    lv_label_set_text(ui->LanguageSet_label_16, "中文(简体)");
    lv_label_set_long_mode(ui->LanguageSet_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LanguageSet_label_16, 0, 30);
    lv_obj_set_size(ui->LanguageSet_label_16, 148, 32);

    //Write style for LanguageSet_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_label_16, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_img_31
    ui->LanguageSet_img_31 = lv_img_create(ui->LanguageSet_cont_3);
    lv_obj_add_flag(ui->LanguageSet_img_31, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LanguageSet_img_31, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->LanguageSet_img_31, 0,0);
    lv_img_set_angle(ui->LanguageSet_img_31, 1800);
    lv_obj_set_pos(ui->LanguageSet_img_31, 625, 59);
    lv_obj_set_size(ui->LanguageSet_img_31, 14, 24);

    //Write style for LanguageSet_img_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->LanguageSet_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LanguageSet_img_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->LanguageSet_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LanguageSet_img_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_cont_4
    ui->LanguageSet_cont_4 = lv_obj_create(ui->LanguageSet_tabview_1_tab_1);
    lv_obj_set_pos(ui->LanguageSet_cont_4, 12, 75);
    lv_obj_set_size(ui->LanguageSet_cont_4, 658, 90);
    lv_obj_set_scrollbar_mode(ui->LanguageSet_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for LanguageSet_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_cont_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->LanguageSet_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->LanguageSet_cont_4, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->LanguageSet_cont_4, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_cont_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_label_15
    ui->LanguageSet_label_15 = lv_label_create(ui->LanguageSet_cont_4);
    lv_label_set_text(ui->LanguageSet_label_15, "English");
    lv_label_set_long_mode(ui->LanguageSet_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LanguageSet_label_15, 0, 30);
    lv_obj_set_size(ui->LanguageSet_label_15, 148, 38);

    //Write style for LanguageSet_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_label_15, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_label_15, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_label_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_img_29
    ui->LanguageSet_img_29 = lv_img_create(ui->LanguageSet_cont_4);
    lv_obj_add_flag(ui->LanguageSet_img_29, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LanguageSet_img_29, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->LanguageSet_img_29, 0,0);
    lv_img_set_angle(ui->LanguageSet_img_29, 1800);
    lv_obj_set_pos(ui->LanguageSet_img_29, 625, 59);
    lv_obj_set_size(ui->LanguageSet_img_29, 14, 24);

    //Write style for LanguageSet_img_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->LanguageSet_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LanguageSet_img_29, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->LanguageSet_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LanguageSet_img_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_btn_1
    ui->LanguageSet_btn_1 = lv_btn_create(ui->LanguageSet);
    ui->LanguageSet_btn_1_label = lv_label_create(ui->LanguageSet_btn_1);
    lv_label_set_text(ui->LanguageSet_btn_1_label, "设  置");
    lv_label_set_long_mode(ui->LanguageSet_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LanguageSet_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->LanguageSet_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LanguageSet_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->LanguageSet_btn_1, 70, 25);
    lv_obj_set_size(ui->LanguageSet_btn_1, 95, 32);

    //Write style for LanguageSet_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->LanguageSet_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LanguageSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_img_1
    ui->LanguageSet_img_1 = lv_img_create(ui->LanguageSet);
    lv_obj_add_flag(ui->LanguageSet_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LanguageSet_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->LanguageSet_img_1, 50,50);
    lv_img_set_angle(ui->LanguageSet_img_1, 0);
    lv_obj_set_pos(ui->LanguageSet_img_1, 43, 28);
    lv_obj_set_size(ui->LanguageSet_img_1, 14, 24);

    //Write style for LanguageSet_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->LanguageSet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LanguageSet_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->LanguageSet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LanguageSet_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_btn_2
    ui->LanguageSet_btn_2 = lv_btn_create(ui->LanguageSet);
    ui->LanguageSet_btn_2_label = lv_label_create(ui->LanguageSet_btn_2);
    lv_label_set_text(ui->LanguageSet_btn_2_label, "");
    lv_label_set_long_mode(ui->LanguageSet_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LanguageSet_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LanguageSet_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LanguageSet_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->LanguageSet_btn_2, -5, -11);
    lv_obj_set_size(ui->LanguageSet_btn_2, 229, 103);

    //Write style for LanguageSet_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->LanguageSet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LanguageSet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_cont_5
    ui->LanguageSet_cont_5 = lv_obj_create(ui->LanguageSet);
    lv_obj_set_pos(ui->LanguageSet_cont_5, 108, -291);
    lv_obj_set_size(ui->LanguageSet_cont_5, 584, 262);
    lv_obj_set_scrollbar_mode(ui->LanguageSet_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for LanguageSet_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_cont_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->LanguageSet_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->LanguageSet_cont_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->LanguageSet_cont_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_cont_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_label_17
    ui->LanguageSet_label_17 = lv_label_create(ui->LanguageSet_cont_5);
    lv_label_set_text(ui->LanguageSet_label_17, "是否将语言更改为:");
    lv_label_set_long_mode(ui->LanguageSet_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LanguageSet_label_17, 32, 66);
    lv_obj_set_size(ui->LanguageSet_label_17, 508, 40);

    //Write style for LanguageSet_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_label_17, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_label_17, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_label_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_cancel_btn
    ui->LanguageSet_cancel_btn = lv_btn_create(ui->LanguageSet_cont_5);
    ui->LanguageSet_cancel_btn_label = lv_label_create(ui->LanguageSet_cancel_btn);
    lv_label_set_text(ui->LanguageSet_cancel_btn_label, "取消");
    lv_label_set_long_mode(ui->LanguageSet_cancel_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LanguageSet_cancel_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LanguageSet_cancel_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LanguageSet_cancel_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->LanguageSet_cancel_btn, 44, 165);
    lv_obj_set_size(ui->LanguageSet_cancel_btn, 100, 50);

    //Write style for LanguageSet_cancel_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LanguageSet_cancel_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_cancel_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_cancel_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LanguageSet_cancel_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_cancel_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_cancel_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_cancel_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_cancel_btn, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_cancel_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_cancel_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LanguageSet_ok_btn
    ui->LanguageSet_ok_btn = lv_btn_create(ui->LanguageSet_cont_5);
    ui->LanguageSet_ok_btn_label = lv_label_create(ui->LanguageSet_ok_btn);
    lv_label_set_text(ui->LanguageSet_ok_btn_label, "确定");
    lv_label_set_long_mode(ui->LanguageSet_ok_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LanguageSet_ok_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LanguageSet_ok_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LanguageSet_ok_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->LanguageSet_ok_btn, 455, 168);
    lv_obj_set_size(ui->LanguageSet_ok_btn, 100, 50);

    //Write style for LanguageSet_ok_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LanguageSet_ok_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LanguageSet_ok_btn, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LanguageSet_ok_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LanguageSet_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LanguageSet_ok_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LanguageSet_ok_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LanguageSet_ok_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LanguageSet_ok_btn, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LanguageSet_ok_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LanguageSet_ok_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of LanguageSet.


    //Update current screen layout.
    lv_obj_update_layout(ui->LanguageSet);

    //Init events for screen.
    events_init_LanguageSet(ui);
}
