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



void setup_scr_setting_screen(lv_ui *ui)
{
    //Write codes setting_screen
    ui->setting_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->setting_screen, 720, 720);
    lv_obj_set_scrollbar_mode(ui->setting_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_tabview_1
    ui->setting_screen_tabview_1 = lv_tabview_create(ui->setting_screen, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->setting_screen_tabview_1, 0, 0);
    lv_obj_set_size(ui->setting_screen_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->setting_screen_tabview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_tabview_1_extra_btnm_main_default
    static lv_style_t style_setting_screen_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_setting_screen_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_setting_screen_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_setting_screen_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_setting_screen_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_setting_screen_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_setting_screen_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->setting_screen_tabview_1), &style_setting_screen_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_setting_screen_tabview_1_extra_btnm_items_default
    static lv_style_t style_setting_screen_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_setting_screen_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_setting_screen_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_setting_screen_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_setting_screen_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->setting_screen_tabview_1), &style_setting_screen_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_setting_screen_tabview_1_extra_btnm_items_checked
    static lv_style_t style_setting_screen_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_setting_screen_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_setting_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_setting_screen_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_setting_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_setting_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_setting_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_setting_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_setting_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_setting_screen_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->setting_screen_tabview_1), &style_setting_screen_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->setting_screen_tabview_1_tab_1 = lv_tabview_add_tab(ui->setting_screen_tabview_1,"");
    lv_obj_t * setting_screen_tabview_1_tab_1_label = lv_label_create(ui->setting_screen_tabview_1_tab_1);
    lv_label_set_text(setting_screen_tabview_1_tab_1_label, "");

    //Write codes setting_screen_btn_1
    ui->setting_screen_btn_1 = lv_btn_create(ui->setting_screen);
    ui->setting_screen_btn_1_label = lv_label_create(ui->setting_screen_btn_1);
    lv_label_set_text(ui->setting_screen_btn_1_label, "设  置");
    lv_label_set_long_mode(ui->setting_screen_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->setting_screen_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->setting_screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->setting_screen_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->setting_screen_btn_1, 70, 25);
    lv_obj_set_size(ui->setting_screen_btn_1, 95, 32);

    //Write style for setting_screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->setting_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_1
    ui->setting_screen_img_1 = lv_img_create(ui->setting_screen);
    lv_obj_add_flag(ui->setting_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_1, 50,50);
    lv_img_set_angle(ui->setting_screen_img_1, 0);
    lv_obj_set_pos(ui->setting_screen_img_1, 43, 28);
    lv_obj_set_size(ui->setting_screen_img_1, 14, 24);

    //Write style for setting_screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_btn_2
    ui->setting_screen_btn_2 = lv_btn_create(ui->setting_screen);
    ui->setting_screen_btn_2_label = lv_label_create(ui->setting_screen_btn_2);
    lv_label_set_text(ui->setting_screen_btn_2_label, "");
    lv_label_set_long_mode(ui->setting_screen_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->setting_screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->setting_screen_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->setting_screen_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->setting_screen_btn_2, -5, -11);
    lv_obj_set_size(ui->setting_screen_btn_2, 229, 103);

    //Write style for setting_screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_3
    ui->setting_screen_cont_3 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_3, 35, 85);
    lv_obj_set_size(ui->setting_screen_cont_3, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_cont_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_3, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_3, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_
    ui->setting_screen_img_ = lv_img_create(ui->setting_screen_cont_3);
    lv_obj_add_flag(ui->setting_screen_img_, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_, &_setnet_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_, 50,50);
    lv_img_set_angle(ui->setting_screen_img_, 0);
    lv_obj_set_pos(ui->setting_screen_img_, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_, 43, 43);

    //Write style for setting_screen_img_, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_1
    ui->setting_screen_label_1 = lv_label_create(ui->setting_screen_cont_3);
    lv_label_set_text(ui->setting_screen_label_1, "网络设置");
    lv_label_set_long_mode(ui->setting_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_1, 53, 30);
    lv_obj_set_size(ui->setting_screen_label_1, 148, 32);

    //Write style for setting_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_2
    ui->setting_screen_img_2 = lv_img_create(ui->setting_screen_cont_3);
    lv_obj_add_flag(ui->setting_screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_2, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_2, 0,0);
    lv_img_set_angle(ui->setting_screen_img_2, 1800);
    lv_obj_set_pos(ui->setting_screen_img_2, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_2, 14, 24);

    //Write style for setting_screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_4
    ui->setting_screen_cont_4 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_4, 35, 175);
    lv_obj_set_size(ui->setting_screen_cont_4, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_4, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_4, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_4
    ui->setting_screen_img_4 = lv_img_create(ui->setting_screen_cont_4);
    lv_obj_add_flag(ui->setting_screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_4, &_setdisp_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_4, 50,50);
    lv_img_set_angle(ui->setting_screen_img_4, 0);
    lv_obj_set_pos(ui->setting_screen_img_4, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_4, 43, 43);

    //Write style for setting_screen_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_2
    ui->setting_screen_label_2 = lv_label_create(ui->setting_screen_cont_4);
    lv_label_set_text(ui->setting_screen_label_2, "显示设置");
    lv_label_set_long_mode(ui->setting_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_2, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_2, 148, 32);

    //Write style for setting_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_3
    ui->setting_screen_img_3 = lv_img_create(ui->setting_screen_cont_4);
    lv_obj_add_flag(ui->setting_screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_3, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_3, 0,0);
    lv_img_set_angle(ui->setting_screen_img_3, 1800);
    lv_obj_set_pos(ui->setting_screen_img_3, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_3, 14, 24);

    //Write style for setting_screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_5
    ui->setting_screen_cont_5 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_5, 35, 265);
    lv_obj_set_size(ui->setting_screen_cont_5, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_cont_5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_5, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_5, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_6
    ui->setting_screen_img_6 = lv_img_create(ui->setting_screen_cont_5);
    lv_obj_add_flag(ui->setting_screen_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_6, &_setswitch_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_6, 50,50);
    lv_img_set_angle(ui->setting_screen_img_6, 0);
    lv_obj_set_pos(ui->setting_screen_img_6, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_6, 43, 43);

    //Write style for setting_screen_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_3
    ui->setting_screen_label_3 = lv_label_create(ui->setting_screen_cont_5);
    lv_label_set_text(ui->setting_screen_label_3, "开关配置");
    lv_label_set_long_mode(ui->setting_screen_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_3, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_3, 148, 32);

    //Write style for setting_screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_5
    ui->setting_screen_img_5 = lv_img_create(ui->setting_screen_cont_5);
    lv_obj_add_flag(ui->setting_screen_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_5, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_5, 0,0);
    lv_img_set_angle(ui->setting_screen_img_5, 1800);
    lv_obj_set_pos(ui->setting_screen_img_5, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_5, 14, 24);

    //Write style for setting_screen_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_6
    ui->setting_screen_cont_6 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_6, 35, 355);
    lv_obj_set_size(ui->setting_screen_cont_6, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_6, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_6, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_8
    ui->setting_screen_img_8 = lv_img_create(ui->setting_screen_cont_6);
    lv_obj_add_flag(ui->setting_screen_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_8, &_setsensor_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_8, 50,50);
    lv_img_set_angle(ui->setting_screen_img_8, 0);
    lv_obj_set_pos(ui->setting_screen_img_8, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_8, 43, 43);

    //Write style for setting_screen_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_4
    ui->setting_screen_label_4 = lv_label_create(ui->setting_screen_cont_6);
    lv_label_set_text(ui->setting_screen_label_4, "传感器配置");
    lv_label_set_long_mode(ui->setting_screen_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_4, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_4, 148, 32);

    //Write style for setting_screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_4, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_7
    ui->setting_screen_img_7 = lv_img_create(ui->setting_screen_cont_6);
    lv_obj_add_flag(ui->setting_screen_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_7, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_7, 0,0);
    lv_img_set_angle(ui->setting_screen_img_7, 1800);
    lv_obj_set_pos(ui->setting_screen_img_7, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_7, 14, 24);

    //Write style for setting_screen_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_7
    ui->setting_screen_cont_7 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_7, 35, 445);
    lv_obj_set_size(ui->setting_screen_cont_7, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_7, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_7, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_10
    ui->setting_screen_img_10 = lv_img_create(ui->setting_screen_cont_7);
    lv_obj_add_flag(ui->setting_screen_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_10, &_setreboot_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_10, 50,50);
    lv_img_set_angle(ui->setting_screen_img_10, 0);
    lv_obj_set_pos(ui->setting_screen_img_10, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_10, 43, 43);

    //Write style for setting_screen_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_5
    ui->setting_screen_label_5 = lv_label_create(ui->setting_screen_cont_7);
    lv_label_set_text(ui->setting_screen_label_5, "设备重启");
    lv_label_set_long_mode(ui->setting_screen_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_5, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_5, 148, 32);

    //Write style for setting_screen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_9
    ui->setting_screen_img_9 = lv_img_create(ui->setting_screen_cont_7);
    lv_obj_add_flag(ui->setting_screen_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_9, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_9, 0,0);
    lv_img_set_angle(ui->setting_screen_img_9, 1800);
    lv_obj_set_pos(ui->setting_screen_img_9, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_9, 14, 24);

    //Write style for setting_screen_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_8
    ui->setting_screen_cont_8 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_8, 35, 535);
    lv_obj_set_size(ui->setting_screen_cont_8, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_8, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_8, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_8, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_12
    ui->setting_screen_img_12 = lv_img_create(ui->setting_screen_cont_8);
    lv_obj_add_flag(ui->setting_screen_img_12, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_12, &_setrestore_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_12, 50,50);
    lv_img_set_angle(ui->setting_screen_img_12, 0);
    lv_obj_set_pos(ui->setting_screen_img_12, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_12, 43, 43);

    //Write style for setting_screen_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_6
    ui->setting_screen_label_6 = lv_label_create(ui->setting_screen_cont_8);
    lv_label_set_text(ui->setting_screen_label_6, "恢复出厂");
    lv_label_set_long_mode(ui->setting_screen_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_6, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_6, 148, 32);

    //Write style for setting_screen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_11
    ui->setting_screen_img_11 = lv_img_create(ui->setting_screen_cont_8);
    lv_obj_add_flag(ui->setting_screen_img_11, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_11, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_11, 0,0);
    lv_img_set_angle(ui->setting_screen_img_11, 1800);
    lv_obj_set_pos(ui->setting_screen_img_11, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_11, 14, 24);

    //Write style for setting_screen_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_cont_9
    ui->setting_screen_cont_9 = lv_obj_create(ui->setting_screen);
    lv_obj_set_pos(ui->setting_screen_cont_9, 35, 625);
    lv_obj_set_size(ui->setting_screen_cont_9, 650, 90);
    lv_obj_set_scrollbar_mode(ui->setting_screen_cont_9, LV_SCROLLBAR_MODE_OFF);

    //Write style for setting_screen_cont_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->setting_screen_cont_9, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->setting_screen_cont_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->setting_screen_cont_9, lv_color_hex(0x151313), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->setting_screen_cont_9, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_cont_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->setting_screen_cont_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->setting_screen_cont_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_14
    ui->setting_screen_img_14 = lv_img_create(ui->setting_screen_cont_9);
    lv_obj_add_flag(ui->setting_screen_img_14, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_14, &_setabout_alpha_43x43);
    lv_img_set_pivot(ui->setting_screen_img_14, 50,50);
    lv_img_set_angle(ui->setting_screen_img_14, 0);
    lv_obj_set_pos(ui->setting_screen_img_14, 0, 23);
    lv_obj_set_size(ui->setting_screen_img_14, 43, 43);

    //Write style for setting_screen_img_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_label_7
    ui->setting_screen_label_7 = lv_label_create(ui->setting_screen_cont_9);
    lv_label_set_text(ui->setting_screen_label_7, "关于产品");
    lv_label_set_long_mode(ui->setting_screen_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->setting_screen_label_7, 54, 30);
    lv_obj_set_size(ui->setting_screen_label_7, 148, 32);

    //Write style for setting_screen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->setting_screen_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->setting_screen_label_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->setting_screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->setting_screen_label_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->setting_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes setting_screen_img_13
    ui->setting_screen_img_13 = lv_img_create(ui->setting_screen_cont_9);
    lv_obj_add_flag(ui->setting_screen_img_13, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->setting_screen_img_13, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->setting_screen_img_13, 0,0);
    lv_img_set_angle(ui->setting_screen_img_13, 1800);
    lv_obj_set_pos(ui->setting_screen_img_13, 632, 59);
    lv_obj_set_size(ui->setting_screen_img_13, 14, 24);

    //Write style for setting_screen_img_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->setting_screen_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->setting_screen_img_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->setting_screen_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->setting_screen_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of setting_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->setting_screen);

    //Init events for screen.
    events_init_setting_screen(ui);
}
