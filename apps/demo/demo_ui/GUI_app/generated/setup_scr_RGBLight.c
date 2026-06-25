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



void setup_scr_RGBLight(lv_ui *ui)
{
    //Write codes RGBLight
    ui->RGBLight = lv_obj_create(NULL);
    lv_obj_set_size(ui->RGBLight, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RGBLight, LV_SCROLLBAR_MODE_OFF);

    //Write style for RGBLight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_tabview_1
    ui->RGBLight_tabview_1 = lv_tabview_create(ui->RGBLight, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->RGBLight_tabview_1, 0, 0);
    lv_obj_set_size(ui->RGBLight_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RGBLight_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for RGBLight_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RGBLight_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RGBLight_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RGBLight_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RGBLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RGBLight_tabview_1_extra_btnm_main_default
    static lv_style_t style_RGBLight_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_RGBLight_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_RGBLight_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_RGBLight_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_RGBLight_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_RGBLight_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_RGBLight_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RGBLight_tabview_1), &style_RGBLight_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RGBLight_tabview_1_extra_btnm_items_default
    static lv_style_t style_RGBLight_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_RGBLight_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_RGBLight_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_RGBLight_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_RGBLight_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RGBLight_tabview_1), &style_RGBLight_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_RGBLight_tabview_1_extra_btnm_items_checked
    static lv_style_t style_RGBLight_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_RGBLight_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_RGBLight_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_RGBLight_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_RGBLight_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_RGBLight_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_RGBLight_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_RGBLight_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_RGBLight_tabview_1_extra_btnm_items_checked, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_RGBLight_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RGBLight_tabview_1), &style_RGBLight_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->RGBLight_tabview_1_tab_1 = lv_tabview_add_tab(ui->RGBLight_tabview_1,"");
    lv_obj_t * RGBLight_tabview_1_tab_1_label = lv_label_create(ui->RGBLight_tabview_1_tab_1);
    lv_label_set_text(RGBLight_tabview_1_tab_1_label, "");

    //Write codes RGBLight_cont_1
    ui->RGBLight_cont_1 = lv_obj_create(ui->RGBLight);
    lv_obj_set_pos(ui->RGBLight_cont_1, 0, 85);
    lv_obj_set_size(ui->RGBLight_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->RGBLight_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for RGBLight_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RGBLight_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_label_2
    ui->RGBLight_label_2 = lv_label_create(ui->RGBLight);
    lv_label_set_text(ui->RGBLight_label_2, "颜 色 | #00718D");
    lv_label_set_long_mode(ui->RGBLight_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RGBLight_label_2, 270, 560);
    lv_obj_set_size(ui->RGBLight_label_2, 257, 34);

    //Write style for RGBLight_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RGBLight_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_ct_bar
    ui->RGBLight_ct_bar = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_ct_bar, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RGBLight_ct_bar, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\rgb_bar.png");
#else
    lv_img_set_src(ui->RGBLight_ct_bar, "S:/sdfile/EXT_RESERVED/uipackres/ui/rgb_bar.png");
#endif
    lv_img_set_pivot(ui->RGBLight_ct_bar, 50,50);
    lv_img_set_angle(ui->RGBLight_ct_bar, 0);
    lv_obj_set_pos(ui->RGBLight_ct_bar, -221, 610);
    lv_obj_set_size(ui->RGBLight_ct_bar, 650, 75);

    //Write style for RGBLight_ct_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_ct_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_ct_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_ct_bar, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_ct_bar, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_slider_2
    ui->RGBLight_slider_2 = lv_slider_create(ui->RGBLight);
    lv_slider_set_range(ui->RGBLight_slider_2, 2700, 6500);
    lv_slider_set_mode(ui->RGBLight_slider_2, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->RGBLight_slider_2, 4600, LV_ANIM_OFF);
    lv_obj_set_pos(ui->RGBLight_slider_2, -220, 610);
    lv_obj_set_size(ui->RGBLight_slider_2, 650, 75);

    //Write style for RGBLight_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_2, 40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_slider_2, lv_color_hex(0x495661), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_slider_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_2, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->RGBLight_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for RGBLight_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_2, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_2, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for RGBLight_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_slider_2, lv_color_hex(0x300208), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_slider_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_2, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes RGBLight_slider_1
    ui->RGBLight_slider_1 = lv_slider_create(ui->RGBLight);
    lv_slider_set_range(ui->RGBLight_slider_1, 0, 100);
    lv_slider_set_mode(ui->RGBLight_slider_1, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->RGBLight_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->RGBLight_slider_1, -215, 465);
    lv_obj_set_size(ui->RGBLight_slider_1, 650, 75);

    //Write style for RGBLight_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_slider_1, lv_color_hex(0xdedfdf), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->RGBLight_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for RGBLight_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_slider_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for RGBLight_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_slider_1, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write style for RGBLight_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DISABLED.
    lv_obj_set_style_bg_opa(ui->RGBLight_slider_1, 0, LV_PART_KNOB|LV_STATE_DISABLED);
    lv_obj_set_style_radius(ui->RGBLight_slider_1, 50, LV_PART_KNOB|LV_STATE_DISABLED);

    //Write codes RGBLight_label_1
    ui->RGBLight_label_1 = lv_label_create(ui->RGBLight);
    lv_label_set_text(ui->RGBLight_label_1, "亮 度 | 50%");
    lv_label_set_long_mode(ui->RGBLight_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RGBLight_label_1, 271, 415);
    lv_obj_set_size(ui->RGBLight_label_1, 227, 39);

    //Write style for RGBLight_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RGBLight_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_btn_1
    ui->RGBLight_btn_1 = lv_btn_create(ui->RGBLight);
    ui->RGBLight_btn_1_label = lv_label_create(ui->RGBLight_btn_1);
    lv_label_set_text(ui->RGBLight_btn_1_label, "彩色灯");
    lv_label_set_long_mode(ui->RGBLight_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RGBLight_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->RGBLight_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RGBLight_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->RGBLight_btn_1, 70, 25);
    lv_obj_set_size(ui->RGBLight_btn_1, 122, 32);

    //Write style for RGBLight_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RGBLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RGBLight_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_imgbtn_1
    ui->RGBLight_imgbtn_1 = lv_imgbtn_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->RGBLight_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->RGBLight_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\btn_close.png", NULL);
#else
    lv_imgbtn_set_src(ui->RGBLight_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->RGBLight_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/btn_close.png", NULL);
#endif
    ui->RGBLight_imgbtn_1_label = lv_label_create(ui->RGBLight_imgbtn_1);
    lv_label_set_text(ui->RGBLight_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->RGBLight_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RGBLight_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RGBLight_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->RGBLight_imgbtn_1, 620, 120);
    lv_obj_set_size(ui->RGBLight_imgbtn_1, 70, 70);

    //Write style for RGBLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->RGBLight_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for RGBLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->RGBLight_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->RGBLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for RGBLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->RGBLight_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->RGBLight_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for RGBLight_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->RGBLight_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes RGBLight_on_off_2_img
    ui->RGBLight_on_off_2_img = lv_imgbtn_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_on_off_2_img, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->RGBLight_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->RGBLight_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->RGBLight_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->RGBLight_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->RGBLight_on_off_2_img_label = lv_label_create(ui->RGBLight_on_off_2_img);
    lv_label_set_text(ui->RGBLight_on_off_2_img_label, "");
    lv_label_set_long_mode(ui->RGBLight_on_off_2_img_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RGBLight_on_off_2_img_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RGBLight_on_off_2_img, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->RGBLight_on_off_2_img, 40, 120);
    lv_obj_set_size(ui->RGBLight_on_off_2_img, 48, 48);

    //Write style for RGBLight_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->RGBLight_on_off_2_img, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_on_off_2_img, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_on_off_2_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for RGBLight_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->RGBLight_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->RGBLight_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for RGBLight_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->RGBLight_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->RGBLight_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for RGBLight_on_off_2_img, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_on_off_2_img, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->RGBLight_on_off_2_img, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes RGBLight_RGBCover
    ui->RGBLight_RGBCover = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_RGBCover, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RGBLight_RGBCover, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RGBCover.png");
#else
    lv_img_set_src(ui->RGBLight_RGBCover, "S:/sdfile/EXT_RESERVED/uipackres/ui/RGBCover.png");
#endif
    lv_img_set_pivot(ui->RGBLight_RGBCover, 50,50);
    lv_img_set_angle(ui->RGBLight_RGBCover, 0);
    lv_obj_set_pos(ui->RGBLight_RGBCover, 233, 85);
    lv_obj_set_size(ui->RGBLight_RGBCover, 196, 190);

    //Write style for RGBLight_RGBCover, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_RGBCover, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_RGBCover, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_RGBCover, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_RGBCover, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_Blue
    ui->RGBLight_Blue = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_Blue, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RGBLight_Blue, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RGBblue.png");
#else
    lv_img_set_src(ui->RGBLight_Blue, "S:/sdfile/EXT_RESERVED/uipackres/ui/RGBblue.png");
#endif
    lv_img_set_pivot(ui->RGBLight_Blue, 50,50);
    lv_img_set_angle(ui->RGBLight_Blue, 0);
    lv_obj_set_pos(ui->RGBLight_Blue, 64, 249);
    lv_obj_set_size(ui->RGBLight_Blue, 537, 170);

    //Write style for RGBLight_Blue, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_Blue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_Blue, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_Blue, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_Blue, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_Red
    ui->RGBLight_Red = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_Red, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RGBLight_Red, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RGBRed.png");
#else
    lv_img_set_src(ui->RGBLight_Red, "S:/sdfile/EXT_RESERVED/uipackres/ui/RGBRed.png");
#endif
    lv_img_set_pivot(ui->RGBLight_Red, 50,50);
    lv_img_set_angle(ui->RGBLight_Red, 0);
    lv_obj_set_pos(ui->RGBLight_Red, 64, 249);
    lv_obj_set_size(ui->RGBLight_Red, 537, 170);

    //Write style for RGBLight_Red, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_Red, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_Red, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_Red, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_Red, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_Green
    ui->RGBLight_Green = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_Green, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->RGBLight_Green, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\RGBGreen.png");
#else
    lv_img_set_src(ui->RGBLight_Green, "S:/sdfile/EXT_RESERVED/uipackres/ui/RGBGreen.png");
#endif
    lv_img_set_pivot(ui->RGBLight_Green, 50,50);
    lv_img_set_angle(ui->RGBLight_Green, 0);
    lv_obj_set_pos(ui->RGBLight_Green, 64, 249);
    lv_obj_set_size(ui->RGBLight_Green, 537, 170);

    //Write style for RGBLight_Green, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_Green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_Green, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_Green, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_Green, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_1
    ui->RGBLight_img_1 = lv_img_create(ui->RGBLight);
    lv_obj_add_flag(ui->RGBLight_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->RGBLight_img_1, 50,50);
    lv_img_set_angle(ui->RGBLight_img_1, 0);
    lv_obj_set_pos(ui->RGBLight_img_1, 43, 28);
    lv_obj_set_size(ui->RGBLight_img_1, 14, 24);

    //Write style for RGBLight_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_btn_2
    ui->RGBLight_btn_2 = lv_btn_create(ui->RGBLight);
    ui->RGBLight_btn_2_label = lv_label_create(ui->RGBLight_btn_2);
    lv_label_set_text(ui->RGBLight_btn_2_label, "");
    lv_label_set_long_mode(ui->RGBLight_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RGBLight_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RGBLight_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RGBLight_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->RGBLight_btn_2, -6, -7);
    lv_obj_set_size(ui->RGBLight_btn_2, 238, 99);

    //Write style for RGBLight_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RGBLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RGBLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RGBLight_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RGBLight_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RGBLight_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RGBLight_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_cont_2
    ui->RGBLight_cont_2 = lv_obj_create(ui->RGBLight);
    lv_obj_set_pos(ui->RGBLight_cont_2, 98, -457);
    lv_obj_set_size(ui->RGBLight_cont_2, 524, 392);
    lv_obj_set_scrollbar_mode(ui->RGBLight_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for RGBLight_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RGBLight_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RGBLight_cont_2, lv_color_hex(0x171717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RGBLight_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RGBLight_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_7
    ui->RGBLight_img_7 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_7, &_RGBscene1_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_7, 50,50);
    lv_img_set_angle(ui->RGBLight_img_7, 0);
    lv_obj_set_pos(ui->RGBLight_img_7, 40, 29);
    lv_obj_set_size(ui->RGBLight_img_7, 112, 140);

    //Write style for RGBLight_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_6
    ui->RGBLight_img_6 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_6, &_RGBscene2_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_6, 50,50);
    lv_img_set_angle(ui->RGBLight_img_6, 0);
    lv_obj_set_pos(ui->RGBLight_img_6, 210, 29);
    lv_obj_set_size(ui->RGBLight_img_6, 112, 140);

    //Write style for RGBLight_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_5
    ui->RGBLight_img_5 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_5, &_RGBscene3_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_5, 50,50);
    lv_img_set_angle(ui->RGBLight_img_5, 0);
    lv_obj_set_pos(ui->RGBLight_img_5, 380, 29);
    lv_obj_set_size(ui->RGBLight_img_5, 112, 140);

    //Write style for RGBLight_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_4
    ui->RGBLight_img_4 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_4, &_RGBscene4_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_4, 50,50);
    lv_img_set_angle(ui->RGBLight_img_4, 0);
    lv_obj_set_pos(ui->RGBLight_img_4, 40, 204);
    lv_obj_set_size(ui->RGBLight_img_4, 112, 140);

    //Write style for RGBLight_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_3
    ui->RGBLight_img_3 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_3, &_RGBscene5_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_3, 50,50);
    lv_img_set_angle(ui->RGBLight_img_3, 0);
    lv_obj_set_pos(ui->RGBLight_img_3, 210, 204);
    lv_obj_set_size(ui->RGBLight_img_3, 112, 140);

    //Write style for RGBLight_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RGBLight_img_2
    ui->RGBLight_img_2 = lv_img_create(ui->RGBLight_cont_2);
    lv_obj_add_flag(ui->RGBLight_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RGBLight_img_2, &_RGBscene6_alpha_112x140);
    lv_img_set_pivot(ui->RGBLight_img_2, 50,50);
    lv_img_set_angle(ui->RGBLight_img_2, 0);
    lv_obj_set_pos(ui->RGBLight_img_2, 380, 204);
    lv_obj_set_size(ui->RGBLight_img_2, 112, 140);

    //Write style for RGBLight_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RGBLight_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RGBLight_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RGBLight_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RGBLight_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of RGBLight.


    //Update current screen layout.
    lv_obj_update_layout(ui->RGBLight);

    //Init events for screen.
    events_init_RGBLight(ui);
}
