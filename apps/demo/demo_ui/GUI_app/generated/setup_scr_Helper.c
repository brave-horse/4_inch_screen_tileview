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



void setup_scr_Helper(lv_ui *ui)
{
    //Write codes Helper
    ui->Helper = lv_obj_create(NULL);
    lv_obj_set_size(ui->Helper, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Helper, LV_SCROLLBAR_MODE_OFF);

    //Write style for Helper, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Helper, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Helper, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Helper, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Helper_tabview_1
    ui->Helper_tabview_1 = lv_tabview_create(ui->Helper, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->Helper_tabview_1, 0, 0);
    lv_obj_set_size(ui->Helper_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->Helper_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for Helper_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Helper_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Helper_tabview_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Helper_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Helper_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Helper_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Helper_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Helper_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Helper_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Helper_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Helper_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Helper_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Helper_tabview_1_extra_btnm_main_default
    static lv_style_t style_Helper_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Helper_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Helper_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Helper_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_Helper_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_Helper_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Helper_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Helper_tabview_1), &style_Helper_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_Helper_tabview_1_extra_btnm_items_default
    static lv_style_t style_Helper_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Helper_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Helper_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Helper_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_Helper_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Helper_tabview_1), &style_Helper_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_Helper_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Helper_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Helper_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Helper_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_Helper_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_Helper_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_Helper_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_Helper_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Helper_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_Helper_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_Helper_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Helper_tabview_1), &style_Helper_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->Helper_tabview_1_tab_1 = lv_tabview_add_tab(ui->Helper_tabview_1,"");
    lv_obj_t * Helper_tabview_1_tab_1_label = lv_label_create(ui->Helper_tabview_1_tab_1);
    lv_label_set_text(Helper_tabview_1_tab_1_label, "");

    //Write codes Helper_label_10
    ui->Helper_label_10 = lv_label_create(ui->Helper);
    lv_label_set_text(ui->Helper_label_10, "使用说明");
    lv_label_set_long_mode(ui->Helper_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Helper_label_10, 70, 25);
    lv_obj_set_size(ui->Helper_label_10, 149, 32);

    //Write style for Helper_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Helper_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Helper_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Helper_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Helper_label_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Helper_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Helper_img_1
    ui->Helper_img_1 = lv_img_create(ui->Helper);
    lv_obj_add_flag(ui->Helper_img_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->Helper_img_1, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\bhelp.png");
#else
    lv_img_set_src(ui->Helper_img_1, "S:/sdfile/EXT_RESERVED/uipackres/ui/bhelp.png");
#endif
    lv_img_set_pivot(ui->Helper_img_1, 50,50);
    lv_img_set_angle(ui->Helper_img_1, 0);
    lv_obj_set_pos(ui->Helper_img_1, 0, 85);
    lv_obj_set_size(ui->Helper_img_1, 720, 635);

    //Write style for Helper_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Helper_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Helper_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Helper_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Helper_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Helper_img_2
    ui->Helper_img_2 = lv_img_create(ui->Helper);
    lv_obj_add_flag(ui->Helper_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Helper_img_2, &_spageback_alpha_14x24);
    lv_img_set_pivot(ui->Helper_img_2, 50,50);
    lv_img_set_angle(ui->Helper_img_2, 0);
    lv_obj_set_pos(ui->Helper_img_2, 43, 28);
    lv_obj_set_size(ui->Helper_img_2, 14, 24);

    //Write style for Helper_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Helper_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Helper_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Helper_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Helper_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Helper_btn_1
    ui->Helper_btn_1 = lv_btn_create(ui->Helper);
    ui->Helper_btn_1_label = lv_label_create(ui->Helper_btn_1);
    lv_label_set_text(ui->Helper_btn_1_label, "");
    lv_label_set_long_mode(ui->Helper_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Helper_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Helper_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Helper_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Helper_btn_1, -5, -11);
    lv_obj_set_size(ui->Helper_btn_1, 263, 107);

    //Write style for Helper_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Helper_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Helper_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Helper_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Helper_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Helper_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Helper_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Helper_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Helper_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Helper.


    //Update current screen layout.
    lv_obj_update_layout(ui->Helper);

    //Init events for screen.
    events_init_Helper(ui);
}
