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



void setup_scr_huifuchuchangshezhi(lv_ui *ui)
{
    //Write codes huifuchuchangshezhi
    ui->huifuchuchangshezhi = lv_obj_create(NULL);
    lv_obj_set_size(ui->huifuchuchangshezhi, 720, 720);
    lv_obj_set_scrollbar_mode(ui->huifuchuchangshezhi, LV_SCROLLBAR_MODE_OFF);

    //Write style for huifuchuchangshezhi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->huifuchuchangshezhi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->huifuchuchangshezhi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_tile
    ui->huifuchuchangshezhi_tile = lv_tabview_create(ui->huifuchuchangshezhi, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->huifuchuchangshezhi_tile, 0, 0);
    lv_obj_set_size(ui->huifuchuchangshezhi_tile, 720, 720);
    lv_obj_set_scrollbar_mode(ui->huifuchuchangshezhi_tile, LV_SCROLLBAR_MODE_ON);

    //Write style for huifuchuchangshezhi_tile, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->huifuchuchangshezhi_tile, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->huifuchuchangshezhi_tile, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_tile, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_tile, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_tile, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->huifuchuchangshezhi_tile, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->huifuchuchangshezhi_tile, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_tile, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_huifuchuchangshezhi_tile_extra_btnm_main_default
    static lv_style_t style_huifuchuchangshezhi_tile_extra_btnm_main_default;
    ui_init_style(&style_huifuchuchangshezhi_tile_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_huifuchuchangshezhi_tile_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_huifuchuchangshezhi_tile_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_huifuchuchangshezhi_tile_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_huifuchuchangshezhi_tile_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_huifuchuchangshezhi_tile_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->huifuchuchangshezhi_tile), &style_huifuchuchangshezhi_tile_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_huifuchuchangshezhi_tile_extra_btnm_items_default
    static lv_style_t style_huifuchuchangshezhi_tile_extra_btnm_items_default;
    ui_init_style(&style_huifuchuchangshezhi_tile_extra_btnm_items_default);

    lv_style_set_text_color(&style_huifuchuchangshezhi_tile_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_huifuchuchangshezhi_tile_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_huifuchuchangshezhi_tile_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->huifuchuchangshezhi_tile), &style_huifuchuchangshezhi_tile_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_huifuchuchangshezhi_tile_extra_btnm_items_checked
    static lv_style_t style_huifuchuchangshezhi_tile_extra_btnm_items_checked;
    ui_init_style(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked);

    lv_style_set_text_color(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_huifuchuchangshezhi_tile_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->huifuchuchangshezhi_tile), &style_huifuchuchangshezhi_tile_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->huifuchuchangshezhi_tile_tab_1 = lv_tabview_add_tab(ui->huifuchuchangshezhi_tile,"");
    lv_obj_t * huifuchuchangshezhi_tile_tab_1_label = lv_label_create(ui->huifuchuchangshezhi_tile_tab_1);
    lv_label_set_text(huifuchuchangshezhi_tile_tab_1_label, "");

    //Write codes huifuchuchangshezhi_btn_1
    ui->huifuchuchangshezhi_btn_1 = lv_btn_create(ui->huifuchuchangshezhi);
    ui->huifuchuchangshezhi_btn_1_label = lv_label_create(ui->huifuchuchangshezhi_btn_1);
    lv_label_set_text(ui->huifuchuchangshezhi_btn_1_label, "恢复出厂");
    lv_label_set_long_mode(ui->huifuchuchangshezhi_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->huifuchuchangshezhi_btn_1_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->huifuchuchangshezhi_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->huifuchuchangshezhi_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->huifuchuchangshezhi_btn_1, 70, 25);
    lv_obj_set_size(ui->huifuchuchangshezhi_btn_1, 153, 32);

    //Write style for huifuchuchangshezhi_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->huifuchuchangshezhi_btn_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_label_1
    ui->huifuchuchangshezhi_label_1 = lv_label_create(ui->huifuchuchangshezhi);
    lv_label_set_text(ui->huifuchuchangshezhi_label_1, "清除所有数据,请谨慎确认!");
    lv_label_set_long_mode(ui->huifuchuchangshezhi_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->huifuchuchangshezhi_label_1, 159, 297);
    lv_obj_set_size(ui->huifuchuchangshezhi_label_1, 338, 58);

    //Write style for huifuchuchangshezhi_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->huifuchuchangshezhi_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_btn_2
    ui->huifuchuchangshezhi_btn_2 = lv_btn_create(ui->huifuchuchangshezhi);
    ui->huifuchuchangshezhi_btn_2_label = lv_label_create(ui->huifuchuchangshezhi_btn_2);
    lv_label_set_text(ui->huifuchuchangshezhi_btn_2_label, "Button");
    lv_label_set_long_mode(ui->huifuchuchangshezhi_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->huifuchuchangshezhi_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->huifuchuchangshezhi_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->huifuchuchangshezhi_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->huifuchuchangshezhi_btn_2, 78, 577);
    lv_obj_set_size(ui->huifuchuchangshezhi_btn_2, 100, 50);

    //Write style for huifuchuchangshezhi_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->huifuchuchangshezhi_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->huifuchuchangshezhi_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_btn_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->huifuchuchangshezhi_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_btn_3
    ui->huifuchuchangshezhi_btn_3 = lv_btn_create(ui->huifuchuchangshezhi);
    ui->huifuchuchangshezhi_btn_3_label = lv_label_create(ui->huifuchuchangshezhi_btn_3);
    lv_label_set_text(ui->huifuchuchangshezhi_btn_3_label, "Button");
    lv_label_set_long_mode(ui->huifuchuchangshezhi_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->huifuchuchangshezhi_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->huifuchuchangshezhi_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->huifuchuchangshezhi_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->huifuchuchangshezhi_btn_3, 547, 560);
    lv_obj_set_size(ui->huifuchuchangshezhi_btn_3, 100, 50);

    //Write style for huifuchuchangshezhi_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->huifuchuchangshezhi_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->huifuchuchangshezhi_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_btn_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->huifuchuchangshezhi_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_btn_4
    ui->huifuchuchangshezhi_btn_4 = lv_btn_create(ui->huifuchuchangshezhi);
    ui->huifuchuchangshezhi_btn_4_label = lv_label_create(ui->huifuchuchangshezhi_btn_4);
    lv_label_set_text(ui->huifuchuchangshezhi_btn_4_label, "");
    lv_label_set_long_mode(ui->huifuchuchangshezhi_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->huifuchuchangshezhi_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->huifuchuchangshezhi_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->huifuchuchangshezhi_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->huifuchuchangshezhi_btn_4, -7, -12);
    lv_obj_set_size(ui->huifuchuchangshezhi_btn_4, 261, 107);

    //Write style for huifuchuchangshezhi_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->huifuchuchangshezhi_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->huifuchuchangshezhi_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->huifuchuchangshezhi_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->huifuchuchangshezhi_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->huifuchuchangshezhi_btn_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->huifuchuchangshezhi_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->huifuchuchangshezhi_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes huifuchuchangshezhi_img_1
    ui->huifuchuchangshezhi_img_1 = lv_img_create(ui->huifuchuchangshezhi);
    lv_obj_add_flag(ui->huifuchuchangshezhi_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->huifuchuchangshezhi_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->huifuchuchangshezhi_img_1, 50,50);
    lv_img_set_angle(ui->huifuchuchangshezhi_img_1, 0);
    lv_obj_set_pos(ui->huifuchuchangshezhi_img_1, 43, 28);
    lv_obj_set_size(ui->huifuchuchangshezhi_img_1, 14, 24);

    //Write style for huifuchuchangshezhi_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->huifuchuchangshezhi_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->huifuchuchangshezhi_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->huifuchuchangshezhi_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->huifuchuchangshezhi_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of huifuchuchangshezhi.


    //Update current screen layout.
    lv_obj_update_layout(ui->huifuchuchangshezhi);

    //Init events for screen.
    events_init_huifuchuchangshezhi(ui);
}
