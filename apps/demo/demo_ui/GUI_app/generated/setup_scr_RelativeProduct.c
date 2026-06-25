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



void setup_scr_RelativeProduct(lv_ui *ui)
{
    //Write codes RelativeProduct
    ui->RelativeProduct = lv_obj_create(NULL);
    lv_obj_set_size(ui->RelativeProduct, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RelativeProduct, LV_SCROLLBAR_MODE_OFF);

    //Write style for RelativeProduct, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RelativeProduct, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RelativeProduct, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RelativeProduct, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_tile
    ui->RelativeProduct_tile = lv_tabview_create(ui->RelativeProduct, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->RelativeProduct_tile, 2, -1);
    lv_obj_set_size(ui->RelativeProduct_tile, 720, 720);
    lv_obj_set_scrollbar_mode(ui->RelativeProduct_tile, LV_SCROLLBAR_MODE_ON);

    //Write style for RelativeProduct_tile, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RelativeProduct_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->RelativeProduct_tile, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->RelativeProduct_tile, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_tile, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_tile, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RelativeProduct_tile, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RelativeProduct_tile, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RelativeProduct_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_tile_extra_btnm_main_default
    static lv_style_t style_RelativeProduct_tile_extra_btnm_main_default;
    ui_init_style(&style_RelativeProduct_tile_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_RelativeProduct_tile_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_RelativeProduct_tile_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_tile_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_RelativeProduct_tile_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_RelativeProduct_tile_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RelativeProduct_tile), &style_RelativeProduct_tile_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_tile_extra_btnm_items_default
    static lv_style_t style_RelativeProduct_tile_extra_btnm_items_default;
    ui_init_style(&style_RelativeProduct_tile_extra_btnm_items_default);

    lv_style_set_text_color(&style_RelativeProduct_tile_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_RelativeProduct_tile_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_RelativeProduct_tile_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RelativeProduct_tile), &style_RelativeProduct_tile_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_RelativeProduct_tile_extra_btnm_items_checked
    static lv_style_t style_RelativeProduct_tile_extra_btnm_items_checked;
    ui_init_style(&style_RelativeProduct_tile_extra_btnm_items_checked);

    lv_style_set_text_color(&style_RelativeProduct_tile_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_RelativeProduct_tile_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_RelativeProduct_tile_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_RelativeProduct_tile_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_RelativeProduct_tile_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_RelativeProduct_tile_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_RelativeProduct_tile_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_tile_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->RelativeProduct_tile), &style_RelativeProduct_tile_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->RelativeProduct_tile_tab_1 = lv_tabview_add_tab(ui->RelativeProduct_tile,"");
    lv_obj_t * RelativeProduct_tile_tab_1_label = lv_label_create(ui->RelativeProduct_tile_tab_1);
    lv_label_set_text(RelativeProduct_tile_tab_1_label, "");

    //Write codes RelativeProduct_list_1
    ui->RelativeProduct_list_1 = lv_list_create(ui->RelativeProduct);
    ui->RelativeProduct_list_1_item0 =lv_list_add_text(ui->RelativeProduct_list_1, "产品型号");
    ui->RelativeProduct_list_1_item1 =lv_list_add_text(ui->RelativeProduct_list_1, "固件版本");
    ui->RelativeProduct_list_1_item2 =lv_list_add_text(ui->RelativeProduct_list_1, "硬件版本");
    ui->RelativeProduct_list_1_item3 =lv_list_add_text(ui->RelativeProduct_list_1, "MAC");
    lv_obj_set_pos(ui->RelativeProduct_list_1, 23, 85);
    lv_obj_set_size(ui->RelativeProduct_list_1, 665, 635);
    lv_obj_set_scrollbar_mode(ui->RelativeProduct_list_1, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_list_1_main_main_default
    static lv_style_t style_RelativeProduct_list_1_main_main_default;
    ui_init_style(&style_RelativeProduct_list_1_main_main_default);

    lv_style_set_pad_top(&style_RelativeProduct_list_1_main_main_default, 0);
    lv_style_set_pad_left(&style_RelativeProduct_list_1_main_main_default, 5);
    lv_style_set_pad_right(&style_RelativeProduct_list_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_RelativeProduct_list_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_RelativeProduct_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_RelativeProduct_list_1_main_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_list_1_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_RelativeProduct_list_1_main_main_default, 0);
    lv_style_set_radius(&style_RelativeProduct_list_1_main_main_default, 3);
    lv_style_set_shadow_width(&style_RelativeProduct_list_1_main_main_default, 0);
    lv_obj_add_style(ui->RelativeProduct_list_1, &style_RelativeProduct_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_list_1_main_scrollbar_default
    static lv_style_t style_RelativeProduct_list_1_main_scrollbar_default;
    ui_init_style(&style_RelativeProduct_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_RelativeProduct_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_RelativeProduct_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_RelativeProduct_list_1_main_scrollbar_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_list_1_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->RelativeProduct_list_1, &style_RelativeProduct_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_list_1_extra_btns_main_default
    static lv_style_t style_RelativeProduct_list_1_extra_btns_main_default;
    ui_init_style(&style_RelativeProduct_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_RelativeProduct_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_RelativeProduct_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_RelativeProduct_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_RelativeProduct_list_1_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_RelativeProduct_list_1_extra_btns_main_default, 2);
    lv_style_set_border_opa(&style_RelativeProduct_list_1_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_RelativeProduct_list_1_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_RelativeProduct_list_1_extra_btns_main_default, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_text_color(&style_RelativeProduct_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_RelativeProduct_list_1_extra_btns_main_default, &lv_font_MiSansNormal_30);
    lv_style_set_text_opa(&style_RelativeProduct_list_1_extra_btns_main_default, 255);
    lv_style_set_radius(&style_RelativeProduct_list_1_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_RelativeProduct_list_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_RelativeProduct_list_1_extra_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_list_1_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_RelativeProduct_list_1_extra_texts_main_default
    static lv_style_t style_RelativeProduct_list_1_extra_texts_main_default;
    ui_init_style(&style_RelativeProduct_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_RelativeProduct_list_1_extra_texts_main_default, 20);
    lv_style_set_pad_left(&style_RelativeProduct_list_1_extra_texts_main_default, 10);
    lv_style_set_pad_right(&style_RelativeProduct_list_1_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_RelativeProduct_list_1_extra_texts_main_default, 24);
    lv_style_set_border_width(&style_RelativeProduct_list_1_extra_texts_main_default, 3);
    lv_style_set_border_opa(&style_RelativeProduct_list_1_extra_texts_main_default, 255);
    lv_style_set_border_color(&style_RelativeProduct_list_1_extra_texts_main_default, lv_color_hex(0x151313));
    lv_style_set_border_side(&style_RelativeProduct_list_1_extra_texts_main_default, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_text_color(&style_RelativeProduct_list_1_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_RelativeProduct_list_1_extra_texts_main_default, &lv_font_MiSansNormal_30);
    lv_style_set_text_opa(&style_RelativeProduct_list_1_extra_texts_main_default, 255);
    lv_style_set_radius(&style_RelativeProduct_list_1_extra_texts_main_default, 0);
    lv_style_set_transform_width(&style_RelativeProduct_list_1_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_RelativeProduct_list_1_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_RelativeProduct_list_1_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_bg_grad_dir(&style_RelativeProduct_list_1_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->RelativeProduct_list_1_item3, &style_RelativeProduct_list_1_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->RelativeProduct_list_1_item2, &style_RelativeProduct_list_1_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->RelativeProduct_list_1_item1, &style_RelativeProduct_list_1_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->RelativeProduct_list_1_item0, &style_RelativeProduct_list_1_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_btn_1
    ui->RelativeProduct_btn_1 = lv_btn_create(ui->RelativeProduct);
    ui->RelativeProduct_btn_1_label = lv_label_create(ui->RelativeProduct_btn_1);
    lv_label_set_text(ui->RelativeProduct_btn_1_label, "设备重启");
    lv_label_set_long_mode(ui->RelativeProduct_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RelativeProduct_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->RelativeProduct_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RelativeProduct_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->RelativeProduct_btn_1, 70, 25);
    lv_obj_set_size(ui->RelativeProduct_btn_1, 152, 32);

    //Write style for RelativeProduct_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RelativeProduct_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RelativeProduct_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_img_1
    ui->RelativeProduct_img_1 = lv_img_create(ui->RelativeProduct);
    lv_obj_add_flag(ui->RelativeProduct_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->RelativeProduct_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->RelativeProduct_img_1, 50,50);
    lv_img_set_angle(ui->RelativeProduct_img_1, 0);
    lv_obj_set_pos(ui->RelativeProduct_img_1, 43, 28);
    lv_obj_set_size(ui->RelativeProduct_img_1, 14, 24);

    //Write style for RelativeProduct_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->RelativeProduct_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->RelativeProduct_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->RelativeProduct_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_label_1
    ui->RelativeProduct_label_1 = lv_label_create(ui->RelativeProduct);
    lv_label_set_text(ui->RelativeProduct_label_1, "LDZNZK-YS-4");
    lv_label_set_long_mode(ui->RelativeProduct_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RelativeProduct_label_1, 440, 110);
    lv_obj_set_size(ui->RelativeProduct_label_1, 230, 32);

    //Write style for RelativeProduct_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_label_2
    ui->RelativeProduct_label_2 = lv_label_create(ui->RelativeProduct);
    lv_label_set_text(ui->RelativeProduct_label_2, "LDZNZK-YS-4");
    lv_label_set_long_mode(ui->RelativeProduct_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RelativeProduct_label_2, 440, 196);
    lv_obj_set_size(ui->RelativeProduct_label_2, 230, 32);

    //Write style for RelativeProduct_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_label_3
    ui->RelativeProduct_label_3 = lv_label_create(ui->RelativeProduct);
    lv_label_set_text(ui->RelativeProduct_label_3, "LDZNZK-YS-4");
    lv_label_set_long_mode(ui->RelativeProduct_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RelativeProduct_label_3, 440, 282);
    lv_obj_set_size(ui->RelativeProduct_label_3, 230, 32);

    //Write style for RelativeProduct_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_label_4
    ui->RelativeProduct_label_4 = lv_label_create(ui->RelativeProduct);
    lv_label_set_text(ui->RelativeProduct_label_4, "LDZNZK-YS-4");
    lv_label_set_long_mode(ui->RelativeProduct_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->RelativeProduct_label_4, 440, 367);
    lv_obj_set_size(ui->RelativeProduct_label_4, 230, 32);

    //Write style for RelativeProduct_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_label_4, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_label_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes RelativeProduct_btn_4
    ui->RelativeProduct_btn_4 = lv_btn_create(ui->RelativeProduct);
    ui->RelativeProduct_btn_4_label = lv_label_create(ui->RelativeProduct_btn_4);
    lv_label_set_text(ui->RelativeProduct_btn_4_label, "");
    lv_label_set_long_mode(ui->RelativeProduct_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->RelativeProduct_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->RelativeProduct_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->RelativeProduct_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->RelativeProduct_btn_4, -6, -15);
    lv_obj_set_size(ui->RelativeProduct_btn_4, 241, 108);

    //Write style for RelativeProduct_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->RelativeProduct_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->RelativeProduct_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->RelativeProduct_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->RelativeProduct_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->RelativeProduct_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->RelativeProduct_btn_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->RelativeProduct_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->RelativeProduct_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of RelativeProduct.


    //Update current screen layout.
    lv_obj_update_layout(ui->RelativeProduct);

    //Init events for screen.
    events_init_RelativeProduct(ui);
}
