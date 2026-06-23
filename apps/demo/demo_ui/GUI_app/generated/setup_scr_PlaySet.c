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



void setup_scr_PlaySet(lv_ui *ui)
{
    //Write codes PlaySet
    ui->PlaySet = lv_obj_create(NULL);
    lv_obj_set_size(ui->PlaySet, 720, 720);
    lv_obj_set_scrollbar_mode(ui->PlaySet, LV_SCROLLBAR_MODE_OFF);

    //Write style for PlaySet, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_tabview_1
    ui->PlaySet_tabview_1 = lv_tabview_create(ui->PlaySet, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->PlaySet_tabview_1, 0, 0);
    lv_obj_set_size(ui->PlaySet_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->PlaySet_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for PlaySet_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_tabview_1_extra_btnm_main_default
    static lv_style_t style_PlaySet_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_PlaySet_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_PlaySet_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_PlaySet_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_PlaySet_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_PlaySet_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_PlaySet_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->PlaySet_tabview_1), &style_PlaySet_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_tabview_1_extra_btnm_items_default
    static lv_style_t style_PlaySet_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_PlaySet_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_PlaySet_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_PlaySet_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_PlaySet_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->PlaySet_tabview_1), &style_PlaySet_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_PlaySet_tabview_1_extra_btnm_items_checked
    static lv_style_t style_PlaySet_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_PlaySet_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_PlaySet_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_PlaySet_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_PlaySet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_PlaySet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_PlaySet_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_PlaySet_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_PlaySet_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_PlaySet_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->PlaySet_tabview_1), &style_PlaySet_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->PlaySet_tabview_1_tab_1 = lv_tabview_add_tab(ui->PlaySet_tabview_1,"");
    lv_obj_t * PlaySet_tabview_1_tab_1_label = lv_label_create(ui->PlaySet_tabview_1_tab_1);
    lv_label_set_text(PlaySet_tabview_1_tab_1_label, "");

    //Write codes PlaySet_cont_1
    ui->PlaySet_cont_1 = lv_obj_create(ui->PlaySet);
    lv_obj_set_pos(ui->PlaySet_cont_1, 0, 85);
    lv_obj_set_size(ui->PlaySet_cont_1, 720, 630);
    lv_obj_set_scrollbar_mode(ui->PlaySet_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for PlaySet_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_cont_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_1
    ui->PlaySet_btn_1 = lv_btn_create(ui->PlaySet);
    ui->PlaySet_btn_1_label = lv_label_create(ui->PlaySet_btn_1);
    lv_label_set_text(ui->PlaySet_btn_1_label, "显示设置");
    lv_label_set_long_mode(ui->PlaySet_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_1, 70, 25);
    lv_obj_set_size(ui->PlaySet_btn_1, 152, 32);

    //Write style for PlaySet_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_List
    ui->PlaySet_List = lv_list_create(ui->PlaySet);
    ui->PlaySet_List_item0 =lv_list_add_text(ui->PlaySet_List, "延时进入待机时间");
    ui->PlaySet_List_item1 =lv_list_add_text(ui->PlaySet_List, "待机显示");
    ui->PlaySet_List_item2 =lv_list_add_text(ui->PlaySet_List, "接近亮屏");
    lv_obj_set_pos(ui->PlaySet_List, 25, 85);
    lv_obj_set_size(ui->PlaySet_List, 665, 635);
    lv_obj_set_scrollbar_mode(ui->PlaySet_List, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_List_main_main_default
    static lv_style_t style_PlaySet_List_main_main_default;
    ui_init_style(&style_PlaySet_List_main_main_default);

    lv_style_set_pad_top(&style_PlaySet_List_main_main_default, 0);
    lv_style_set_pad_left(&style_PlaySet_List_main_main_default, 5);
    lv_style_set_pad_right(&style_PlaySet_List_main_main_default, 0);
    lv_style_set_pad_bottom(&style_PlaySet_List_main_main_default, 0);
    lv_style_set_bg_opa(&style_PlaySet_List_main_main_default, 255);
    lv_style_set_bg_color(&style_PlaySet_List_main_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_PlaySet_List_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_PlaySet_List_main_main_default, 0);
    lv_style_set_radius(&style_PlaySet_List_main_main_default, 3);
    lv_style_set_shadow_width(&style_PlaySet_List_main_main_default, 0);
    lv_obj_add_style(ui->PlaySet_List, &style_PlaySet_List_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_List_main_scrollbar_default
    static lv_style_t style_PlaySet_List_main_scrollbar_default;
    ui_init_style(&style_PlaySet_List_main_scrollbar_default);

    lv_style_set_radius(&style_PlaySet_List_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_PlaySet_List_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_PlaySet_List_main_scrollbar_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_PlaySet_List_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->PlaySet_List, &style_PlaySet_List_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_List_extra_btns_main_default
    static lv_style_t style_PlaySet_List_extra_btns_main_default;
    ui_init_style(&style_PlaySet_List_extra_btns_main_default);

    lv_style_set_pad_top(&style_PlaySet_List_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_PlaySet_List_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_PlaySet_List_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_PlaySet_List_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_PlaySet_List_extra_btns_main_default, 2);
    lv_style_set_border_opa(&style_PlaySet_List_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_PlaySet_List_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_PlaySet_List_extra_btns_main_default, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_text_color(&style_PlaySet_List_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_PlaySet_List_extra_btns_main_default, &lv_font_MiSansNormal_30);
    lv_style_set_text_opa(&style_PlaySet_List_extra_btns_main_default, 255);
    lv_style_set_radius(&style_PlaySet_List_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_PlaySet_List_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_PlaySet_List_extra_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_PlaySet_List_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_PlaySet_List_extra_texts_main_default
    static lv_style_t style_PlaySet_List_extra_texts_main_default;
    ui_init_style(&style_PlaySet_List_extra_texts_main_default);

    lv_style_set_pad_top(&style_PlaySet_List_extra_texts_main_default, 20);
    lv_style_set_pad_left(&style_PlaySet_List_extra_texts_main_default, 10);
    lv_style_set_pad_right(&style_PlaySet_List_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_PlaySet_List_extra_texts_main_default, 24);
    lv_style_set_border_width(&style_PlaySet_List_extra_texts_main_default, 3);
    lv_style_set_border_opa(&style_PlaySet_List_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_PlaySet_List_extra_texts_main_default, lv_color_hex(0x151313));
    lv_style_set_border_side(&style_PlaySet_List_extra_texts_main_default, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_text_color(&style_PlaySet_List_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_PlaySet_List_extra_texts_main_default, &lv_font_MiSansNormal_30);
    lv_style_set_text_opa(&style_PlaySet_List_extra_texts_main_default, 255);
    lv_style_set_radius(&style_PlaySet_List_extra_texts_main_default, 0);
    lv_style_set_transform_width(&style_PlaySet_List_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_PlaySet_List_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_PlaySet_List_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_PlaySet_List_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->PlaySet_List_item2, &style_PlaySet_List_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->PlaySet_List_item1, &style_PlaySet_List_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->PlaySet_List_item0, &style_PlaySet_List_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_2
    ui->PlaySet_btn_2 = lv_btn_create(ui->PlaySet);
    ui->PlaySet_btn_2_label = lv_label_create(ui->PlaySet_btn_2);
    lv_label_set_text(ui->PlaySet_btn_2_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_2, -7, -12);
    lv_obj_set_size(ui->PlaySet_btn_2, 248, 103);

    //Write style for PlaySet_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_img_1
    ui->PlaySet_img_1 = lv_img_create(ui->PlaySet);
    lv_obj_add_flag(ui->PlaySet_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->PlaySet_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->PlaySet_img_1, 50,50);
    lv_img_set_angle(ui->PlaySet_img_1, 0);
    lv_obj_set_pos(ui->PlaySet_img_1, 43, 28);
    lv_obj_set_size(ui->PlaySet_img_1, 14, 24);

    //Write style for PlaySet_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->PlaySet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->PlaySet_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->PlaySet_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_img_2
    ui->PlaySet_img_2 = lv_img_create(ui->PlaySet);
    lv_obj_add_flag(ui->PlaySet_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->PlaySet_img_2, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->PlaySet_img_2, 0,0);
    lv_img_set_angle(ui->PlaySet_img_2, 1800);
    lv_obj_set_pos(ui->PlaySet_img_2, 667, 142);
    lv_obj_set_size(ui->PlaySet_img_2, 14, 24);

    //Write style for PlaySet_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->PlaySet_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->PlaySet_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->PlaySet_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_img_3
    ui->PlaySet_img_3 = lv_img_create(ui->PlaySet);
    lv_obj_add_flag(ui->PlaySet_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->PlaySet_img_3, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->PlaySet_img_3, 0,0);
    lv_img_set_angle(ui->PlaySet_img_3, 1800);
    lv_obj_set_pos(ui->PlaySet_img_3, 670, 322);
    lv_obj_set_size(ui->PlaySet_img_3, 14, 24);

    //Write style for PlaySet_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->PlaySet_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->PlaySet_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->PlaySet_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_img_4
    ui->PlaySet_img_4 = lv_img_create(ui->PlaySet);
    lv_obj_add_flag(ui->PlaySet_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->PlaySet_img_4, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->PlaySet_img_4, 0,0);
    lv_img_set_angle(ui->PlaySet_img_4, 1800);
    lv_obj_set_pos(ui->PlaySet_img_4, 667, 232);
    lv_obj_set_size(ui->PlaySet_img_4, 14, 24);

    //Write style for PlaySet_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->PlaySet_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->PlaySet_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->PlaySet_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of PlaySet.


    //Update current screen layout.
    lv_obj_update_layout(ui->PlaySet);

    //Init events for screen.
    events_init_PlaySet(ui);
}
