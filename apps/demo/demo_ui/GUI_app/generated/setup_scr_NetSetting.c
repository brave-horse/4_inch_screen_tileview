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



void setup_scr_NetSetting(lv_ui *ui)
{
    //Write codes NetSetting
    ui->NetSetting = lv_obj_create(NULL);
    lv_obj_set_size(ui->NetSetting, 720, 720);
    lv_obj_set_scrollbar_mode(ui->NetSetting, LV_SCROLLBAR_MODE_OFF);

    //Write style for NetSetting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NetSetting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NetSetting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_tabview_1
    ui->NetSetting_tabview_1 = lv_tabview_create(ui->NetSetting, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->NetSetting_tabview_1, 0, 0);
    lv_obj_set_size(ui->NetSetting_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->NetSetting_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for NetSetting_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NetSetting_tabview_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NetSetting_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NetSetting_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NetSetting_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NetSetting_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_NetSetting_tabview_1_extra_btnm_main_default
    static lv_style_t style_NetSetting_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_NetSetting_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_NetSetting_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_NetSetting_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_NetSetting_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_NetSetting_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_NetSetting_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->NetSetting_tabview_1), &style_NetSetting_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_NetSetting_tabview_1_extra_btnm_items_default
    static lv_style_t style_NetSetting_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_NetSetting_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_NetSetting_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_NetSetting_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_NetSetting_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->NetSetting_tabview_1), &style_NetSetting_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_NetSetting_tabview_1_extra_btnm_items_checked
    static lv_style_t style_NetSetting_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_NetSetting_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_NetSetting_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_NetSetting_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_NetSetting_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_NetSetting_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_NetSetting_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_NetSetting_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_NetSetting_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_NetSetting_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->NetSetting_tabview_1), &style_NetSetting_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->NetSetting_tabview_1_tab_1 = lv_tabview_add_tab(ui->NetSetting_tabview_1,"");
    lv_obj_t * NetSetting_tabview_1_tab_1_label = lv_label_create(ui->NetSetting_tabview_1_tab_1);
    lv_label_set_text(NetSetting_tabview_1_tab_1_label, "");

    //Write codes NetSetting_NetSet
    ui->NetSetting_NetSet = lv_btn_create(ui->NetSetting);
    ui->NetSetting_NetSet_label = lv_label_create(ui->NetSetting_NetSet);
    lv_label_set_text(ui->NetSetting_NetSet_label, "网络设置");
    lv_label_set_long_mode(ui->NetSetting_NetSet_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->NetSetting_NetSet_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->NetSetting_NetSet, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NetSetting_NetSet_label, LV_PCT(100));
    lv_obj_set_pos(ui->NetSetting_NetSet, 70, 25);
    lv_obj_set_size(ui->NetSetting_NetSet, 156, 32);

    //Write style for NetSetting_NetSet, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting_NetSet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NetSetting_NetSet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_NetSet, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_NetSet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_NetSet, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_NetSet, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_NetSet, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_NetSet, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_img_1
    ui->NetSetting_img_1 = lv_img_create(ui->NetSetting);
    lv_obj_add_flag(ui->NetSetting_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NetSetting_img_1, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->NetSetting_img_1, 50,50);
    lv_img_set_angle(ui->NetSetting_img_1, 0);
    lv_obj_set_pos(ui->NetSetting_img_1, 43, 28);
    lv_obj_set_size(ui->NetSetting_img_1, 14, 24);

    //Write style for NetSetting_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NetSetting_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NetSetting_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NetSetting_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_btn_1
    ui->NetSetting_btn_1 = lv_btn_create(ui->NetSetting);
    ui->NetSetting_btn_1_label = lv_label_create(ui->NetSetting_btn_1);
    lv_label_set_text(ui->NetSetting_btn_1_label, "");
    lv_label_set_long_mode(ui->NetSetting_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->NetSetting_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->NetSetting_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NetSetting_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->NetSetting_btn_1, -5, -11);
    lv_obj_set_size(ui->NetSetting_btn_1, 261, 107);

    //Write style for NetSetting_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NetSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_img_5
    ui->NetSetting_img_5 = lv_img_create(ui->NetSetting);
    lv_obj_add_flag(ui->NetSetting_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NetSetting_img_5, &_Sbind_alpha_71x71);
    lv_img_set_pivot(ui->NetSetting_img_5, 50,50);
    lv_img_set_angle(ui->NetSetting_img_5, 0);
    lv_obj_set_pos(ui->NetSetting_img_5, 307, 296);
    lv_obj_set_size(ui->NetSetting_img_5, 71, 71);

    //Write style for NetSetting_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NetSetting_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NetSetting_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NetSetting_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_btn_5
    ui->NetSetting_btn_5 = lv_btn_create(ui->NetSetting);
    ui->NetSetting_btn_5_label = lv_label_create(ui->NetSetting_btn_5);
    lv_label_set_text(ui->NetSetting_btn_5_label, "解除设备");
    lv_label_set_long_mode(ui->NetSetting_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->NetSetting_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->NetSetting_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NetSetting_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->NetSetting_btn_5, 207, 578);
    lv_obj_set_size(ui->NetSetting_btn_5, 306, 50);

    //Write style for NetSetting_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NetSetting_btn_5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NetSetting_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NetSetting_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_btn_5, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_btn_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_label_4
    ui->NetSetting_label_4 = lv_label_create(ui->NetSetting);
    lv_label_set_text(ui->NetSetting_label_4, "设备已经绑定米家App");
    lv_label_set_long_mode(ui->NetSetting_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NetSetting_label_4, 193, 152);
    lv_obj_set_size(ui->NetSetting_label_4, 334, 32);

    //Write style for NetSetting_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_label_4, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_img_4
    ui->NetSetting_img_4 = lv_img_create(ui->NetSetting);
    lv_obj_add_flag(ui->NetSetting_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NetSetting_img_4, &_SQRCode_alpha_300x300);
    lv_img_set_pivot(ui->NetSetting_img_4, 50,50);
    lv_img_set_angle(ui->NetSetting_img_4, 0);
    lv_obj_set_pos(ui->NetSetting_img_4, 210, 210);
    lv_obj_set_size(ui->NetSetting_img_4, 300, 300);

    //Write style for NetSetting_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NetSetting_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NetSetting_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NetSetting_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_img_3
    ui->NetSetting_img_3 = lv_img_create(ui->NetSetting);
    lv_obj_add_flag(ui->NetSetting_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NetSetting_img_3, &_Sstartbind_alpha_136x145);
    lv_img_set_pivot(ui->NetSetting_img_3, 50,50);
    lv_img_set_angle(ui->NetSetting_img_3, 0);
    lv_obj_set_pos(ui->NetSetting_img_3, 292, 287);
    lv_obj_set_size(ui->NetSetting_img_3, 136, 145);

    //Write style for NetSetting_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NetSetting_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NetSetting_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NetSetting_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_btn_3
    ui->NetSetting_btn_3 = lv_btn_create(ui->NetSetting);
    ui->NetSetting_btn_3_label = lv_label_create(ui->NetSetting_btn_3);
    lv_label_set_text(ui->NetSetting_btn_3_label, "开始绑定");
    lv_label_set_long_mode(ui->NetSetting_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->NetSetting_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->NetSetting_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NetSetting_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->NetSetting_btn_3, 207, 578);
    lv_obj_set_size(ui->NetSetting_btn_3, 306, 50);

    //Write style for NetSetting_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NetSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NetSetting_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NetSetting_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NetSetting_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_btn_3, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_btn_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NetSetting_label_3
    ui->NetSetting_label_3 = lv_label_create(ui->NetSetting);
    lv_label_set_text(ui->NetSetting_label_3, "设备未绑定米家");
    lv_label_set_long_mode(ui->NetSetting_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NetSetting_label_3, 193, 152);
    lv_obj_set_size(ui->NetSetting_label_3, 334, 32);

    //Write style for NetSetting_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NetSetting_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NetSetting_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NetSetting_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NetSetting_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NetSetting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of NetSetting.


    //Update current screen layout.
    lv_obj_update_layout(ui->NetSetting);

    //Init events for screen.
    events_init_NetSetting(ui);
}
