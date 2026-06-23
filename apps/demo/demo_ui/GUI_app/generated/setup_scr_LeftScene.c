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



void setup_scr_LeftScene(lv_ui *ui)
{
    //Write codes LeftScene
    ui->LeftScene = lv_obj_create(NULL);
    lv_obj_set_size(ui->LeftScene, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LeftScene, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LeftScene, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_tabview_1
    ui->LeftScene_tabview_1 = lv_tabview_create(ui->LeftScene, LV_DIR_TOP, 0);
    lv_obj_set_pos(ui->LeftScene_tabview_1, 0, 0);
    lv_obj_set_size(ui->LeftScene_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->LeftScene_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for LeftScene_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->LeftScene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->LeftScene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LeftScene_tabview_1_extra_btnm_main_default
    static lv_style_t style_LeftScene_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_LeftScene_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_LeftScene_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_LeftScene_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_LeftScene_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_LeftScene_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_LeftScene_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LeftScene_tabview_1), &style_LeftScene_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_LeftScene_tabview_1_extra_btnm_items_default
    static lv_style_t style_LeftScene_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_LeftScene_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_LeftScene_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_LeftScene_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_LeftScene_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LeftScene_tabview_1), &style_LeftScene_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_LeftScene_tabview_1_extra_btnm_items_checked
    static lv_style_t style_LeftScene_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_LeftScene_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_LeftScene_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_LeftScene_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_LeftScene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_LeftScene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_LeftScene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_LeftScene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_LeftScene_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_LeftScene_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->LeftScene_tabview_1), &style_LeftScene_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->LeftScene_tabview_1_tab_1 = lv_tabview_add_tab(ui->LeftScene_tabview_1,"");
    lv_obj_t * LeftScene_tabview_1_tab_1_label = lv_label_create(ui->LeftScene_tabview_1_tab_1);
    lv_label_set_text(LeftScene_tabview_1_tab_1_label, "");

    //Write codes LeftScene_cont_18
    ui->LeftScene_cont_18 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_18, 350, 485);
    lv_obj_set_size(ui->LeftScene_cont_18, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_18, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_18, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_18, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_18, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_22
    ui->LeftScene_label_22 = lv_label_create(ui->LeftScene_cont_18);
    lv_label_set_text(ui->LeftScene_label_22, "80%");
    lv_label_set_long_mode(ui->LeftScene_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_22, 140, 130);
    lv_obj_set_size(ui->LeftScene_label_22, 70, 35);

    //Write style for LeftScene_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_22, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_18
    ui->LeftScene_img_18 = lv_img_create(ui->LeftScene_cont_18);
    lv_obj_add_flag(ui->LeftScene_img_18, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_18, &_CuratianS4_alpha_59x31);
    lv_img_set_pivot(ui->LeftScene_img_18, 50,50);
    lv_img_set_angle(ui->LeftScene_img_18, 0);
    lv_obj_set_pos(ui->LeftScene_img_18, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_18, 59, 31);

    //Write style for LeftScene_img_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_cont_17
    ui->LeftScene_cont_17 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_17, 5, 485);
    lv_obj_set_size(ui->LeftScene_cont_17, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_17, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_17, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_17, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_17, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_21
    ui->LeftScene_label_21 = lv_label_create(ui->LeftScene_cont_17);
    lv_label_set_text(ui->LeftScene_label_21, "60%");
    lv_label_set_long_mode(ui->LeftScene_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_21, 140, 130);
    lv_obj_set_size(ui->LeftScene_label_21, 65, 30);

    //Write style for LeftScene_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_21, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_21, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_17
    ui->LeftScene_img_17 = lv_img_create(ui->LeftScene_cont_17);
    lv_obj_add_flag(ui->LeftScene_img_17, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_17, &_CuratianS3_alpha_59x31);
    lv_img_set_pivot(ui->LeftScene_img_17, 50,50);
    lv_img_set_angle(ui->LeftScene_img_17, 0);
    lv_obj_set_pos(ui->LeftScene_img_17, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_17, 59, 31);

    //Write style for LeftScene_img_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_cont_15
    ui->LeftScene_cont_15 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_15, 350, 249);
    lv_obj_set_size(ui->LeftScene_cont_15, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_15, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_15, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_15, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_15, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_19
    ui->LeftScene_label_19 = lv_label_create(ui->LeftScene_cont_15);
    lv_label_set_text(ui->LeftScene_label_19, "40%");
    lv_label_set_long_mode(ui->LeftScene_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_19, 140, 128);
    lv_obj_set_size(ui->LeftScene_label_19, 67, 40);

    //Write style for LeftScene_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_19, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_19, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_19, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_15
    ui->LeftScene_img_15 = lv_img_create(ui->LeftScene_cont_15);
    lv_obj_add_flag(ui->LeftScene_img_15, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_15, &_CuratianS2_alpha_59x31);
    lv_img_set_pivot(ui->LeftScene_img_15, 50,50);
    lv_img_set_angle(ui->LeftScene_img_15, 0);
    lv_obj_set_pos(ui->LeftScene_img_15, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_15, 59, 31);

    //Write style for LeftScene_img_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_cont_16
    ui->LeftScene_cont_16 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_16, 5, 249);
    lv_obj_set_size(ui->LeftScene_cont_16, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_16, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_16, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_16, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_16, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_20
    ui->LeftScene_label_20 = lv_label_create(ui->LeftScene_cont_16);
    lv_label_set_text(ui->LeftScene_label_20, "20%");
    lv_label_set_long_mode(ui->LeftScene_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_20, 140, 130);
    lv_obj_set_size(ui->LeftScene_label_20, 61, 35);

    //Write style for LeftScene_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_20, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_20, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_16
    ui->LeftScene_img_16 = lv_img_create(ui->LeftScene_cont_16);
    lv_obj_add_flag(ui->LeftScene_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_16, &_CuratianS1_alpha_59x31);
    lv_img_set_pivot(ui->LeftScene_img_16, 50,50);
    lv_img_set_angle(ui->LeftScene_img_16, 0);
    lv_obj_set_pos(ui->LeftScene_img_16, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_16, 59, 31);

    //Write style for LeftScene_img_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_cont_14
    ui->LeftScene_cont_14 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_14, 350, 15);
    lv_obj_set_size(ui->LeftScene_cont_14, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_14, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_14, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_14, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_14, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_18
    ui->LeftScene_label_18 = lv_label_create(ui->LeftScene_cont_14);
    lv_label_set_text(ui->LeftScene_label_18, "窗帘全关");
    lv_label_set_long_mode(ui->LeftScene_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_18, 85, 127);
    lv_obj_set_size(ui->LeftScene_label_18, 150, 40);

    //Write style for LeftScene_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_18, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_18, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_14
    ui->LeftScene_img_14 = lv_img_create(ui->LeftScene_cont_14);
    lv_obj_add_flag(ui->LeftScene_img_14, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_14, &_CurAllClose_alpha_53x31);
    lv_img_set_pivot(ui->LeftScene_img_14, 50,50);
    lv_img_set_angle(ui->LeftScene_img_14, 0);
    lv_obj_set_pos(ui->LeftScene_img_14, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_14, 53, 31);

    //Write style for LeftScene_img_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_cont_13
    ui->LeftScene_cont_13 = lv_obj_create(ui->LeftScene_tabview_1_tab_1);
    lv_obj_set_pos(ui->LeftScene_cont_13, 5, 15);
    lv_obj_set_size(ui->LeftScene_cont_13, 330, 220);
    lv_obj_set_scrollbar_mode(ui->LeftScene_cont_13, LV_SCROLLBAR_MODE_OFF);

    //Write style for LeftScene_cont_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_cont_13, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_cont_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->LeftScene_cont_13, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->LeftScene_cont_13, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_label_17
    ui->LeftScene_label_17 = lv_label_create(ui->LeftScene_cont_13);
    lv_label_set_text(ui->LeftScene_label_17, "窗帘全开");
    lv_label_set_long_mode(ui->LeftScene_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->LeftScene_label_17, 85, 130);
    lv_obj_set_size(ui->LeftScene_label_17, 150, 40);

    //Write style for LeftScene_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->LeftScene_label_17, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->LeftScene_label_17, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->LeftScene_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->LeftScene_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->LeftScene_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes LeftScene_img_13
    ui->LeftScene_img_13 = lv_img_create(ui->LeftScene_cont_13);
    lv_obj_add_flag(ui->LeftScene_img_13, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->LeftScene_img_13, &_CurAllOpen_alpha_53x31);
    lv_img_set_pivot(ui->LeftScene_img_13, 50,50);
    lv_img_set_angle(ui->LeftScene_img_13, 0);
    lv_obj_set_pos(ui->LeftScene_img_13, 135, 40);
    lv_obj_set_size(ui->LeftScene_img_13, 53, 31);

    //Write style for LeftScene_img_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->LeftScene_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->LeftScene_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->LeftScene_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->LeftScene_img_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of LeftScene.


    //Update current screen layout.
    lv_obj_update_layout(ui->LeftScene);

}
