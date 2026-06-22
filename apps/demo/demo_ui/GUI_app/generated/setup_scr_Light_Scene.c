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



void setup_scr_Light_Scene(lv_ui *ui)
{
    //Write codes Light_Scene
    ui->Light_Scene = lv_obj_create(NULL);
    lv_obj_set_size(ui->Light_Scene, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Light_Scene, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Light_Scene, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_tabview_1
    ui->Light_Scene_tabview_1 = lv_tabview_create(ui->Light_Scene, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Light_Scene_tabview_1, 0, 0);
    lv_obj_set_size(ui->Light_Scene_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Light_Scene_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Light_Scene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Light_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Light_Scene_tabview_1_extra_btnm_main_default
    static lv_style_t style_Light_Scene_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Light_Scene_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Light_Scene_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Light_Scene_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Light_Scene_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Light_Scene_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Light_Scene_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Light_Scene_tabview_1), &style_Light_Scene_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Light_Scene_tabview_1_extra_btnm_items_default
    static lv_style_t style_Light_Scene_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Light_Scene_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Light_Scene_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Light_Scene_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Light_Scene_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Light_Scene_tabview_1), &style_Light_Scene_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Light_Scene_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Light_Scene_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Light_Scene_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Light_Scene_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Light_Scene_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Light_Scene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Light_Scene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Light_Scene_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Light_Scene_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Light_Scene_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Light_Scene_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Light_Scene_tabview_1), &style_Light_Scene_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Light_Scene_tabview_1_tab_1 = lv_tabview_add_tab(ui->Light_Scene_tabview_1,"");
    lv_obj_t * Light_Scene_tabview_1_tab_1_label = lv_label_create(ui->Light_Scene_tabview_1_tab_1);
    lv_label_set_text(Light_Scene_tabview_1_tab_1_label, "");

    //Write codes Light_Scene_cont_6
    ui->Light_Scene_cont_6 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_6, 345, 400);
    lv_obj_set_size(ui->Light_Scene_cont_6, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_6, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_6, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_6
    ui->Light_Scene_label_6 = lv_label_create(ui->Light_Scene_cont_6);
    lv_label_set_text(ui->Light_Scene_label_6, "情景模式4");
    lv_label_set_long_mode(ui->Light_Scene_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_6, 85, 128);
    lv_obj_set_size(ui->Light_Scene_label_6, 160, 35);

    //Write style for Light_Scene_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_6
    ui->Light_Scene_img_6 = lv_img_create(ui->Light_Scene_cont_6);
    lv_obj_add_flag(ui->Light_Scene_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_6, &_LightScene4_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_6, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_6, 0);
    lv_obj_set_pos(ui->Light_Scene_img_6, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_6, 48, 48);

    //Write style for Light_Scene_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_cont_5
    ui->Light_Scene_cont_5 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_5, 0, 400);
    lv_obj_set_size(ui->Light_Scene_cont_5, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_5, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_5, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_9
    ui->Light_Scene_label_9 = lv_label_create(ui->Light_Scene_cont_5);
    lv_label_set_text(ui->Light_Scene_label_9, "情景模式3");
    lv_label_set_long_mode(ui->Light_Scene_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_9, 85, 122);
    lv_obj_set_size(ui->Light_Scene_label_9, 150, 40);

    //Write style for Light_Scene_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_9, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_5
    ui->Light_Scene_img_5 = lv_img_create(ui->Light_Scene_cont_5);
    lv_obj_add_flag(ui->Light_Scene_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_5, &_LightScene3_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_5, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_5, 0);
    lv_obj_set_pos(ui->Light_Scene_img_5, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_5, 48, 48);

    //Write style for Light_Scene_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_cont_4
    ui->Light_Scene_cont_4 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_4, 0, 200);
    lv_obj_set_size(ui->Light_Scene_cont_4, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_4, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_4, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_4
    ui->Light_Scene_label_4 = lv_label_create(ui->Light_Scene_cont_4);
    lv_label_set_text(ui->Light_Scene_label_4, "情景模式1");
    lv_label_set_long_mode(ui->Light_Scene_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_4, 85, 134);
    lv_obj_set_size(ui->Light_Scene_label_4, 150, 40);

    //Write style for Light_Scene_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_4, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_4
    ui->Light_Scene_img_4 = lv_img_create(ui->Light_Scene_cont_4);
    lv_obj_add_flag(ui->Light_Scene_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_4, &_LightScene1_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_4, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_4, 0);
    lv_obj_set_pos(ui->Light_Scene_img_4, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_4, 48, 48);

    //Write style for Light_Scene_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_cont_3
    ui->Light_Scene_cont_3 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_3, 344, 200);
    lv_obj_set_size(ui->Light_Scene_cont_3, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_3, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_3, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_3
    ui->Light_Scene_label_3 = lv_label_create(ui->Light_Scene_cont_3);
    lv_label_set_text(ui->Light_Scene_label_3, "情景模式2");
    lv_label_set_long_mode(ui->Light_Scene_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_3, 85, 130);
    lv_obj_set_size(ui->Light_Scene_label_3, 150, 40);

    //Write style for Light_Scene_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_3
    ui->Light_Scene_img_3 = lv_img_create(ui->Light_Scene_cont_3);
    lv_obj_add_flag(ui->Light_Scene_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_3, &_LightScene2_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_3, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_3, 0);
    lv_obj_set_pos(ui->Light_Scene_img_3, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_3, 48, 48);

    //Write style for Light_Scene_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_cont_2
    ui->Light_Scene_cont_2 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_2, 344, 1);
    lv_obj_set_size(ui->Light_Scene_cont_2, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_2, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_2, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_8
    ui->Light_Scene_label_8 = lv_label_create(ui->Light_Scene_cont_2);
    lv_label_set_text(ui->Light_Scene_label_8, "灯光全关");
    lv_label_set_long_mode(ui->Light_Scene_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_8, 85, 127);
    lv_obj_set_size(ui->Light_Scene_label_8, 150, 40);

    //Write style for Light_Scene_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_8, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_2
    ui->Light_Scene_img_2 = lv_img_create(ui->Light_Scene_cont_2);
    lv_obj_add_flag(ui->Light_Scene_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_2, &_onoff_off_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_2, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_2, 0);
    lv_obj_set_pos(ui->Light_Scene_img_2, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_2, 48, 48);

    //Write style for Light_Scene_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->Light_Scene_img_2, lv_color_hex(0xc62a2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_cont_1
    ui->Light_Scene_cont_1 = lv_obj_create(ui->Light_Scene_tabview_1_tab_1);
    lv_obj_set_pos(ui->Light_Scene_cont_1, 0, 1);
    lv_obj_set_size(ui->Light_Scene_cont_1, 330, 185);
    lv_obj_set_scrollbar_mode(ui->Light_Scene_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Light_Scene_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_cont_1, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Light_Scene_cont_1, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Light_Scene_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_7
    ui->Light_Scene_label_7 = lv_label_create(ui->Light_Scene_cont_1);
    lv_label_set_text(ui->Light_Scene_label_7, "灯光全开");
    lv_label_set_long_mode(ui->Light_Scene_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_7, 85, 130);
    lv_obj_set_size(ui->Light_Scene_label_7, 150, 40);

    //Write style for Light_Scene_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_img_1
    ui->Light_Scene_img_1 = lv_img_create(ui->Light_Scene_cont_1);
    lv_obj_add_flag(ui->Light_Scene_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Light_Scene_img_1, &_onoff_on_alpha_48x48);
    lv_img_set_pivot(ui->Light_Scene_img_1, 50,50);
    lv_img_set_angle(ui->Light_Scene_img_1, 0);
    lv_obj_set_pos(ui->Light_Scene_img_1, 135, 40);
    lv_obj_set_size(ui->Light_Scene_img_1, 48, 48);

    //Write style for Light_Scene_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Light_Scene_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Light_Scene_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Light_Scene_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Light_Scene_label_10
    ui->Light_Scene_label_10 = lv_label_create(ui->Light_Scene);
    lv_label_set_text(ui->Light_Scene_label_10, "灯光情景");
    lv_label_set_long_mode(ui->Light_Scene_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Light_Scene_label_10, 43, 25);
    lv_obj_set_size(ui->Light_Scene_label_10, 125, 32);

    //Write style for Light_Scene_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Light_Scene_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Light_Scene_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Light_Scene_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Light_Scene_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Light_Scene_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Light_Scene.


    //Update current screen layout.
    lv_obj_update_layout(ui->Light_Scene);

}
