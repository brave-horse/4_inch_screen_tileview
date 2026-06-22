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



void setup_scr_light_CT_screen(lv_ui *ui)
{
    //Write codes light_CT_screen
    ui->light_CT_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->light_CT_screen, 720, 720);
    lv_obj_set_scrollbar_mode(ui->light_CT_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for light_CT_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_tabview_1
    ui->light_CT_screen_tabview_1 = lv_tabview_create(ui->light_CT_screen, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->light_CT_screen_tabview_1, 0, -1);
    lv_obj_set_size(ui->light_CT_screen_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->light_CT_screen_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for light_CT_screen_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->light_CT_screen_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->light_CT_screen_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->light_CT_screen_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->light_CT_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_light_CT_screen_tabview_1_extra_btnm_main_default
    static lv_style_t style_light_CT_screen_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_light_CT_screen_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_light_CT_screen_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_light_CT_screen_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_light_CT_screen_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_light_CT_screen_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_light_CT_screen_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->light_CT_screen_tabview_1), &style_light_CT_screen_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_light_CT_screen_tabview_1_extra_btnm_items_default
    static lv_style_t style_light_CT_screen_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_light_CT_screen_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_light_CT_screen_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_light_CT_screen_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_light_CT_screen_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->light_CT_screen_tabview_1), &style_light_CT_screen_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_light_CT_screen_tabview_1_extra_btnm_items_checked
    static lv_style_t style_light_CT_screen_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_light_CT_screen_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_light_CT_screen_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->light_CT_screen_tabview_1), &style_light_CT_screen_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->light_CT_screen_tabview_1_tab_1 = lv_tabview_add_tab(ui->light_CT_screen_tabview_1,"");
    lv_obj_t * light_CT_screen_tabview_1_tab_1_label = lv_label_create(ui->light_CT_screen_tabview_1_tab_1);
    lv_label_set_text(light_CT_screen_tabview_1_tab_1_label, "");

    //Write codes light_CT_screen_cont_1
    ui->light_CT_screen_cont_1 = lv_obj_create(ui->light_CT_screen);
    lv_obj_set_pos(ui->light_CT_screen_cont_1, 0, 88);
    lv_obj_set_size(ui->light_CT_screen_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->light_CT_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for light_CT_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->light_CT_screen_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_label_2
    ui->light_CT_screen_label_2 = lv_label_create(ui->light_CT_screen);
    lv_label_set_text(ui->light_CT_screen_label_2, "色 温 | 4850K");
    lv_label_set_long_mode(ui->light_CT_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->light_CT_screen_label_2, 270, 560);
    lv_obj_set_size(ui->light_CT_screen_label_2, 195, 34);

    //Write style for light_CT_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->light_CT_screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_ct_bar
    ui->light_CT_screen_ct_bar = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_ct_bar, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->light_CT_screen_ct_bar, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\ct_bar.png");
#else
    lv_img_set_src(ui->light_CT_screen_ct_bar, "S:/sdfile/EXT_RESERVED/uipackres/ui/ct_bar.png");
#endif
    lv_img_set_pivot(ui->light_CT_screen_ct_bar, 50,50);
    lv_img_set_angle(ui->light_CT_screen_ct_bar, 0);
    lv_obj_set_pos(ui->light_CT_screen_ct_bar, -210, 610);
    lv_obj_set_size(ui->light_CT_screen_ct_bar, 650, 75);

    //Write style for light_CT_screen_ct_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_ct_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_ct_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_ct_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_ct_bar, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_slider_2
    ui->light_CT_screen_slider_2 = lv_slider_create(ui->light_CT_screen);
    lv_slider_set_range(ui->light_CT_screen_slider_2, 2700, 6500);
    lv_slider_set_mode(ui->light_CT_screen_slider_2, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->light_CT_screen_slider_2, 4600, LV_ANIM_OFF);
    lv_obj_set_pos(ui->light_CT_screen_slider_2, -210, 610);
    lv_obj_set_size(ui->light_CT_screen_slider_2, 650, 75);

    //Write style for light_CT_screen_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_2, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->light_CT_screen_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_2, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_2, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen_slider_2, lv_color_hex(0x300208), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen_slider_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_2, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_slider_1
    ui->light_CT_screen_slider_1 = lv_slider_create(ui->light_CT_screen);
    lv_slider_set_range(ui->light_CT_screen_slider_1, 0, 100);
    lv_slider_set_mode(ui->light_CT_screen_slider_1, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui->light_CT_screen_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->light_CT_screen_slider_1, -215, 465);
    lv_obj_set_size(ui->light_CT_screen_slider_1, 650, 70);

    //Write style for light_CT_screen_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen_slider_1, lv_color_hex(0xdedfdf), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->light_CT_screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->light_CT_screen_slider_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->light_CT_screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_1, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DISABLED.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_slider_1, 0, LV_PART_KNOB|LV_STATE_DISABLED);
    lv_obj_set_style_radius(ui->light_CT_screen_slider_1, 50, LV_PART_KNOB|LV_STATE_DISABLED);

    //Write codes light_CT_screen_label_1
    ui->light_CT_screen_label_1 = lv_label_create(ui->light_CT_screen);
    lv_label_set_text(ui->light_CT_screen_label_1, "亮 度 | 50%");
    lv_label_set_long_mode(ui->light_CT_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->light_CT_screen_label_1, 270, 415);
    lv_obj_set_size(ui->light_CT_screen_label_1, 174, 32);

    //Write style for light_CT_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->light_CT_screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_dev_shell_img
    ui->light_CT_screen_dev_shell_img = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_dev_shell_img, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->light_CT_screen_dev_shell_img, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\dev_shell.png");
#else
    lv_img_set_src(ui->light_CT_screen_dev_shell_img, "S:/sdfile/EXT_RESERVED/uipackres/ui/dev_shell.png");
#endif
    lv_img_set_pivot(ui->light_CT_screen_dev_shell_img, 50,50);
    lv_img_set_angle(ui->light_CT_screen_dev_shell_img, 0);
    lv_obj_set_pos(ui->light_CT_screen_dev_shell_img, 272, 84);
    lv_obj_set_size(ui->light_CT_screen_dev_shell_img, 166, 190);

    //Write style for light_CT_screen_dev_shell_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_dev_shell_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_dev_shell_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_dev_shell_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_dev_shell_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_white_lid
    ui->light_CT_screen_white_lid = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_white_lid, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->light_CT_screen_white_lid, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\white_lid.png");
#else
    lv_img_set_src(ui->light_CT_screen_white_lid, "S:/sdfile/EXT_RESERVED/uipackres/ui/white_lid.png");
#endif
    lv_img_set_pivot(ui->light_CT_screen_white_lid, 50,50);
    lv_img_set_angle(ui->light_CT_screen_white_lid, 0);
    lv_obj_set_pos(ui->light_CT_screen_white_lid, 212, 235);
    lv_obj_set_size(ui->light_CT_screen_white_lid, 286, 54);

    //Write style for light_CT_screen_white_lid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_white_lid, 184, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->light_CT_screen_white_lid, lv_color_hex(0x020202), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_white_lid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_white_lid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_white_lid, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_dev_orange_img
    ui->light_CT_screen_dev_orange_img = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_dev_orange_img, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->light_CT_screen_dev_orange_img, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\dev_orange.png");
#else
    lv_img_set_src(ui->light_CT_screen_dev_orange_img, "S:/sdfile/EXT_RESERVED/uipackres/ui/dev_orange.png");
#endif
    lv_img_set_pivot(ui->light_CT_screen_dev_orange_img, 50,50);
    lv_img_set_angle(ui->light_CT_screen_dev_orange_img, 0);
    lv_obj_set_pos(ui->light_CT_screen_dev_orange_img, 110, 246);
    lv_obj_set_size(ui->light_CT_screen_dev_orange_img, 490, 164);

    //Write style for light_CT_screen_dev_orange_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_dev_orange_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_dev_orange_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_dev_orange_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_dev_orange_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_dev_white_img
    ui->light_CT_screen_dev_white_img = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_dev_white_img, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->light_CT_screen_dev_white_img, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\dev_white.png");
#else
    lv_img_set_src(ui->light_CT_screen_dev_white_img, "S:/sdfile/EXT_RESERVED/uipackres/ui/dev_white.png");
#endif
    lv_img_set_pivot(ui->light_CT_screen_dev_white_img, 50,50);
    lv_img_set_angle(ui->light_CT_screen_dev_white_img, 0);
    lv_obj_set_pos(ui->light_CT_screen_dev_white_img, 110, 246);
    lv_obj_set_size(ui->light_CT_screen_dev_white_img, 490, 164);

    //Write style for light_CT_screen_dev_white_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_dev_white_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_dev_white_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_dev_white_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_dev_white_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_btn_1
    ui->light_CT_screen_btn_1 = lv_btn_create(ui->light_CT_screen);
    ui->light_CT_screen_btn_1_label = lv_label_create(ui->light_CT_screen_btn_1);
    lv_label_set_text(ui->light_CT_screen_btn_1_label, "色温灯");
    lv_label_set_long_mode(ui->light_CT_screen_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->light_CT_screen_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->light_CT_screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->light_CT_screen_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->light_CT_screen_btn_1, 70, 25);
    lv_obj_set_size(ui->light_CT_screen_btn_1, 128, 32);

    //Write style for light_CT_screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->light_CT_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->light_CT_screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_imgbtn_1
    ui->light_CT_screen_imgbtn_1 = lv_imgbtn_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->light_CT_screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->light_CT_screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\btn_close.png", NULL);
#else
    lv_imgbtn_set_src(ui->light_CT_screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/scene_btn.png", NULL);
    lv_imgbtn_set_src(ui->light_CT_screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/btn_close.png", NULL);
#endif
    ui->light_CT_screen_imgbtn_1_label = lv_label_create(ui->light_CT_screen_imgbtn_1);
    lv_label_set_text(ui->light_CT_screen_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->light_CT_screen_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->light_CT_screen_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->light_CT_screen_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->light_CT_screen_imgbtn_1, 620, 120);
    lv_obj_set_size(ui->light_CT_screen_imgbtn_1, 70, 70);

    //Write style for light_CT_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->light_CT_screen_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->light_CT_screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->light_CT_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for light_CT_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->light_CT_screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->light_CT_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for light_CT_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes light_CT_screen_on_off_2_img
    ui->light_CT_screen_on_off_2_img = lv_imgbtn_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_on_off_2_img, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->light_CT_screen_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->light_CT_screen_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->light_CT_screen_on_off_2_img, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->light_CT_screen_on_off_2_img, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->light_CT_screen_on_off_2_img_label = lv_label_create(ui->light_CT_screen_on_off_2_img);
    lv_label_set_text(ui->light_CT_screen_on_off_2_img_label, "");
    lv_label_set_long_mode(ui->light_CT_screen_on_off_2_img_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->light_CT_screen_on_off_2_img_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->light_CT_screen_on_off_2_img, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->light_CT_screen_on_off_2_img, 38, 120);
    lv_obj_set_size(ui->light_CT_screen_on_off_2_img, 48, 48);

    //Write style for light_CT_screen_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->light_CT_screen_on_off_2_img, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_on_off_2_img, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_on_off_2_img, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for light_CT_screen_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->light_CT_screen_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->light_CT_screen_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for light_CT_screen_on_off_2_img, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->light_CT_screen_on_off_2_img, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->light_CT_screen_on_off_2_img, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for light_CT_screen_on_off_2_img, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_on_off_2_img, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->light_CT_screen_on_off_2_img, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes light_CT_screen_btn_2
    ui->light_CT_screen_btn_2 = lv_btn_create(ui->light_CT_screen);
    ui->light_CT_screen_btn_2_label = lv_label_create(ui->light_CT_screen_btn_2);
    lv_label_set_text(ui->light_CT_screen_btn_2_label, "");
    lv_label_set_long_mode(ui->light_CT_screen_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->light_CT_screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->light_CT_screen_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->light_CT_screen_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->light_CT_screen_btn_2, -8, -4);
    lv_obj_set_size(ui->light_CT_screen_btn_2, 258, 95);

    //Write style for light_CT_screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->light_CT_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->light_CT_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->light_CT_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->light_CT_screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->light_CT_screen_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->light_CT_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->light_CT_screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes light_CT_screen_img_1
    ui->light_CT_screen_img_1 = lv_img_create(ui->light_CT_screen);
    lv_obj_add_flag(ui->light_CT_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->light_CT_screen_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->light_CT_screen_img_1, 50,50);
    lv_img_set_angle(ui->light_CT_screen_img_1, 0);
    lv_obj_set_pos(ui->light_CT_screen_img_1, 43, 28);
    lv_obj_set_size(ui->light_CT_screen_img_1, 14, 24);

    //Write style for light_CT_screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->light_CT_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->light_CT_screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->light_CT_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->light_CT_screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of light_CT_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->light_CT_screen);

    //Init events for screen.
    events_init_light_CT_screen(ui);
}
