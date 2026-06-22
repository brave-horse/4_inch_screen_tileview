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



void setup_scr_Reset(lv_ui *ui)
{
    //Write codes Reset
    ui->Reset = lv_obj_create(NULL);
    lv_obj_set_size(ui->Reset, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Reset, LV_SCROLLBAR_MODE_OFF);

    //Write style for Reset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Reset, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Reset, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_tile
    ui->Reset_tile = lv_tabview_create(ui->Reset, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Reset_tile, 0, 0);
    lv_obj_set_size(ui->Reset_tile, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Reset_tile, LV_SCROLLBAR_MODE_ON);

    //Write style for Reset_tile, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Reset_tile, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Reset_tile, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_tile, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_tile, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Reset_tile, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Reset_tile, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Reset_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Reset_tile_extra_btnm_main_default
    static lv_style_t style_Reset_tile_extra_btnm_main_default;
    ui_init_style(&style_Reset_tile_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Reset_tile_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Reset_tile_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Reset_tile_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Reset_tile_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Reset_tile_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Reset_tile), &style_Reset_tile_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Reset_tile_extra_btnm_items_default
    static lv_style_t style_Reset_tile_extra_btnm_items_default;
    ui_init_style(&style_Reset_tile_extra_btnm_items_default);

    lv_style_set_text_color(&style_Reset_tile_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Reset_tile_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Reset_tile_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Reset_tile), &style_Reset_tile_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Reset_tile_extra_btnm_items_checked
    static lv_style_t style_Reset_tile_extra_btnm_items_checked;
    ui_init_style(&style_Reset_tile_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Reset_tile_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Reset_tile_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Reset_tile_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Reset_tile_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Reset_tile_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Reset_tile_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Reset_tile_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Reset_tile_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Reset_tile), &style_Reset_tile_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Reset_tile_tab_1 = lv_tabview_add_tab(ui->Reset_tile,"");
    lv_obj_t * Reset_tile_tab_1_label = lv_label_create(ui->Reset_tile_tab_1);
    lv_label_set_text(Reset_tile_tab_1_label, "");

    //Write codes Reset_btn_1
    ui->Reset_btn_1 = lv_btn_create(ui->Reset);
    ui->Reset_btn_1_label = lv_label_create(ui->Reset_btn_1);
    lv_label_set_text(ui->Reset_btn_1_label, "设备重启");
    lv_label_set_long_mode(ui->Reset_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Reset_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->Reset_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Reset_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Reset_btn_1, 70, 25);
    lv_obj_set_size(ui->Reset_btn_1, 152, 32);

    //Write style for Reset_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Reset_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Reset_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_label_1
    ui->Reset_label_1 = lv_label_create(ui->Reset);
    lv_label_set_text(ui->Reset_label_1, "是否重启设备?");
    lv_label_set_long_mode(ui->Reset_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Reset_label_1, 237, 255);
    lv_obj_set_size(ui->Reset_label_1, 229, 58);

    //Write style for Reset_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Reset_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_btn_2
    ui->Reset_btn_2 = lv_btn_create(ui->Reset);
    ui->Reset_btn_2_label = lv_label_create(ui->Reset_btn_2);
    lv_label_set_text(ui->Reset_btn_2_label, "Button");
    lv_label_set_long_mode(ui->Reset_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Reset_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Reset_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Reset_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Reset_btn_2, 78, 577);
    lv_obj_set_size(ui->Reset_btn_2, 100, 50);

    //Write style for Reset_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Reset_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Reset_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Reset_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_btn_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Reset_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_btn_3
    ui->Reset_btn_3 = lv_btn_create(ui->Reset);
    ui->Reset_btn_3_label = lv_label_create(ui->Reset_btn_3);
    lv_label_set_text(ui->Reset_btn_3_label, "Button");
    lv_label_set_long_mode(ui->Reset_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Reset_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Reset_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Reset_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->Reset_btn_3, 547, 560);
    lv_obj_set_size(ui->Reset_btn_3, 100, 50);

    //Write style for Reset_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Reset_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Reset_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Reset_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_btn_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Reset_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_btn_4
    ui->Reset_btn_4 = lv_btn_create(ui->Reset);
    ui->Reset_btn_4_label = lv_label_create(ui->Reset_btn_4);
    lv_label_set_text(ui->Reset_btn_4_label, "");
    lv_label_set_long_mode(ui->Reset_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Reset_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Reset_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Reset_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->Reset_btn_4, -6, -15);
    lv_obj_set_size(ui->Reset_btn_4, 241, 108);

    //Write style for Reset_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Reset_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Reset_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Reset_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Reset_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Reset_btn_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Reset_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Reset_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Reset_img_1
    ui->Reset_img_1 = lv_img_create(ui->Reset);
    lv_obj_add_flag(ui->Reset_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Reset_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Reset_img_1, 50,50);
    lv_img_set_angle(ui->Reset_img_1, 0);
    lv_obj_set_pos(ui->Reset_img_1, 43, 28);
    lv_obj_set_size(ui->Reset_img_1, 14, 24);

    //Write style for Reset_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Reset_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Reset_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Reset_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Reset_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Reset.


    //Update current screen layout.
    lv_obj_update_layout(ui->Reset);

    //Init events for screen.
    events_init_Reset(ui);
}
