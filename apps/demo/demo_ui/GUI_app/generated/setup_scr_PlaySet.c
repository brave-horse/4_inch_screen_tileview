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
    lv_obj_set_pos(ui->PlaySet_List, 21, 91);
    lv_obj_set_size(ui->PlaySet_List, 665, 585);
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

    //Write codes PlaySet_tileview_1
    ui->PlaySet_tileview_1 = lv_tileview_create(ui->PlaySet);
    ui->PlaySet_tileview_1_tile = lv_tileview_add_tile(ui->PlaySet_tileview_1, 0, 0, LV_DIR_RIGHT);
    lv_obj_set_pos(ui->PlaySet_tileview_1, 916, 0);
    lv_obj_set_size(ui->PlaySet_tileview_1, 600, 245);
    lv_obj_set_scrollbar_mode(ui->PlaySet_tileview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for PlaySet_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_1, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for PlaySet_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes PlaySet_line_5
    ui->PlaySet_line_5 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_5[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_5, PlaySet_line_5, 2);
    lv_obj_set_pos(ui->PlaySet_line_5, 45, 55);
    lv_obj_set_size(ui->PlaySet_line_5, 505, 22);

    //Write style for PlaySet_line_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_5, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_5
    ui->PlaySet_label_5 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_5, "15秒");
    lv_label_set_long_mode(ui->PlaySet_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_5, 50, 18);
    lv_obj_set_size(ui->PlaySet_label_5, 100, 32);

    //Write style for PlaySet_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_5
    ui->PlaySet_btn_5 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_5_label = lv_label_create(ui->PlaySet_btn_5);
    lv_label_set_text(ui->PlaySet_btn_5_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_5_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_5, 500, 14);
    lv_obj_set_size(ui->PlaySet_btn_5, 35, 35);

    //Write style for PlaySet_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_5, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_6
    ui->PlaySet_line_6 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_6[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_6, PlaySet_line_6, 2);
    lv_obj_set_pos(ui->PlaySet_line_6, 45, 131);
    lv_obj_set_size(ui->PlaySet_line_6, 505, 22);

    //Write style for PlaySet_line_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_6, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_6
    ui->PlaySet_btn_6 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_6_label = lv_label_create(ui->PlaySet_btn_6);
    lv_label_set_text(ui->PlaySet_btn_6_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_6_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_6_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_6, 500, 89);
    lv_obj_set_size(ui->PlaySet_btn_6, 35, 35);

    //Write style for PlaySet_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_6, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_6, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_6
    ui->PlaySet_label_6 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_6, "30秒");
    lv_label_set_long_mode(ui->PlaySet_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_6, 50, 94);
    lv_obj_set_size(ui->PlaySet_label_6, 100, 32);

    //Write style for PlaySet_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_7
    ui->PlaySet_btn_7 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_7_label = lv_label_create(ui->PlaySet_btn_7);
    lv_label_set_text(ui->PlaySet_btn_7_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_7_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_7_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_7, 500, 164);
    lv_obj_set_size(ui->PlaySet_btn_7, 35, 35);

    //Write style for PlaySet_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_7, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_7, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_7
    ui->PlaySet_line_7 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_7[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_7, PlaySet_line_7, 2);
    lv_obj_set_pos(ui->PlaySet_line_7, 45, 207);
    lv_obj_set_size(ui->PlaySet_line_7, 505, 22);

    //Write style for PlaySet_line_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_7, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_7
    ui->PlaySet_label_7 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_7, "1分钟");
    lv_label_set_long_mode(ui->PlaySet_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_7, 50, 170);
    lv_obj_set_size(ui->PlaySet_label_7, 100, 32);

    //Write style for PlaySet_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_8
    ui->PlaySet_btn_8 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_8_label = lv_label_create(ui->PlaySet_btn_8);
    lv_label_set_text(ui->PlaySet_btn_8_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_8_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_8_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_8, 500, 239);
    lv_obj_set_size(ui->PlaySet_btn_8, 35, 35);

    //Write style for PlaySet_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_8, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_8, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_8, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_8, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_8
    ui->PlaySet_line_8 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_8[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_8, PlaySet_line_8, 2);
    lv_obj_set_pos(ui->PlaySet_line_8, 45, 283);
    lv_obj_set_size(ui->PlaySet_line_8, 505, 22);

    //Write style for PlaySet_line_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_8, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_8
    ui->PlaySet_label_8 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_8, "2分钟\n");
    lv_label_set_long_mode(ui->PlaySet_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_8, 50, 246);
    lv_obj_set_size(ui->PlaySet_label_8, 100, 32);

    //Write style for PlaySet_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_8, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_9
    ui->PlaySet_btn_9 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_9_label = lv_label_create(ui->PlaySet_btn_9);
    lv_label_set_text(ui->PlaySet_btn_9_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_9_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_9_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_9, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_9_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_9, 500, 314);
    lv_obj_set_size(ui->PlaySet_btn_9, 35, 35);

    //Write style for PlaySet_btn_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_9, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_9, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_9, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_9, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_9, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_9
    ui->PlaySet_line_9 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_9[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_9, PlaySet_line_9, 2);
    lv_obj_set_pos(ui->PlaySet_line_9, 45, 359);
    lv_obj_set_size(ui->PlaySet_line_9, 505, 22);

    //Write style for PlaySet_line_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_9, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_9
    ui->PlaySet_label_9 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_9, "5分钟");
    lv_label_set_long_mode(ui->PlaySet_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_9, 50, 322);
    lv_obj_set_size(ui->PlaySet_label_9, 100, 32);

    //Write style for PlaySet_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_9, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_10
    ui->PlaySet_btn_10 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_10_label = lv_label_create(ui->PlaySet_btn_10);
    lv_label_set_text(ui->PlaySet_btn_10_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_10_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_10_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_10, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_10_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_10, 500, 389);
    lv_obj_set_size(ui->PlaySet_btn_10, 35, 35);

    //Write style for PlaySet_btn_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_10, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_10, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_10, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_10, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_10
    ui->PlaySet_line_10 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_10[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_10, PlaySet_line_10, 2);
    lv_obj_set_pos(ui->PlaySet_line_10, 45, 435);
    lv_obj_set_size(ui->PlaySet_line_10, 505, 22);

    //Write style for PlaySet_line_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_10, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_10
    ui->PlaySet_label_10 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_10, "10分钟");
    lv_label_set_long_mode(ui->PlaySet_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_10, 50, 398);
    lv_obj_set_size(ui->PlaySet_label_10, 100, 32);

    //Write style for PlaySet_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_11
    ui->PlaySet_line_11 = lv_line_create(ui->PlaySet_tileview_1_tile);
    static lv_point_t PlaySet_line_11[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_11, PlaySet_line_11, 2);
    lv_obj_set_pos(ui->PlaySet_line_11, 45, 511);
    lv_obj_set_size(ui->PlaySet_line_11, 505, 22);

    //Write style for PlaySet_line_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_11, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_11, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_11
    ui->PlaySet_btn_11 = lv_btn_create(ui->PlaySet_tileview_1_tile);
    ui->PlaySet_btn_11_label = lv_label_create(ui->PlaySet_btn_11);
    lv_label_set_text(ui->PlaySet_btn_11_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_11_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_11_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_11, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_11_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_11, 500, 464);
    lv_obj_set_size(ui->PlaySet_btn_11, 35, 35);

    //Write style for PlaySet_btn_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_11, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_11, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_11, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_11, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_11, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_11
    ui->PlaySet_label_11 = lv_label_create(ui->PlaySet_tileview_1_tile);
    lv_label_set_text(ui->PlaySet_label_11, "永久");
    lv_label_set_long_mode(ui->PlaySet_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_11, 50, 474);
    lv_obj_set_size(ui->PlaySet_label_11, 100, 32);

    //Write style for PlaySet_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_11, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_11, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_tileview_2
    ui->PlaySet_tileview_2 = lv_tileview_create(ui->PlaySet);
    ui->PlaySet_tileview_2_tile = lv_tileview_add_tile(ui->PlaySet_tileview_2, 0, 0, LV_DIR_RIGHT);
    lv_obj_set_pos(ui->PlaySet_tileview_2, 1886, 42);
    lv_obj_set_size(ui->PlaySet_tileview_2, 600, 245);
    lv_obj_set_scrollbar_mode(ui->PlaySet_tileview_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for PlaySet_tileview_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_2, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_tileview_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for PlaySet_tileview_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_2, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_2, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_2, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_2, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes PlaySet_line_18
    ui->PlaySet_line_18 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_18[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_18, PlaySet_line_18, 2);
    lv_obj_set_pos(ui->PlaySet_line_18, 45, 55);
    lv_obj_set_size(ui->PlaySet_line_18, 505, 22);

    //Write style for PlaySet_line_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_18, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_18, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_18
    ui->PlaySet_label_18 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_18, "熄屏");
    lv_label_set_long_mode(ui->PlaySet_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_18, 50, 16);
    lv_obj_set_size(ui->PlaySet_label_18, 100, 32);

    //Write style for PlaySet_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_18, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_18, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_18
    ui->PlaySet_btn_18 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_18_label = lv_label_create(ui->PlaySet_btn_18);
    lv_label_set_text(ui->PlaySet_btn_18_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_18_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_18_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_18, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_18_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_18, 500, 14);
    lv_obj_set_size(ui->PlaySet_btn_18, 35, 35);

    //Write style for PlaySet_btn_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_18, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_18, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_18, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_18, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_18, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_18, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_17
    ui->PlaySet_line_17 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_17[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_17, PlaySet_line_17, 2);
    lv_obj_set_pos(ui->PlaySet_line_17, 45, 131);
    lv_obj_set_size(ui->PlaySet_line_17, 505, 22);

    //Write style for PlaySet_line_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_17, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_17, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_17
    ui->PlaySet_btn_17 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_17_label = lv_label_create(ui->PlaySet_btn_17);
    lv_label_set_text(ui->PlaySet_btn_17_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_17_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_17_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_17, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_17_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_17, 500, 89);
    lv_obj_set_size(ui->PlaySet_btn_17, 35, 35);

    //Write style for PlaySet_btn_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_17, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_17, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_17, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_17, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_17, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_17, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_17
    ui->PlaySet_label_17 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_17, "屏保");
    lv_label_set_long_mode(ui->PlaySet_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_17, 50, 94);
    lv_obj_set_size(ui->PlaySet_label_17, 100, 32);

    //Write style for PlaySet_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_17, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_17, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_16
    ui->PlaySet_btn_16 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_16_label = lv_label_create(ui->PlaySet_btn_16);
    lv_label_set_text(ui->PlaySet_btn_16_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_16_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_16_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_16, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_16_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_16, 500, 164);
    lv_obj_set_size(ui->PlaySet_btn_16, 35, 35);

    //Write style for PlaySet_btn_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_16, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_16, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_16, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_16, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_16, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_16
    ui->PlaySet_line_16 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_16[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_16, PlaySet_line_16, 2);
    lv_obj_set_pos(ui->PlaySet_line_16, 45, 207);
    lv_obj_set_size(ui->PlaySet_line_16, 505, 22);

    //Write style for PlaySet_line_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_16, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_16, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_16
    ui->PlaySet_label_16 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_16, "场景");
    lv_label_set_long_mode(ui->PlaySet_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_16, 50, 170);
    lv_obj_set_size(ui->PlaySet_label_16, 100, 32);

    //Write style for PlaySet_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_16, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_16, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_15
    ui->PlaySet_btn_15 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_15_label = lv_label_create(ui->PlaySet_btn_15);
    lv_label_set_text(ui->PlaySet_btn_15_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_15_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_15_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_15, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_15_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_15, 500, 239);
    lv_obj_set_size(ui->PlaySet_btn_15, 35, 35);

    //Write style for PlaySet_btn_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_15, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_15, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_15, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_15, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_15, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_15, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_15
    ui->PlaySet_line_15 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_15[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_15, PlaySet_line_15, 2);
    lv_obj_set_pos(ui->PlaySet_line_15, 45, 283);
    lv_obj_set_size(ui->PlaySet_line_15, 505, 22);

    //Write style for PlaySet_line_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_15, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_15, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_15
    ui->PlaySet_label_15 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_15, "开关\n");
    lv_label_set_long_mode(ui->PlaySet_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_15, 50, 246);
    lv_obj_set_size(ui->PlaySet_label_15, 100, 32);

    //Write style for PlaySet_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_15, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_15, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_14
    ui->PlaySet_btn_14 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_14_label = lv_label_create(ui->PlaySet_btn_14);
    lv_label_set_text(ui->PlaySet_btn_14_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_14_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_14_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_14, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_14_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_14, 500, 314);
    lv_obj_set_size(ui->PlaySet_btn_14, 35, 35);

    //Write style for PlaySet_btn_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_14, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_14, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_14, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_14, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_14, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_14, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_14
    ui->PlaySet_line_14 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_14[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_14, PlaySet_line_14, 2);
    lv_obj_set_pos(ui->PlaySet_line_14, 45, 359);
    lv_obj_set_size(ui->PlaySet_line_14, 505, 22);

    //Write style for PlaySet_line_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_14, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_14, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_14
    ui->PlaySet_label_14 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_14, "设备");
    lv_label_set_long_mode(ui->PlaySet_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_14, 50, 322);
    lv_obj_set_size(ui->PlaySet_label_14, 100, 32);

    //Write style for PlaySet_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_14, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_14, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_13
    ui->PlaySet_btn_13 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_13_label = lv_label_create(ui->PlaySet_btn_13);
    lv_label_set_text(ui->PlaySet_btn_13_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_13_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_13_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_13, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_13_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_13, 500, 389);
    lv_obj_set_size(ui->PlaySet_btn_13, 35, 35);

    //Write style for PlaySet_btn_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_13, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_13, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_13, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_13, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_13, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_13
    ui->PlaySet_line_13 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_13[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_13, PlaySet_line_13, 2);
    lv_obj_set_pos(ui->PlaySet_line_13, 45, 435);
    lv_obj_set_size(ui->PlaySet_line_13, 505, 22);

    //Write style for PlaySet_line_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_13, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_13, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_13
    ui->PlaySet_label_13 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_13, "灯光");
    lv_label_set_long_mode(ui->PlaySet_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_13, 50, 398);
    lv_obj_set_size(ui->PlaySet_label_13, 100, 32);

    //Write style for PlaySet_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_13, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_13, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_12
    ui->PlaySet_line_12 = lv_line_create(ui->PlaySet_tileview_2_tile);
    static lv_point_t PlaySet_line_12[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_12, PlaySet_line_12, 2);
    lv_obj_set_pos(ui->PlaySet_line_12, 45, 511);
    lv_obj_set_size(ui->PlaySet_line_12, 505, 22);

    //Write style for PlaySet_line_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_12, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_12
    ui->PlaySet_btn_12 = lv_btn_create(ui->PlaySet_tileview_2_tile);
    ui->PlaySet_btn_12_label = lv_label_create(ui->PlaySet_btn_12);
    lv_label_set_text(ui->PlaySet_btn_12_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_12_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_12_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_12, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_12_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_12, 500, 464);
    lv_obj_set_size(ui->PlaySet_btn_12, 35, 35);

    //Write style for PlaySet_btn_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_12, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_12, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_12, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_12, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_12, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_12
    ui->PlaySet_label_12 = lv_label_create(ui->PlaySet_tileview_2_tile);
    lv_label_set_text(ui->PlaySet_label_12, "窗帘");
    lv_label_set_long_mode(ui->PlaySet_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_12, 50, 474);
    lv_obj_set_size(ui->PlaySet_label_12, 100, 32);

    //Write style for PlaySet_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_12, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_12, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_tileview_3
    ui->PlaySet_tileview_3 = lv_tileview_create(ui->PlaySet);
    ui->PlaySet_tileview_3_tile = lv_tileview_add_tile(ui->PlaySet_tileview_3, 0, 0, LV_DIR_RIGHT);
    lv_obj_set_pos(ui->PlaySet_tileview_3, 2662, 16);
    lv_obj_set_size(ui->PlaySet_tileview_3, 600, 245);
    lv_obj_set_scrollbar_mode(ui->PlaySet_tileview_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for PlaySet_tileview_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_3, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_tileview_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for PlaySet_tileview_3, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_tileview_3, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->PlaySet_tileview_3, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->PlaySet_tileview_3, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_tileview_3, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes PlaySet_line_25
    ui->PlaySet_line_25 = lv_line_create(ui->PlaySet_tileview_3_tile);
    static lv_point_t PlaySet_line_25[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_25, PlaySet_line_25, 2);
    lv_obj_set_pos(ui->PlaySet_line_25, 45, 55);
    lv_obj_set_size(ui->PlaySet_line_25, 505, 22);

    //Write style for PlaySet_line_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_25, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_25, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_25, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_25
    ui->PlaySet_label_25 = lv_label_create(ui->PlaySet_tileview_3_tile);
    lv_label_set_text(ui->PlaySet_label_25, "关闭");
    lv_label_set_long_mode(ui->PlaySet_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_25, 50, 18);
    lv_obj_set_size(ui->PlaySet_label_25, 100, 32);

    //Write style for PlaySet_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_25, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_25, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_25, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_25
    ui->PlaySet_btn_25 = lv_btn_create(ui->PlaySet_tileview_3_tile);
    ui->PlaySet_btn_25_label = lv_label_create(ui->PlaySet_btn_25);
    lv_label_set_text(ui->PlaySet_btn_25_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_25_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_25_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_25, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_25_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_25, 500, 14);
    lv_obj_set_size(ui->PlaySet_btn_25, 35, 35);

    //Write style for PlaySet_btn_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_25, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_25, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_25, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_25, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_25, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_25, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_25, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_24
    ui->PlaySet_line_24 = lv_line_create(ui->PlaySet_tileview_3_tile);
    static lv_point_t PlaySet_line_24[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_24, PlaySet_line_24, 2);
    lv_obj_set_pos(ui->PlaySet_line_24, 45, 131);
    lv_obj_set_size(ui->PlaySet_line_24, 505, 22);

    //Write style for PlaySet_line_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_24, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_24, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_24, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_24
    ui->PlaySet_btn_24 = lv_btn_create(ui->PlaySet_tileview_3_tile);
    ui->PlaySet_btn_24_label = lv_label_create(ui->PlaySet_btn_24);
    lv_label_set_text(ui->PlaySet_btn_24_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_24_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_24_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_24, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_24_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_24, 500, 89);
    lv_obj_set_size(ui->PlaySet_btn_24, 35, 35);

    //Write style for PlaySet_btn_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_24, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_24, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_24, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_24, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_24, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_24, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_24
    ui->PlaySet_label_24 = lv_label_create(ui->PlaySet_tileview_3_tile);
    lv_label_set_text(ui->PlaySet_label_24, "近");
    lv_label_set_long_mode(ui->PlaySet_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_24, 50, 94);
    lv_obj_set_size(ui->PlaySet_label_24, 100, 32);

    //Write style for PlaySet_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_24, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_24, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_23
    ui->PlaySet_btn_23 = lv_btn_create(ui->PlaySet_tileview_3_tile);
    ui->PlaySet_btn_23_label = lv_label_create(ui->PlaySet_btn_23);
    lv_label_set_text(ui->PlaySet_btn_23_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_23_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_23_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_23, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_23_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_23, 500, 164);
    lv_obj_set_size(ui->PlaySet_btn_23, 35, 35);

    //Write style for PlaySet_btn_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_23, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_23, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_23, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_23, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_23, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_23
    ui->PlaySet_line_23 = lv_line_create(ui->PlaySet_tileview_3_tile);
    static lv_point_t PlaySet_line_23[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_23, PlaySet_line_23, 2);
    lv_obj_set_pos(ui->PlaySet_line_23, 45, 207);
    lv_obj_set_size(ui->PlaySet_line_23, 505, 22);

    //Write style for PlaySet_line_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_23, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_23, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_23
    ui->PlaySet_label_23 = lv_label_create(ui->PlaySet_tileview_3_tile);
    lv_label_set_text(ui->PlaySet_label_23, "中");
    lv_label_set_long_mode(ui->PlaySet_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_23, 50, 170);
    lv_obj_set_size(ui->PlaySet_label_23, 100, 32);

    //Write style for PlaySet_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_23, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_23, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_btn_22
    ui->PlaySet_btn_22 = lv_btn_create(ui->PlaySet_tileview_3_tile);
    ui->PlaySet_btn_22_label = lv_label_create(ui->PlaySet_btn_22);
    lv_label_set_text(ui->PlaySet_btn_22_label, "");
    lv_label_set_long_mode(ui->PlaySet_btn_22_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->PlaySet_btn_22_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->PlaySet_btn_22, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->PlaySet_btn_22_label, LV_PCT(100));
    lv_obj_set_pos(ui->PlaySet_btn_22, 500, 239);
    lv_obj_set_size(ui->PlaySet_btn_22, 35, 35);

    //Write style for PlaySet_btn_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->PlaySet_btn_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->PlaySet_btn_22, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->PlaySet_btn_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->PlaySet_btn_22, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->PlaySet_btn_22, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_btn_22, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_btn_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_btn_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_btn_22, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_btn_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_btn_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_line_22
    ui->PlaySet_line_22 = lv_line_create(ui->PlaySet_tileview_3_tile);
    static lv_point_t PlaySet_line_22[] = {{500, 0},{0, 0},};
    lv_line_set_points(ui->PlaySet_line_22, PlaySet_line_22, 2);
    lv_obj_set_pos(ui->PlaySet_line_22, 45, 283);
    lv_obj_set_size(ui->PlaySet_line_22, 505, 22);

    //Write style for PlaySet_line_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->PlaySet_line_22, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->PlaySet_line_22, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->PlaySet_line_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->PlaySet_line_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_22
    ui->PlaySet_label_22 = lv_label_create(ui->PlaySet_tileview_3_tile);
    lv_label_set_text(ui->PlaySet_label_22, "远\n");
    lv_label_set_long_mode(ui->PlaySet_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_22, 50, 246);
    lv_obj_set_size(ui->PlaySet_label_22, 100, 32);

    //Write style for PlaySet_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_22, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_22, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_1
    ui->PlaySet_label_1 = lv_label_create(ui->PlaySet);
    lv_label_set_text(ui->PlaySet_label_1, "30秒");
    lv_label_set_long_mode(ui->PlaySet_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_1, 533, 114);
    lv_obj_set_size(ui->PlaySet_label_1, 100, 32);

    //Write style for PlaySet_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_2
    ui->PlaySet_label_2 = lv_label_create(ui->PlaySet);
    lv_label_set_text(ui->PlaySet_label_2, "熄屏");
    lv_label_set_long_mode(ui->PlaySet_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_2, 533, 203);
    lv_obj_set_size(ui->PlaySet_label_2, 100, 32);

    //Write style for PlaySet_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes PlaySet_label_3
    ui->PlaySet_label_3 = lv_label_create(ui->PlaySet);
    lv_label_set_text(ui->PlaySet_label_3, "关闭");
    lv_label_set_long_mode(ui->PlaySet_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->PlaySet_label_3, 533, 292);
    lv_obj_set_size(ui->PlaySet_label_3, 100, 32);

    //Write style for PlaySet_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->PlaySet_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->PlaySet_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->PlaySet_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->PlaySet_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->PlaySet_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of PlaySet.


    //Update current screen layout.
    lv_obj_update_layout(ui->PlaySet);

    //Init events for screen.
    events_init_PlaySet(ui);
}
