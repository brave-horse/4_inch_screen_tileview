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



void setup_scr_LedStrip(lv_ui *ui)
{
    //Write codes LedStrip
    ui->LedStrip = lv_obj_create(NULL);
    lv_obj_set_size(ui->LedStrip, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LedStrip, LV_SCROLLBAR_MODE_OFF);

    //Write style for LedStrip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_tabview_1
    ui->LedStrip_tabview_1 = lv_tabview_create(ui->LedStrip, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->LedStrip_tabview_1, 0, 0);
    lv_obj_set_size(ui->LedStrip_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LedStrip_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for LedStrip_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LedStrip_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LedStrip_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LedStrip_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LedStrip_tabview_1_extra_btnm_main_default
    static lv_style_t style_LedStrip_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_LedStrip_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_LedStrip_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_LedStrip_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_LedStrip_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_LedStrip_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_LedStrip_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LedStrip_tabview_1), &style_LedStrip_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LedStrip_tabview_1_extra_btnm_items_default
    static lv_style_t style_LedStrip_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_LedStrip_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_LedStrip_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_LedStrip_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_LedStrip_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LedStrip_tabview_1), &style_LedStrip_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_LedStrip_tabview_1_extra_btnm_items_checked
    static lv_style_t style_LedStrip_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_LedStrip_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_LedStrip_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_LedStrip_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_LedStrip_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_LedStrip_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_LedStrip_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_LedStrip_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_LedStrip_tabview_1_extra_btnm_items_checked, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_LedStrip_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LedStrip_tabview_1), &style_LedStrip_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->LedStrip_tabview_1_tab_1 = lv_tabview_add_tab(ui->LedStrip_tabview_1,"");
    lv_obj_t * LedStrip_tabview_1_tab_1_label = lv_label_create(ui->LedStrip_tabview_1_tab_1);
    lv_label_set_text(LedStrip_tabview_1_tab_1_label, "");

    //Write codes LedStrip_btn_2
    ui->LedStrip_btn_2 = lv_btn_create(ui->LedStrip_tabview_1_tab_1);
    ui->LedStrip_btn_2_label = lv_label_create(ui->LedStrip_btn_2);
    lv_label_set_text(ui->LedStrip_btn_2_label, "");
    lv_label_set_long_mode(ui->LedStrip_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LedStrip_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->LedStrip_btn_2, 4, 4);
    lv_obj_set_size(ui->LedStrip_btn_2, 229, 82);

    //Write style for LedStrip_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LedStrip_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_btn_3
    ui->LedStrip_btn_3 = lv_btn_create(ui->LedStrip_tabview_1_tab_1);
    ui->LedStrip_btn_3_label = lv_label_create(ui->LedStrip_btn_3);
    lv_label_set_text(ui->LedStrip_btn_3_label, "");
    lv_label_set_long_mode(ui->LedStrip_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LedStrip_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->LedStrip_btn_3, 4, 4);
    lv_obj_set_size(ui->LedStrip_btn_3, 229, 82);

    //Write style for LedStrip_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LedStrip_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_btn_3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_cont_1
    ui->LedStrip_cont_1 = lv_obj_create(ui->LedStrip);
    lv_obj_set_pos(ui->LedStrip_cont_1, 0, 87);
    lv_obj_set_size(ui->LedStrip_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->LedStrip_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for LedStrip_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LedStrip_cont_1, 107, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_label_2
    ui->LedStrip_label_2 = lv_label_create(ui->LedStrip);
    lv_label_set_text(ui->LedStrip_label_2, "色 温 | 4850K");
    lv_label_set_long_mode(ui->LedStrip_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LedStrip_label_2, 270, 560);
    lv_obj_set_size(ui->LedStrip_label_2, 195, 34);

    //Write style for LedStrip_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_ct_bar
    ui->LedStrip_ct_bar = lv_img_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_ct_bar, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->LedStrip_ct_bar, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ct_bar.png");
#else
    lv_img_set_src(ui->LedStrip_ct_bar, "S:/sdfile/EXT_RESERVED/uipackres/ui/ct_bar.png");
#endif
    lv_img_set_pivot(ui->LedStrip_ct_bar, 50,50);
    lv_img_set_angle(ui->LedStrip_ct_bar, 0);
    lv_obj_set_pos(ui->LedStrip_ct_bar, -210, 610);
    lv_obj_set_size(ui->LedStrip_ct_bar, 650, 75);

    //Write style for LedStrip_ct_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_ct_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LedStrip_ct_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_ct_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_ct_bar, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_slider_2
    ui->LedStrip_slider_2 = lv_slider_create(ui->LedStrip);
    lv_slider_set_range(ui->LedStrip_slider_2, 2700, 6500);
    lv_slider_set_mode(ui->LedStrip_slider_2, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->LedStrip_slider_2, 4600, LV_ANIM_OFF);
    lv_obj_set_pos(ui->LedStrip_slider_2, -210, 610);
    lv_obj_set_size(ui->LedStrip_slider_2, 650, 75);

    //Write style for LedStrip_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_2, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->LedStrip_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for LedStrip_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_2, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_2, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for LedStrip_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip_slider_2, lv_color_hex(0x300208), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip_slider_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_2, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes LedStrip_slider_1
    ui->LedStrip_slider_1 = lv_slider_create(ui->LedStrip);
    lv_slider_set_range(ui->LedStrip_slider_1, 0, 100);
    lv_slider_set_mode(ui->LedStrip_slider_1, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->LedStrip_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->LedStrip_slider_1, -215, 465);
    lv_obj_set_size(ui->LedStrip_slider_1, 650, 75);

    //Write style for LedStrip_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip_slider_1, lv_color_hex(0xdedfdf), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->LedStrip_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for LedStrip_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LedStrip_slider_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LedStrip_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for LedStrip_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_slider_1, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write style for LedStrip_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DISABLED.
    lv_obj_set_style_bg_opa(ui->LedStrip_slider_1, 0, LV_PART_KNOB|LV_STATE_DISABLED);
    lv_obj_set_style_radius(ui->LedStrip_slider_1, 50, LV_PART_KNOB|LV_STATE_DISABLED);

    //Write codes LedStrip_label_1
    ui->LedStrip_label_1 = lv_label_create(ui->LedStrip);
    lv_label_set_text(ui->LedStrip_label_1, "亮 度 | 50%");
    lv_label_set_long_mode(ui->LedStrip_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LedStrip_label_1, 270, 415);
    lv_obj_set_size(ui->LedStrip_label_1, 166, 39);

    //Write style for LedStrip_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_btn_1
    ui->LedStrip_btn_1 = lv_btn_create(ui->LedStrip);
    ui->LedStrip_btn_1_label = lv_label_create(ui->LedStrip_btn_1);
    lv_label_set_text(ui->LedStrip_btn_1_label, "灯  带");
    lv_label_set_long_mode(ui->LedStrip_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LedStrip_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->LedStrip_btn_1, 70, 25);
    lv_obj_set_size(ui->LedStrip_btn_1, 110, 32);

    //Write style for LedStrip_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LedStrip_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_imgbtn_1
    ui->LedStrip_imgbtn_1 = lv_imgbtn_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->LedStrip_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->LedStrip_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\btn_close.png", NULL);
#else
    lv_imgbtn_set_src(ui->LedStrip_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->LedStrip_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/btn_close.png", NULL);
#endif
    ui->LedStrip_imgbtn_1_label = lv_label_create(ui->LedStrip_imgbtn_1);
    lv_label_set_text(ui->LedStrip_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->LedStrip_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->LedStrip_imgbtn_1, 620, 120);
    lv_obj_set_size(ui->LedStrip_imgbtn_1, 70, 70);

    //Write style for LedStrip_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->LedStrip_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for LedStrip_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->LedStrip_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->LedStrip_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for LedStrip_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->LedStrip_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->LedStrip_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for LedStrip_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->LedStrip_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes LedStrip_on_off_2_img
    ui->LedStrip_on_off_2_img = lv_imgbtn_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_on_off_2_img, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->LedStrip_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->LedStrip_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->LedStrip_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->LedStrip_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->LedStrip_on_off_2_img_label = lv_label_create(ui->LedStrip_on_off_2_img);
    lv_label_set_text(ui->LedStrip_on_off_2_img_label, "");
    lv_label_set_long_mode(ui->LedStrip_on_off_2_img_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_on_off_2_img_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_on_off_2_img, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->LedStrip_on_off_2_img, 40, 120);
    lv_obj_set_size(ui->LedStrip_on_off_2_img, 48, 48);

    //Write style for LedStrip_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->LedStrip_on_off_2_img, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_on_off_2_img, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_on_off_2_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for LedStrip_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->LedStrip_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->LedStrip_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for LedStrip_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->LedStrip_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->LedStrip_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for LedStrip_on_off_2_img, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_on_off_2_img, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->LedStrip_on_off_2_img, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes LedStrip_LSOn
    ui->LedStrip_LSOn = lv_img_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_LSOn, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->LedStrip_LSOn, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LedStripOn.png");
#else
    lv_img_set_src(ui->LedStrip_LSOn, "S:/sdfile/EXT_RESERVED/uipackres/ui/LedStripOn.png");
#endif
    lv_img_set_pivot(ui->LedStrip_LSOn, 50,50);
    lv_img_set_angle(ui->LedStrip_LSOn, 0);
    lv_obj_set_pos(ui->LedStrip_LSOn, 208, 149);
    lv_obj_set_size(ui->LedStrip_LSOn, 300, 196);

    //Write style for LedStrip_LSOn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_LSOn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LedStrip_LSOn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_LSOn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_LSOn, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_LSOff
    ui->LedStrip_LSOff = lv_img_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_LSOff, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->LedStrip_LSOff, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LedStripOff.png");
#else
    lv_img_set_src(ui->LedStrip_LSOff, "S:/sdfile/EXT_RESERVED/uipackres/ui/LedStripOff.png");
#endif
    lv_img_set_pivot(ui->LedStrip_LSOff, 50,50);
    lv_img_set_angle(ui->LedStrip_LSOff, 0);
    lv_obj_set_pos(ui->LedStrip_LSOff, 208, 149);
    lv_obj_set_size(ui->LedStrip_LSOff, 300, 196);

    //Write style for LedStrip_LSOff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_LSOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LedStrip_LSOff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_LSOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_LSOff, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_btn_4
    ui->LedStrip_btn_4 = lv_btn_create(ui->LedStrip);
    ui->LedStrip_btn_4_label = lv_label_create(ui->LedStrip_btn_4);
    lv_label_set_text(ui->LedStrip_btn_4_label, "");
    lv_label_set_long_mode(ui->LedStrip_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->LedStrip_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->LedStrip_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->LedStrip_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->LedStrip_btn_4, -7, -5);
    lv_obj_set_size(ui->LedStrip_btn_4, 249, 96);

    //Write style for LedStrip_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LedStrip_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LedStrip_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LedStrip_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LedStrip_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LedStrip_btn_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LedStrip_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LedStrip_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LedStrip_img_1
    ui->LedStrip_img_1 = lv_img_create(ui->LedStrip);
    lv_obj_add_flag(ui->LedStrip_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LedStrip_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->LedStrip_img_1, 50,50);
    lv_img_set_angle(ui->LedStrip_img_1, 0);
    lv_obj_set_pos(ui->LedStrip_img_1, 43, 28);
    lv_obj_set_size(ui->LedStrip_img_1, 14, 24);

    //Write style for LedStrip_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LedStrip_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LedStrip_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LedStrip_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LedStrip_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of LedStrip.


    //Update current screen layout.
    lv_obj_update_layout(ui->LedStrip);

    //Init events for screen.
    events_init_LedStrip(ui);
}
