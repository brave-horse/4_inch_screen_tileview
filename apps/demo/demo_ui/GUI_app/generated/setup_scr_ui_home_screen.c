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



void setup_scr_ui_home_screen(lv_ui *ui)
{
    //Write codes ui_home_screen
    ui->ui_home_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->ui_home_screen, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1
    ui->ui_home_screen_cont_1 = lv_obj_create(ui->ui_home_screen);
    lv_obj_set_pos(ui->ui_home_screen_cont_1, 0, -430);
    lv_obj_set_size(ui->ui_home_screen_cont_1, 720, 320);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_2
    ui->ui_home_screen_cont_2 = lv_obj_create(ui->ui_home_screen_cont_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_2, 47, 19);
    lv_obj_set_size(ui->ui_home_screen_cont_2, 640, 151);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_2, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_2, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_MainSetBtn
    ui->ui_home_screen_MainSetBtn = lv_btn_create(ui->ui_home_screen_cont_2);
    ui->ui_home_screen_MainSetBtn_label = lv_label_create(ui->ui_home_screen_MainSetBtn);
    lv_label_set_text(ui->ui_home_screen_MainSetBtn_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_MainSetBtn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_MainSetBtn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_MainSetBtn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_MainSetBtn_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_MainSetBtn, 28, 25);
    lv_obj_set_size(ui->ui_home_screen_MainSetBtn, 100, 100);

    //Write style for ui_home_screen_MainSetBtn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_MainSetBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_MainSetBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_MainSetBtn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_MainSetBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_MainSetBtn, 80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_MainSetBtn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_MainSetBtn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_MainSetBtn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_MainSetBtn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_MainSetBtn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_MainSetImg
    ui->ui_home_screen_MainSetImg = lv_img_create(ui->ui_home_screen_cont_2);
    lv_obj_add_flag(ui->ui_home_screen_MainSetImg, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_MainSetImg, &_sSetting_alpha_46x46);
    lv_img_set_pivot(ui->ui_home_screen_MainSetImg, 50,50);
    lv_img_set_angle(ui->ui_home_screen_MainSetImg, 0);
    lv_obj_set_pos(ui->ui_home_screen_MainSetImg, 53, 52);
    lv_obj_set_size(ui->ui_home_screen_MainSetImg, 46, 46);

    //Write style for ui_home_screen_MainSetImg, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_MainSetImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_MainSetImg, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_MainSetImg, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_MainSetImg, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_4
    ui->ui_home_screen_btn_4 = lv_btn_create(ui->ui_home_screen_cont_2);
    ui->ui_home_screen_btn_4_label = lv_label_create(ui->ui_home_screen_btn_4);
    lv_label_set_text(ui->ui_home_screen_btn_4_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_4, 191, 23);
    lv_obj_set_size(ui->ui_home_screen_btn_4, 100, 100);

    //Write style for ui_home_screen_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_4, 80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_5
    ui->ui_home_screen_btn_5 = lv_btn_create(ui->ui_home_screen_cont_2);
    ui->ui_home_screen_btn_5_label = lv_label_create(ui->ui_home_screen_btn_5);
    lv_label_set_text(ui->ui_home_screen_btn_5_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_5, 350, 25);
    lv_obj_set_size(ui->ui_home_screen_btn_5, 100, 100);

    //Write style for ui_home_screen_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_5, 80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_6
    ui->ui_home_screen_btn_6 = lv_btn_create(ui->ui_home_screen_cont_2);
    ui->ui_home_screen_btn_6_label = lv_label_create(ui->ui_home_screen_btn_6);
    lv_label_set_text(ui->ui_home_screen_btn_6_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_6_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_6, 509, 25);
    lv_obj_set_size(ui->ui_home_screen_btn_6, 100, 100);

    //Write style for ui_home_screen_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_6, 80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_3
    ui->ui_home_screen_img_3 = lv_img_create(ui->ui_home_screen_cont_2);
    lv_obj_add_flag(ui->ui_home_screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_3, &_sHome_alpha_46x46);
    lv_img_set_pivot(ui->ui_home_screen_img_3, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_3, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_3, 536, 46);
    lv_obj_set_size(ui->ui_home_screen_img_3, 46, 46);

    //Write style for ui_home_screen_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_4
    ui->ui_home_screen_img_4 = lv_img_create(ui->ui_home_screen_cont_2);
    lv_obj_add_flag(ui->ui_home_screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_4, &_sManual_alpha_46x46);
    lv_img_set_pivot(ui->ui_home_screen_img_4, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_4, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_4, 377, 51);
    lv_obj_set_size(ui->ui_home_screen_img_4, 46, 46);

    //Write style for ui_home_screen_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_6
    ui->ui_home_screen_img_6 = lv_img_create(ui->ui_home_screen_cont_2);
    lv_obj_add_flag(ui->ui_home_screen_img_6, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_6, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sSleep_on.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_6, "S:/sdfile/EXT_RESERVED/uipackres/ui/sSleep_on.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_6, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_6, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_6, 216, 50);
    lv_obj_set_size(ui->ui_home_screen_img_6, 46, 46);

    //Write style for ui_home_screen_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_2
    ui->ui_home_screen_img_2 = lv_img_create(ui->ui_home_screen_cont_2);
    lv_obj_add_flag(ui->ui_home_screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_2, &_sSleep_off_alpha_46x46);
    lv_img_set_pivot(ui->ui_home_screen_img_2, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_2, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_2, 216, 50);
    lv_obj_set_size(ui->ui_home_screen_img_2, 46, 46);

    //Write style for ui_home_screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_slider_1
    ui->ui_home_screen_slider_1 = lv_slider_create(ui->ui_home_screen_cont_1);
    lv_slider_set_range(ui->ui_home_screen_slider_1, 0, 100);
    lv_slider_set_mode(ui->ui_home_screen_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->ui_home_screen_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->ui_home_screen_slider_1, 47, 199);
    lv_obj_set_size(ui->ui_home_screen_slider_1, 640, 62);

    //Write style for ui_home_screen_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_slider_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_slider_1, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_slider_1, 40, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->ui_home_screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_slider_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_slider_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_slider_1, 36, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_5
    ui->ui_home_screen_img_5 = lv_img_create(ui->ui_home_screen_cont_1);
    lv_obj_add_flag(ui->ui_home_screen_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_5, &_sSun_alpha_30x34);
    lv_img_set_pivot(ui->ui_home_screen_img_5, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_5, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_5, 71, 212);
    lv_obj_set_size(ui->ui_home_screen_img_5, 30, 34);

    //Write style for ui_home_screen_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_tileview_1
    ui->ui_home_screen_tileview_1 = lv_tileview_create(ui->ui_home_screen);
    ui->ui_home_screen_tileview_1_tile_0 = lv_tileview_add_tile(ui->ui_home_screen_tileview_1, 0, 0, LV_DIR_RIGHT);
    ui->ui_home_screen_tileview_1_tile_1 = lv_tileview_add_tile(ui->ui_home_screen_tileview_1, 1, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->ui_home_screen_tileview_1_tile_2 = lv_tileview_add_tile(ui->ui_home_screen_tileview_1, 2, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->ui_home_screen_tileview_1_tile_3 = lv_tileview_add_tile(ui->ui_home_screen_tileview_1, 3, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    ui->ui_home_screen_tileview_1_tile_4 = lv_tileview_add_tile(ui->ui_home_screen_tileview_1, 4, 0, LV_DIR_LEFT);
    lv_obj_set_pos(ui->ui_home_screen_tileview_1, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_tileview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_tileview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tileview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tileview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tileview_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tileview_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes ui_home_screen_img_1
    ui->ui_home_screen_img_1 = lv_img_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_obj_add_flag(ui->ui_home_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_1, &_color_alpha_720x720);
    lv_img_set_pivot(ui->ui_home_screen_img_1, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_1, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_1, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_1, 720, 720);

    //Write style for ui_home_screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_1
    ui->ui_home_screen_label_1 = lv_label_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_label_set_text(ui->ui_home_screen_label_1, "2026/06/01");
    lv_label_set_long_mode(ui->ui_home_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_1, 67, 114);
    lv_obj_set_size(ui->ui_home_screen_label_1, 172, 43);

    //Write style for ui_home_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_2
    ui->ui_home_screen_label_2 = lv_label_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_label_set_text(ui->ui_home_screen_label_2, "星期一");
    lv_label_set_long_mode(ui->ui_home_screen_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_2, 61, 180);
    lv_obj_set_size(ui->ui_home_screen_label_2, 118, 40);

    //Write style for ui_home_screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_1
    ui->ui_home_screen_btn_1 = lv_btn_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_obj_add_flag(ui->ui_home_screen_btn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->ui_home_screen_btn_1_label = lv_label_create(ui->ui_home_screen_btn_1);
    lv_label_set_text(ui->ui_home_screen_btn_1_label, "按键1");
    lv_label_set_long_mode(ui->ui_home_screen_btn_1_label, LV_LABEL_LONG_CLIP);
    lv_obj_align(ui->ui_home_screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_1, 484, 0);
    lv_obj_set_size(ui->ui_home_screen_btn_1, 236, 236);

    //Write style for ui_home_screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_1, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_2
    ui->ui_home_screen_btn_2 = lv_btn_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_obj_add_flag(ui->ui_home_screen_btn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->ui_home_screen_btn_2_label = lv_label_create(ui->ui_home_screen_btn_2);
    lv_label_set_text(ui->ui_home_screen_btn_2_label, "按键3");
    lv_label_set_long_mode(ui->ui_home_screen_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_2, 484, 483);
    lv_obj_set_size(ui->ui_home_screen_btn_2, 236, 236);

    //Write style for ui_home_screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_2, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_btn_7
    ui->ui_home_screen_btn_7 = lv_btn_create(ui->ui_home_screen_tileview_1_tile_0);
    lv_obj_add_flag(ui->ui_home_screen_btn_7, LV_OBJ_FLAG_CHECKABLE);
    ui->ui_home_screen_btn_7_label = lv_label_create(ui->ui_home_screen_btn_7);
    lv_label_set_text(ui->ui_home_screen_btn_7_label, "按键2");
    lv_label_set_long_mode(ui->ui_home_screen_btn_7_label, LV_LABEL_LONG_CLIP);
    lv_obj_align(ui->ui_home_screen_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_home_screen_btn_7_label, LV_PCT(100));
    lv_obj_set_pos(ui->ui_home_screen_btn_7, 484, 242);
    lv_obj_set_size(ui->ui_home_screen_btn_7, 236, 236);

    //Write style for ui_home_screen_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_btn_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_btn_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes ui_home_screen_tabview_3
    ui->ui_home_screen_tabview_3 = lv_tabview_create(ui->ui_home_screen_tileview_1_tile_1, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->ui_home_screen_tabview_3, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_tabview_3, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_tabview_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_tabview_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tabview_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tabview_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tabview_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_tabview_3, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_tabview_3, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_tabview_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_tabview_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_tabview_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_tabview_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tabview_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_tabview_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_3_extra_btnm_main_default
    static lv_style_t style_ui_home_screen_tabview_3_extra_btnm_main_default;
    ui_init_style(&style_ui_home_screen_tabview_3_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_ui_home_screen_tabview_3_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_3_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_3_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_ui_home_screen_tabview_3_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_3_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_3), &style_ui_home_screen_tabview_3_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_3_extra_btnm_items_default
    static lv_style_t style_ui_home_screen_tabview_3_extra_btnm_items_default;
    ui_init_style(&style_ui_home_screen_tabview_3_extra_btnm_items_default);

    lv_style_set_text_color(&style_ui_home_screen_tabview_3_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_ui_home_screen_tabview_3_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_3_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_3), &style_ui_home_screen_tabview_3_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_ui_home_screen_tabview_3_extra_btnm_items_checked
    static lv_style_t style_ui_home_screen_tabview_3_extra_btnm_items_checked;
    ui_init_style(&style_ui_home_screen_tabview_3_extra_btnm_items_checked);

    lv_style_set_text_color(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_text_font(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_3_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_3), &style_ui_home_screen_tabview_3_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->ui_home_screen_tabview_3_tab_1 = lv_tabview_add_tab(ui->ui_home_screen_tabview_3,"");
    lv_obj_t * ui_home_screen_tabview_3_tab_1_label = lv_label_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_label_set_text(ui_home_screen_tabview_3_tab_1_label, "");

    //Write codes ui_home_screen_cont_27
    ui->ui_home_screen_cont_27 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_27, 1, 0);
    lv_obj_set_size(ui->ui_home_screen_cont_27, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_27, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_27, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_27, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_27, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_9
    ui->ui_home_screen_imgbtn_9 = lv_imgbtn_create(ui->ui_home_screen_cont_27);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_9, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_9, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_9, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_9, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_9, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_9_label = lv_label_create(ui->ui_home_screen_imgbtn_9);
    lv_label_set_text(ui->ui_home_screen_imgbtn_9_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_9_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_9_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_9, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_9, 248, 29);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_9, 48, 48);

    //Write style for ui_home_screen_imgbtn_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_9, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_9, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_9, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_9, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_9, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_9, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_9, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_9, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_9, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_9, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_img_61
    ui->ui_home_screen_img_61 = lv_img_create(ui->ui_home_screen_cont_27);
    lv_obj_add_flag(ui->ui_home_screen_img_61, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_61, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sdev_on.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_61, "S:/sdfile/EXT_RESERVED/uipackres/ui/sdev_on.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_61, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_61, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_61, 34, 20);
    lv_obj_set_size(ui->ui_home_screen_img_61, 50, 57);

    //Write style for ui_home_screen_img_61, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_61, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_61, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_61, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_61, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_60
    ui->ui_home_screen_img_60 = lv_img_create(ui->ui_home_screen_cont_27);
    lv_obj_add_flag(ui->ui_home_screen_img_60, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_60, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sdev_off.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_60, "S:/sdfile/EXT_RESERVED/uipackres/ui/sdev_off.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_60, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_60, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_60, 34, 20);
    lv_obj_set_size(ui->ui_home_screen_img_60, 50, 57);

    //Write style for ui_home_screen_img_60, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_60, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_60, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_60, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_60, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_36
    ui->ui_home_screen_label_36 = lv_label_create(ui->ui_home_screen_cont_27);
    lv_label_set_text(ui->ui_home_screen_label_36, "色温灯");
    lv_label_set_long_mode(ui->ui_home_screen_label_36, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_36, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_36, 100, 35);

    //Write style for ui_home_screen_label_36, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_36, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_36, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_36, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_36, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_26
    ui->ui_home_screen_cont_26 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_26, 343, 0);
    lv_obj_set_size(ui->ui_home_screen_cont_26, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_26, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_26, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_26, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_26, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_59
    ui->ui_home_screen_img_59 = lv_img_create(ui->ui_home_screen_cont_26);
    lv_obj_add_flag(ui->ui_home_screen_img_59, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_59, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLSOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_59, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLSOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_59, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_59, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_59, 20, 42);
    lv_obj_set_size(ui->ui_home_screen_img_59, 65, 43);

    //Write style for ui_home_screen_img_59, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_59, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_59, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_59, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_59, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_58
    ui->ui_home_screen_img_58 = lv_img_create(ui->ui_home_screen_cont_26);
    lv_obj_add_flag(ui->ui_home_screen_img_58, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_58, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLSOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_58, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLSOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_58, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_58, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_58, 20, 42);
    lv_obj_set_size(ui->ui_home_screen_img_58, 65, 43);

    //Write style for ui_home_screen_img_58, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_58, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_58, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_58, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_58, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_8
    ui->ui_home_screen_imgbtn_8 = lv_imgbtn_create(ui->ui_home_screen_cont_26);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_8, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_8, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_8, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_8, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_8, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_8_label = lv_label_create(ui->ui_home_screen_imgbtn_8);
    lv_label_set_text(ui->ui_home_screen_imgbtn_8_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_8, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_8, 48, 48);

    //Write style for ui_home_screen_imgbtn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_8, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_8, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_8, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_8, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_8, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_8, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_8, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_8, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_8, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_8, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_35
    ui->ui_home_screen_label_35 = lv_label_create(ui->ui_home_screen_cont_26);
    lv_label_set_text(ui->ui_home_screen_label_35, "灯  带");
    lv_label_set_long_mode(ui->ui_home_screen_label_35, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_35, 19, 135);
    lv_obj_set_size(ui->ui_home_screen_label_35, 92, 32);

    //Write style for ui_home_screen_label_35, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_35, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_35, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_35, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_35, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_25
    ui->ui_home_screen_cont_25 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_25, 0, 211);
    lv_obj_set_size(ui->ui_home_screen_cont_25, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_25, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_25, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_25, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_25, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_57
    ui->ui_home_screen_img_57 = lv_img_create(ui->ui_home_screen_cont_25);
    lv_obj_add_flag(ui->ui_home_screen_img_57, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_57, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sMLOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_57, "S:/sdfile/EXT_RESERVED/uipackres/ui/sMLOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_57, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_57, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_57, 30, 40);
    lv_obj_set_size(ui->ui_home_screen_img_57, 70, 4);

    //Write style for ui_home_screen_img_57, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_57, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_57, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_57, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_57, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_56
    ui->ui_home_screen_img_56 = lv_img_create(ui->ui_home_screen_cont_25);
    lv_obj_add_flag(ui->ui_home_screen_img_56, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_56, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sMLOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_56, "S:/sdfile/EXT_RESERVED/uipackres/ui/sMLOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_56, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_56, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_56, 30, 40);
    lv_obj_set_size(ui->ui_home_screen_img_56, 70, 4);

    //Write style for ui_home_screen_img_56, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_56, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_56, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_56, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_56, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_7
    ui->ui_home_screen_imgbtn_7 = lv_imgbtn_create(ui->ui_home_screen_cont_25);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_7, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_7, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_7, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_7, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_7, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_7_label = lv_label_create(ui->ui_home_screen_imgbtn_7);
    lv_label_set_text(ui->ui_home_screen_imgbtn_7_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_7, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_7, 48, 48);

    //Write style for ui_home_screen_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_7, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_7, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_7, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_34
    ui->ui_home_screen_label_34 = lv_label_create(ui->ui_home_screen_cont_25);
    lv_label_set_text(ui->ui_home_screen_label_34, "磁吸灯");
    lv_label_set_long_mode(ui->ui_home_screen_label_34, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_34, 18, 135);
    lv_obj_set_size(ui->ui_home_screen_label_34, 100, 35);

    //Write style for ui_home_screen_label_34, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_34, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_34, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_34, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_34, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_24
    ui->ui_home_screen_cont_24 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_24, 343, 209);
    lv_obj_set_size(ui->ui_home_screen_cont_24, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_24, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_24, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_24, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_24, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_55
    ui->ui_home_screen_img_55 = lv_img_create(ui->ui_home_screen_cont_24);
    lv_obj_add_flag(ui->ui_home_screen_img_55, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_55, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sRGBLOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_55, "S:/sdfile/EXT_RESERVED/uipackres/ui/sRGBLOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_55, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_55, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_55, 27, 27);
    lv_obj_set_size(ui->ui_home_screen_img_55, 60, 58);

    //Write style for ui_home_screen_img_55, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_55, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_55, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_55, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_54
    ui->ui_home_screen_img_54 = lv_img_create(ui->ui_home_screen_cont_24);
    lv_obj_add_flag(ui->ui_home_screen_img_54, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_54, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sRGBLOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_54, "S:/sdfile/EXT_RESERVED/uipackres/ui/sRGBLOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_54, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_54, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_54, 27, 27);
    lv_obj_set_size(ui->ui_home_screen_img_54, 60, 58);

    //Write style for ui_home_screen_img_54, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_54, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_54, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_54, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_54, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_6
    ui->ui_home_screen_imgbtn_6 = lv_imgbtn_create(ui->ui_home_screen_cont_24);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_6, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_6, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_6_label = lv_label_create(ui->ui_home_screen_imgbtn_6);
    lv_label_set_text(ui->ui_home_screen_imgbtn_6_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_6, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_6, 48, 48);

    //Write style for ui_home_screen_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_6, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_6, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_6, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_33
    ui->ui_home_screen_label_33 = lv_label_create(ui->ui_home_screen_cont_24);
    lv_label_set_text(ui->ui_home_screen_label_33, "彩色灯");
    lv_label_set_long_mode(ui->ui_home_screen_label_33, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_33, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_33, 90, 35);

    //Write style for ui_home_screen_label_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_33, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_33, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_33, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_23
    ui->ui_home_screen_cont_23 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_23, 0, 421);
    lv_obj_set_size(ui->ui_home_screen_cont_23, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_23, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_23, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_23, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_23, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_53
    ui->ui_home_screen_img_53 = lv_img_create(ui->ui_home_screen_cont_23);
    lv_obj_add_flag(ui->ui_home_screen_img_53, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_53, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sFCOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_53, "S:/sdfile/EXT_RESERVED/uipackres/ui/sFCOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_53, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_53, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_53, 26, 38);
    lv_obj_set_size(ui->ui_home_screen_img_53, 49, 43);

    //Write style for ui_home_screen_img_53, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_53, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_53, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_53, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_53, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_52
    ui->ui_home_screen_img_52 = lv_img_create(ui->ui_home_screen_cont_23);
    lv_obj_add_flag(ui->ui_home_screen_img_52, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_52, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sFCOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_52, "S:/sdfile/EXT_RESERVED/uipackres/ui/sFCOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_52, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_52, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_52, 26, 38);
    lv_obj_set_size(ui->ui_home_screen_img_52, 49, 43);

    //Write style for ui_home_screen_img_52, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_52, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_52, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_52, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_52, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_32
    ui->ui_home_screen_label_32 = lv_label_create(ui->ui_home_screen_cont_23);
    lv_label_set_text(ui->ui_home_screen_label_32, "布  帘");
    lv_label_set_long_mode(ui->ui_home_screen_label_32, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_32, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_32, 82, 35);

    //Write style for ui_home_screen_label_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_32, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_32, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_32, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_51
    ui->ui_home_screen_img_51 = lv_img_create(ui->ui_home_screen_cont_23);
    lv_obj_add_flag(ui->ui_home_screen_img_51, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_51, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sClose.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_51, "S:/sdfile/EXT_RESERVED/uipackres/ui/sClose.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_51, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_51, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_51, 249, 29);
    lv_obj_set_size(ui->ui_home_screen_img_51, 60, 60);

    //Write style for ui_home_screen_img_51, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_51, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_51, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_51, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_51, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_50
    ui->ui_home_screen_img_50 = lv_img_create(ui->ui_home_screen_cont_23);
    lv_obj_add_flag(ui->ui_home_screen_img_50, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_50, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sOpen.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_50, "S:/sdfile/EXT_RESERVED/uipackres/ui/sOpen.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_50, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_50, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_50, 159, 29);
    lv_obj_set_size(ui->ui_home_screen_img_50, 60, 60);

    //Write style for ui_home_screen_img_50, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_50, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_50, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_50, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_50, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_22
    ui->ui_home_screen_cont_22 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_22, 345, 420);
    lv_obj_set_size(ui->ui_home_screen_cont_22, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_22, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_22, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_22, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_22, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_49
    ui->ui_home_screen_img_49 = lv_img_create(ui->ui_home_screen_cont_22);
    lv_obj_add_flag(ui->ui_home_screen_img_49, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_49, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sFCOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_49, "S:/sdfile/EXT_RESERVED/uipackres/ui/sFCOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_49, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_49, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_49, 23, 39);
    lv_obj_set_size(ui->ui_home_screen_img_49, 49, 43);

    //Write style for ui_home_screen_img_49, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_49, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_49, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_48
    ui->ui_home_screen_img_48 = lv_img_create(ui->ui_home_screen_cont_22);
    lv_obj_add_flag(ui->ui_home_screen_img_48, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_48, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sFCOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_48, "S:/sdfile/EXT_RESERVED/uipackres/ui/sFCOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_48, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_48, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_48, 23, 38);
    lv_obj_set_size(ui->ui_home_screen_img_48, 49, 43);

    //Write style for ui_home_screen_img_48, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_48, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_48, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_48, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_48, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_31
    ui->ui_home_screen_label_31 = lv_label_create(ui->ui_home_screen_cont_22);
    lv_label_set_text(ui->ui_home_screen_label_31, "纱  帘");
    lv_label_set_long_mode(ui->ui_home_screen_label_31, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_31, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_31, 82, 35);

    //Write style for ui_home_screen_label_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_31, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_31, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_31, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_47
    ui->ui_home_screen_img_47 = lv_img_create(ui->ui_home_screen_cont_22);
    lv_obj_add_flag(ui->ui_home_screen_img_47, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_47, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sOpen.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_47, "S:/sdfile/EXT_RESERVED/uipackres/ui/sOpen.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_47, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_47, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_47, 160, 29);
    lv_obj_set_size(ui->ui_home_screen_img_47, 60, 60);

    //Write style for ui_home_screen_img_47, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_47, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_47, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_47, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_47, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_46
    ui->ui_home_screen_img_46 = lv_img_create(ui->ui_home_screen_cont_22);
    lv_obj_add_flag(ui->ui_home_screen_img_46, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_46, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sClose.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_46, "S:/sdfile/EXT_RESERVED/uipackres/ui/sClose.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_46, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_46, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_46, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_img_46, 60, 60);

    //Write style for ui_home_screen_img_46, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_46, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_46, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_21
    ui->ui_home_screen_cont_21 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_21, 0, 630);
    lv_obj_set_size(ui->ui_home_screen_cont_21, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_21, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_21, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_21, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_21, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_45
    ui->ui_home_screen_img_45 = lv_img_create(ui->ui_home_screen_cont_21);
    lv_obj_add_flag(ui->ui_home_screen_img_45, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_45, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sRBOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_45, "S:/sdfile/EXT_RESERVED/uipackres/ui/sRBOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_45, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_45, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_45, 26, 35);
    lv_obj_set_size(ui->ui_home_screen_img_45, 65, 20);

    //Write style for ui_home_screen_img_45, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_45, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_45, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_44
    ui->ui_home_screen_img_44 = lv_img_create(ui->ui_home_screen_cont_21);
    lv_obj_add_flag(ui->ui_home_screen_img_44, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_44, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sRBOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_44, "S:/sdfile/EXT_RESERVED/uipackres/ui/sRBOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_44, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_44, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_44, 26, 36);
    lv_obj_set_size(ui->ui_home_screen_img_44, 65, 43);

    //Write style for ui_home_screen_img_44, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_44, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_44, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_30
    ui->ui_home_screen_label_30 = lv_label_create(ui->ui_home_screen_cont_21);
    lv_label_set_text(ui->ui_home_screen_label_30, "卷  帘");
    lv_label_set_long_mode(ui->ui_home_screen_label_30, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_30, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_30, 82, 35);

    //Write style for ui_home_screen_label_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_30, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_30, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_30, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_43
    ui->ui_home_screen_img_43 = lv_img_create(ui->ui_home_screen_cont_21);
    lv_obj_add_flag(ui->ui_home_screen_img_43, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_43, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDown.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_43, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDown.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_43, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_43, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_43, 250, 110);
    lv_obj_set_size(ui->ui_home_screen_img_43, 60, 60);

    //Write style for ui_home_screen_img_43, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_43, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_43, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_42
    ui->ui_home_screen_img_42 = lv_img_create(ui->ui_home_screen_cont_21);
    lv_obj_add_flag(ui->ui_home_screen_img_42, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_42, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sUp.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_42, "S:/sdfile/EXT_RESERVED/uipackres/ui/sUp.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_42, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_42, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_42, 250, 21);
    lv_obj_set_size(ui->ui_home_screen_img_42, 60, 60);

    //Write style for ui_home_screen_img_42, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_42, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_42, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_20
    ui->ui_home_screen_cont_20 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_20, 345, 630);
    lv_obj_set_size(ui->ui_home_screen_cont_20, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_20, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_20, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_20, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_20, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_41
    ui->ui_home_screen_img_41 = lv_img_create(ui->ui_home_screen_cont_20);
    lv_obj_add_flag(ui->ui_home_screen_img_41, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_41, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDreamOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_41, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDreamOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_41, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_41, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_41, 28, 34);
    lv_obj_set_size(ui->ui_home_screen_img_41, 54, 41);

    //Write style for ui_home_screen_img_41, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_41, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_41, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_40
    ui->ui_home_screen_img_40 = lv_img_create(ui->ui_home_screen_cont_20);
    lv_obj_add_flag(ui->ui_home_screen_img_40, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_40, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDreamOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_40, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDreamOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_40, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_40, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_40, 28, 34);
    lv_obj_set_size(ui->ui_home_screen_img_40, 54, 41);

    //Write style for ui_home_screen_img_40, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_40, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_40, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_29
    ui->ui_home_screen_label_29 = lv_label_create(ui->ui_home_screen_cont_20);
    lv_label_set_text(ui->ui_home_screen_label_29, "梦幻帘");
    lv_label_set_long_mode(ui->ui_home_screen_label_29, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_29, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_29, 92, 35);

    //Write style for ui_home_screen_label_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_29, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_29, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_29, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_39
    ui->ui_home_screen_img_39 = lv_img_create(ui->ui_home_screen_cont_20);
    lv_obj_add_flag(ui->ui_home_screen_img_39, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_39, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sClose.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_39, "S:/sdfile/EXT_RESERVED/uipackres/ui/sClose.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_39, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_39, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_39, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_img_39, 60, 60);

    //Write style for ui_home_screen_img_39, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_39, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_39, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_38
    ui->ui_home_screen_img_38 = lv_img_create(ui->ui_home_screen_cont_20);
    lv_obj_add_flag(ui->ui_home_screen_img_38, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_38, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sOpen.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_38, "S:/sdfile/EXT_RESERVED/uipackres/ui/sOpen.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_38, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_38, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_38, 160, 30);
    lv_obj_set_size(ui->ui_home_screen_img_38, 60, 60);

    //Write style for ui_home_screen_img_38, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_38, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_38, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_19
    ui->ui_home_screen_cont_19 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_19, 0, 840);
    lv_obj_set_size(ui->ui_home_screen_cont_19, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_19, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_19, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_19, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_19, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_5
    ui->ui_home_screen_imgbtn_5 = lv_imgbtn_create(ui->ui_home_screen_cont_19);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_5_label = lv_label_create(ui->ui_home_screen_imgbtn_5);
    lv_label_set_text(ui->ui_home_screen_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_5, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_5, 48, 48);

    //Write style for ui_home_screen_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_5, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_5, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_5, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_28
    ui->ui_home_screen_label_28 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_28, "空  调");
    lv_label_set_long_mode(ui->ui_home_screen_label_28, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_28, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_28, 86, 35);

    //Write style for ui_home_screen_label_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_28, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_28, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_28, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_27
    ui->ui_home_screen_label_27 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_27, "16℃");
    lv_label_set_long_mode(ui->ui_home_screen_label_27, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_27, 213, 142);
    lv_obj_set_size(ui->ui_home_screen_label_27, 100, 32);

    //Write style for ui_home_screen_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_27, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_27, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_27, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_26
    ui->ui_home_screen_label_26 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_26, "关");
    lv_label_set_long_mode(ui->ui_home_screen_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_26, 123, 33);
    lv_obj_set_size(ui->ui_home_screen_label_26, 61, 37);

    //Write style for ui_home_screen_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_26, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_26, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_25
    ui->ui_home_screen_label_25 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_25, "送风");
    lv_label_set_long_mode(ui->ui_home_screen_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_25, 123, 33);
    lv_obj_set_size(ui->ui_home_screen_label_25, 61, 37);

    //Write style for ui_home_screen_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_25, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_25, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_25, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_37
    ui->ui_home_screen_img_37 = lv_img_create(ui->ui_home_screen_cont_19);
    lv_obj_add_flag(ui->ui_home_screen_img_37, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_37, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sVACimg.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_37, "S:/sdfile/EXT_RESERVED/uipackres/ui/sVACimg.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_37, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_37, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_37, 17, 37);
    lv_obj_set_size(ui->ui_home_screen_img_37, 77, 49);

    //Write style for ui_home_screen_img_37, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_37, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_37, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_36
    ui->ui_home_screen_img_36 = lv_img_create(ui->ui_home_screen_cont_19);
    lv_obj_add_flag(ui->ui_home_screen_img_36, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_36, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sAC.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_36, "S:/sdfile/EXT_RESERVED/uipackres/ui/sAC.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_36, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_36, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_36, 17, 37);
    lv_obj_set_size(ui->ui_home_screen_img_36, 77, 49);

    //Write style for ui_home_screen_img_36, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_36, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_36, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_24
    ui->ui_home_screen_label_24 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_24, "制冷");
    lv_label_set_long_mode(ui->ui_home_screen_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_24, 123, 33);
    lv_obj_set_size(ui->ui_home_screen_label_24, 61, 37);

    //Write style for ui_home_screen_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_24, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_24, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_23
    ui->ui_home_screen_label_23 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_23, "制热");
    lv_label_set_long_mode(ui->ui_home_screen_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_23, 123, 33);
    lv_obj_set_size(ui->ui_home_screen_label_23, 61, 37);

    //Write style for ui_home_screen_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_23, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_23, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_22
    ui->ui_home_screen_label_22 = lv_label_create(ui->ui_home_screen_cont_19);
    lv_label_set_text(ui->ui_home_screen_label_22, "除湿");
    lv_label_set_long_mode(ui->ui_home_screen_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_22, 123, 33);
    lv_obj_set_size(ui->ui_home_screen_label_22, 61, 37);

    //Write style for ui_home_screen_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_22, &lv_font_ZiTiQuanWeiJunHeiW22_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_18
    ui->ui_home_screen_cont_18 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_18, 344, 840);
    lv_obj_set_size(ui->ui_home_screen_cont_18, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_18, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_18, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_18, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_18, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_35
    ui->ui_home_screen_img_35 = lv_img_create(ui->ui_home_screen_cont_18);
    lv_obj_add_flag(ui->ui_home_screen_img_35, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_35, &_small_disc_alpha_51x51);
    lv_img_set_pivot(ui->ui_home_screen_img_35, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_35, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_35, 23, 34);
    lv_obj_set_size(ui->ui_home_screen_img_35, 51, 51);

    //Write style for ui_home_screen_img_35, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_35, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_35, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_34
    ui->ui_home_screen_img_34 = lv_img_create(ui->ui_home_screen_cont_18);
    lv_obj_add_flag(ui->ui_home_screen_img_34, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_34, &_srack_alpha_20x31);
    lv_img_set_pivot(ui->ui_home_screen_img_34, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_34, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_34, 66, 26);
    lv_obj_set_size(ui->ui_home_screen_img_34, 20, 31);

    //Write style for ui_home_screen_img_34, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_34, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_34, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_4
    ui->ui_home_screen_imgbtn_4 = lv_imgbtn_create(ui->ui_home_screen_cont_18);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\small_play.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\small_pause.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/small_play.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/small_pause.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_4_label = lv_label_create(ui->ui_home_screen_imgbtn_4);
    lv_label_set_text(ui->ui_home_screen_imgbtn_4_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_4, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_4, 60, 60);

    //Write style for ui_home_screen_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_4, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_4, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_4, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_21
    ui->ui_home_screen_label_21 = lv_label_create(ui->ui_home_screen_cont_18);
    lv_label_set_text(ui->ui_home_screen_label_21, "音  乐");
    lv_label_set_long_mode(ui->ui_home_screen_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_21, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_21, 91, 35);

    //Write style for ui_home_screen_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_21, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_21, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_17
    ui->ui_home_screen_cont_17 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_17, 0, 1050);
    lv_obj_set_size(ui->ui_home_screen_cont_17, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_17, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_17, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_17, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_17, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_33
    ui->ui_home_screen_img_33 = lv_img_create(ui->ui_home_screen_cont_17);
    lv_obj_add_flag(ui->ui_home_screen_img_33, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_33, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDryRackOn.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_33, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDryRackOn.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_33, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_33, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_33, 24, 16);
    lv_obj_set_size(ui->ui_home_screen_img_33, 104, 58);

    //Write style for ui_home_screen_img_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_33, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_32
    ui->ui_home_screen_img_32 = lv_img_create(ui->ui_home_screen_cont_17);
    lv_obj_add_flag(ui->ui_home_screen_img_32, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_32, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDryRackOff.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_32, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDryRackOff.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_32, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_32, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_32, 24, 16);
    lv_obj_set_size(ui->ui_home_screen_img_32, 104, 27);

    //Write style for ui_home_screen_img_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_32, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_20
    ui->ui_home_screen_label_20 = lv_label_create(ui->ui_home_screen_cont_17);
    lv_label_set_text(ui->ui_home_screen_label_20, "晾衣机");
    lv_label_set_long_mode(ui->ui_home_screen_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_20, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_20, 90, 35);

    //Write style for ui_home_screen_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_20, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_20, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_31
    ui->ui_home_screen_img_31 = lv_img_create(ui->ui_home_screen_cont_17);
    lv_obj_add_flag(ui->ui_home_screen_img_31, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_31, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDown.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_31, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDown.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_31, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_31, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_31, 250, 110);
    lv_obj_set_size(ui->ui_home_screen_img_31, 60, 60);

    //Write style for ui_home_screen_img_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_31, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_30
    ui->ui_home_screen_img_30 = lv_img_create(ui->ui_home_screen_cont_17);
    lv_obj_add_flag(ui->ui_home_screen_img_30, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_30, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sUp.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_30, "S:/sdfile/EXT_RESERVED/uipackres/ui/sUp.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_30, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_30, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_30, 250, 20);
    lv_obj_set_size(ui->ui_home_screen_img_30, 60, 60);

    //Write style for ui_home_screen_img_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_30, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_19
    ui->ui_home_screen_img_19 = lv_img_create(ui->ui_home_screen_cont_17);
    lv_obj_add_flag(ui->ui_home_screen_img_19, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_19, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sDryRackL.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_19, "S:/sdfile/EXT_RESERVED/uipackres/ui/sDryRackL.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_19, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_19, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_19, 63, 20);
    lv_obj_set_size(ui->ui_home_screen_img_19, 21, 5);

    //Write style for ui_home_screen_img_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_19, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_16
    ui->ui_home_screen_cont_16 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_16, 344, 1048);
    lv_obj_set_size(ui->ui_home_screen_cont_16, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_16, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_16, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_16, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_16, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_29
    ui->ui_home_screen_img_29 = lv_img_create(ui->ui_home_screen_cont_16);
    lv_obj_add_flag(ui->ui_home_screen_img_29, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_29, &_sFanAndLTon_alpha_60x60);
    lv_img_set_pivot(ui->ui_home_screen_img_29, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_29, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_29, 19, 27);
    lv_obj_set_size(ui->ui_home_screen_img_29, 60, 60);

    //Write style for ui_home_screen_img_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_29, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_28
    ui->ui_home_screen_img_28 = lv_img_create(ui->ui_home_screen_cont_16);
    lv_obj_add_flag(ui->ui_home_screen_img_28, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_28, &_sFanAndLToff_alpha_60x60);
    lv_img_set_pivot(ui->ui_home_screen_img_28, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_28, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_28, 19, 27);
    lv_obj_set_size(ui->ui_home_screen_img_28, 60, 60);

    //Write style for ui_home_screen_img_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_28, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_3
    ui->ui_home_screen_imgbtn_3 = lv_imgbtn_create(ui->ui_home_screen_cont_16);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_3_label = lv_label_create(ui->ui_home_screen_imgbtn_3);
    lv_label_set_text(ui->ui_home_screen_imgbtn_3_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_3, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_3, 48, 48);

    //Write style for ui_home_screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_3, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_3, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_3, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_label_19
    ui->ui_home_screen_label_19 = lv_label_create(ui->ui_home_screen_cont_16);
    lv_label_set_text(ui->ui_home_screen_label_19, "风扇灯");
    lv_label_set_long_mode(ui->ui_home_screen_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_19, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_19, 91, 35);

    //Write style for ui_home_screen_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_19, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_19, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_19, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_2
    ui->ui_home_screen_imgbtn_2 = lv_imgbtn_create(ui->ui_home_screen_cont_16);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\slightOff.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\slightOn.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/slightOff.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/slightOn.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_2_label = lv_label_create(ui->ui_home_screen_imgbtn_2);
    lv_label_set_text(ui->ui_home_screen_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_2, 160, 20);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_2, 60, 60);

    //Write style for ui_home_screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_cont_15
    ui->ui_home_screen_cont_15 = lv_obj_create(ui->ui_home_screen_tabview_3_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_15, 0, 1260);
    lv_obj_set_size(ui->ui_home_screen_cont_15, 330, 195);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_15, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_15, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_15, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_15, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_18
    ui->ui_home_screen_label_18 = lv_label_create(ui->ui_home_screen_cont_15);
    lv_label_set_text(ui->ui_home_screen_label_18, "浴  霸");
    lv_label_set_long_mode(ui->ui_home_screen_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_18, 20, 135);
    lv_obj_set_size(ui->ui_home_screen_label_18, 86, 35);

    //Write style for ui_home_screen_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_18, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_18, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_27
    ui->ui_home_screen_img_27 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_27, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_27, &_sIdleBtn_alpha_60x60);
    lv_img_set_pivot(ui->ui_home_screen_img_27, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_27, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_27, 250, 30);
    lv_obj_set_size(ui->ui_home_screen_img_27, 60, 60);

    //Write style for ui_home_screen_img_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_27, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_26
    ui->ui_home_screen_img_26 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_26, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_26, &_sHlight_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_26, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_26, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_26, 22, 32);
    lv_obj_set_size(ui->ui_home_screen_img_26, 65, 43);

    //Write style for ui_home_screen_img_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_26, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_imgbtn_1
    ui->ui_home_screen_imgbtn_1 = lv_imgbtn_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\slightOff.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\slightOn.png", NULL);
#else
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/slightOff.png", NULL);
    lv_imgbtn_set_src(ui->ui_home_screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "S:/sdfile/EXT_RESERVED/uipackres/ui/slightOn.png", NULL);
#endif
    ui->ui_home_screen_imgbtn_1_label = lv_label_create(ui->ui_home_screen_imgbtn_1);
    lv_label_set_text(ui->ui_home_screen_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->ui_home_screen_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_home_screen_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_home_screen_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->ui_home_screen_imgbtn_1, 160, 30);
    lv_obj_set_size(ui->ui_home_screen_imgbtn_1, 60, 60);

    //Write style for ui_home_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_home_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for ui_home_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->ui_home_screen_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->ui_home_screen_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for ui_home_screen_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->ui_home_screen_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes ui_home_screen_img_25
    ui->ui_home_screen_img_25 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_25, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_25, &_sLowHeatMode_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_25, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_25, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_25, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_25, 65, 43);

    //Write style for ui_home_screen_img_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_25, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_24
    ui->ui_home_screen_img_24 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_24, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_24, &_sHeatMode_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_24, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_24, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_24, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_24, 65, 43);

    //Write style for ui_home_screen_img_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_24, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_23
    ui->ui_home_screen_img_23 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_23, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_23, &_sventilate_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_23, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_23, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_23, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_23, 65, 43);

    //Write style for ui_home_screen_img_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_23, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_22
    ui->ui_home_screen_img_22 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_22, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_22, &_sFanMode_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_22, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_22, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_22, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_22, 65, 43);

    //Write style for ui_home_screen_img_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_22, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_21
    ui->ui_home_screen_img_21 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_21, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_21, &_sDev_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_21, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_21, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_21, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_21, 65, 43);

    //Write style for ui_home_screen_img_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_21, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_20
    ui->ui_home_screen_img_20 = lv_img_create(ui->ui_home_screen_cont_15);
    lv_obj_add_flag(ui->ui_home_screen_img_20, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_20, &_sIdleMode_alpha_65x43);
    lv_img_set_pivot(ui->ui_home_screen_img_20, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_20, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_20, 23, 33);
    lv_obj_set_size(ui->ui_home_screen_img_20, 65, 43);

    //Write style for ui_home_screen_img_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_20, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_17
    ui->ui_home_screen_label_17 = lv_label_create(ui->ui_home_screen_tileview_1_tile_1);
    lv_label_set_text(ui->ui_home_screen_label_17, "设备管理");
    lv_label_set_long_mode(ui->ui_home_screen_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_17, 40, 25);
    lv_obj_set_size(ui->ui_home_screen_label_17, 120, 33);

    //Write style for ui_home_screen_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_17, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_17, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes ui_home_screen_tabview_1
    ui->ui_home_screen_tabview_1 = lv_tabview_create(ui->ui_home_screen_tileview_1_tile_2, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->ui_home_screen_tabview_1, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_tabview_1, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_tabview_1, LV_SCROLLBAR_MODE_ON);

    //Write style for ui_home_screen_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tabview_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_tabview_1, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_tabview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_tabview_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_tabview_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_tabview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_1_extra_btnm_main_default
    static lv_style_t style_ui_home_screen_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_ui_home_screen_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_ui_home_screen_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_1_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_ui_home_screen_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_1), &style_ui_home_screen_tabview_1_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_1_extra_btnm_items_default
    static lv_style_t style_ui_home_screen_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_ui_home_screen_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_ui_home_screen_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_ui_home_screen_tabview_1_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_1_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_1), &style_ui_home_screen_tabview_1_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_ui_home_screen_tabview_1_extra_btnm_items_checked
    static lv_style_t style_ui_home_screen_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_ui_home_screen_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_1), &style_ui_home_screen_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->ui_home_screen_tabview_1_tab_1 = lv_tabview_add_tab(ui->ui_home_screen_tabview_1,"");
    lv_obj_t * ui_home_screen_tabview_1_tab_1_label = lv_label_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_label_set_text(ui_home_screen_tabview_1_tab_1_label, "");

    //Write codes ui_home_screen_cont_8
    ui->ui_home_screen_cont_8 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_8, 345, 400);
    lv_obj_set_size(ui->ui_home_screen_cont_8, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_8, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_8, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_9
    ui->ui_home_screen_label_9 = lv_label_create(ui->ui_home_screen_cont_8);
    lv_label_set_text(ui->ui_home_screen_label_9, "情景模式4");
    lv_label_set_long_mode(ui->ui_home_screen_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_9, 85, 128);
    lv_obj_set_size(ui->ui_home_screen_label_9, 160, 35);

    //Write style for ui_home_screen_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_9, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_12
    ui->ui_home_screen_img_12 = lv_img_create(ui->ui_home_screen_cont_8);
    lv_obj_add_flag(ui->ui_home_screen_img_12, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_12, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LightScene4.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_12, "S:/sdfile/EXT_RESERVED/uipackres/ui/LightScene4.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_12, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_12, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_12, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_12, 48, 48);

    //Write style for ui_home_screen_img_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_12, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_7
    ui->ui_home_screen_cont_7 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_7, 0, 400);
    lv_obj_set_size(ui->ui_home_screen_cont_7, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_7, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_7, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_8
    ui->ui_home_screen_label_8 = lv_label_create(ui->ui_home_screen_cont_7);
    lv_label_set_text(ui->ui_home_screen_label_8, "情景模式3");
    lv_label_set_long_mode(ui->ui_home_screen_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_8, 85, 122);
    lv_obj_set_size(ui->ui_home_screen_label_8, 150, 40);

    //Write style for ui_home_screen_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_8, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_11
    ui->ui_home_screen_img_11 = lv_img_create(ui->ui_home_screen_cont_7);
    lv_obj_add_flag(ui->ui_home_screen_img_11, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_11, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LightScene3.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_11, "S:/sdfile/EXT_RESERVED/uipackres/ui/LightScene3.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_11, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_11, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_11, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_11, 48, 48);

    //Write style for ui_home_screen_img_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_11, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_6
    ui->ui_home_screen_cont_6 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_6, 0, 200);
    lv_obj_set_size(ui->ui_home_screen_cont_6, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_6, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_6, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_7
    ui->ui_home_screen_label_7 = lv_label_create(ui->ui_home_screen_cont_6);
    lv_label_set_text(ui->ui_home_screen_label_7, "情景模式1");
    lv_label_set_long_mode(ui->ui_home_screen_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_7, 85, 134);
    lv_obj_set_size(ui->ui_home_screen_label_7, 150, 40);

    //Write style for ui_home_screen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_7, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_10
    ui->ui_home_screen_img_10 = lv_img_create(ui->ui_home_screen_cont_6);
    lv_obj_add_flag(ui->ui_home_screen_img_10, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_10, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LightScene1.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_10, "S:/sdfile/EXT_RESERVED/uipackres/ui/LightScene1.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_10, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_10, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_10, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_10, 48, 48);

    //Write style for ui_home_screen_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_5
    ui->ui_home_screen_cont_5 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_5, 344, 200);
    lv_obj_set_size(ui->ui_home_screen_cont_5, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_5, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_5, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_6
    ui->ui_home_screen_label_6 = lv_label_create(ui->ui_home_screen_cont_5);
    lv_label_set_text(ui->ui_home_screen_label_6, "情景模式2");
    lv_label_set_long_mode(ui->ui_home_screen_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_6, 85, 130);
    lv_obj_set_size(ui->ui_home_screen_label_6, 150, 40);

    //Write style for ui_home_screen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_6, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_9
    ui->ui_home_screen_img_9 = lv_img_create(ui->ui_home_screen_cont_5);
    lv_obj_add_flag(ui->ui_home_screen_img_9, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_9, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\LightScene2.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_9, "S:/sdfile/EXT_RESERVED/uipackres/ui/LightScene2.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_9, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_9, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_9, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_9, 48, 48);

    //Write style for ui_home_screen_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_4
    ui->ui_home_screen_cont_4 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_4, 344, 1);
    lv_obj_set_size(ui->ui_home_screen_cont_4, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_4, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_4, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_5
    ui->ui_home_screen_label_5 = lv_label_create(ui->ui_home_screen_cont_4);
    lv_label_set_text(ui->ui_home_screen_label_5, "灯光全关");
    lv_label_set_long_mode(ui->ui_home_screen_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_5, 85, 127);
    lv_obj_set_size(ui->ui_home_screen_label_5, 150, 40);

    //Write style for ui_home_screen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_5, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_8
    ui->ui_home_screen_img_8 = lv_img_create(ui->ui_home_screen_cont_4);
    lv_obj_add_flag(ui->ui_home_screen_img_8, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_8, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_off.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_8, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_off.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_8, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_8, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_8, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_8, 48, 48);

    //Write style for ui_home_screen_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->ui_home_screen_img_8, lv_color_hex(0xc62a2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_3
    ui->ui_home_screen_cont_3 = lv_obj_create(ui->ui_home_screen_tabview_1_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_3, 0, 1);
    lv_obj_set_size(ui->ui_home_screen_cont_3, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_3, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_3, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_4
    ui->ui_home_screen_label_4 = lv_label_create(ui->ui_home_screen_cont_3);
    lv_label_set_text(ui->ui_home_screen_label_4, "灯光全开");
    lv_label_set_long_mode(ui->ui_home_screen_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_4, 85, 130);
    lv_obj_set_size(ui->ui_home_screen_label_4, 150, 40);

    //Write style for ui_home_screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_4, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_7
    ui->ui_home_screen_img_7 = lv_img_create(ui->ui_home_screen_cont_3);
    lv_obj_add_flag(ui->ui_home_screen_img_7, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_7, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\onoff_on.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_7, "S:/sdfile/EXT_RESERVED/uipackres/ui/onoff_on.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_7, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_7, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_7, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_7, 48, 48);

    //Write style for ui_home_screen_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_3
    ui->ui_home_screen_label_3 = lv_label_create(ui->ui_home_screen_tileview_1_tile_2);
    lv_label_set_text(ui->ui_home_screen_label_3, "灯光情景");
    lv_label_set_long_mode(ui->ui_home_screen_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_3, 43, 25);
    lv_obj_set_size(ui->ui_home_screen_label_3, 125, 32);

    //Write style for ui_home_screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_3, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes ui_home_screen_tabview_2
    ui->ui_home_screen_tabview_2 = lv_tabview_create(ui->ui_home_screen_tileview_1_tile_3, LV_DIR_TOP, 85);
    lv_obj_set_pos(ui->ui_home_screen_tabview_2, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_tabview_2, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_tabview_2, LV_SCROLLBAR_MODE_ON);

    //Write style for ui_home_screen_tabview_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tabview_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tabview_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tabview_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_tabview_2, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_tabview_2, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_tabview_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_tabview_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_tabview_2, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_tabview_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tabview_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_tabview_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_2_extra_btnm_main_default
    static lv_style_t style_ui_home_screen_tabview_2_extra_btnm_main_default;
    ui_init_style(&style_ui_home_screen_tabview_2_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_ui_home_screen_tabview_2_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_2_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_2_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_ui_home_screen_tabview_2_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_2_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_2), &style_ui_home_screen_tabview_2_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_2_extra_btnm_items_default
    static lv_style_t style_ui_home_screen_tabview_2_extra_btnm_items_default;
    ui_init_style(&style_ui_home_screen_tabview_2_extra_btnm_items_default);

    lv_style_set_text_color(&style_ui_home_screen_tabview_2_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_ui_home_screen_tabview_2_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_2_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_2), &style_ui_home_screen_tabview_2_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_ui_home_screen_tabview_2_extra_btnm_items_checked
    static lv_style_t style_ui_home_screen_tabview_2_extra_btnm_items_checked;
    ui_init_style(&style_ui_home_screen_tabview_2_extra_btnm_items_checked);

    lv_style_set_text_color(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_2_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_2), &style_ui_home_screen_tabview_2_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->ui_home_screen_tabview_2_tab_1 = lv_tabview_add_tab(ui->ui_home_screen_tabview_2,"");
    lv_obj_t * ui_home_screen_tabview_2_tab_1_label = lv_label_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_label_set_text(ui_home_screen_tabview_2_tab_1_label, "");

    //Write codes ui_home_screen_cont_14
    ui->ui_home_screen_cont_14 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_14, 345, 400);
    lv_obj_set_size(ui->ui_home_screen_cont_14, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_14, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_14, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_14, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_14, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_16
    ui->ui_home_screen_label_16 = lv_label_create(ui->ui_home_screen_cont_14);
    lv_label_set_text(ui->ui_home_screen_label_16, "80%");
    lv_label_set_long_mode(ui->ui_home_screen_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_16, 140, 130);
    lv_obj_set_size(ui->ui_home_screen_label_16, 70, 35);

    //Write style for ui_home_screen_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_16, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_16, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_18
    ui->ui_home_screen_img_18 = lv_img_create(ui->ui_home_screen_cont_14);
    lv_obj_add_flag(ui->ui_home_screen_img_18, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_18, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CuratianS4.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_18, "S:/sdfile/EXT_RESERVED/uipackres/ui/CuratianS4.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_18, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_18, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_18, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_18, 59, 31);

    //Write style for ui_home_screen_img_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_18, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_13
    ui->ui_home_screen_cont_13 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_13, 0, 400);
    lv_obj_set_size(ui->ui_home_screen_cont_13, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_13, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_13, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_13, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_13, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_15
    ui->ui_home_screen_label_15 = lv_label_create(ui->ui_home_screen_cont_13);
    lv_label_set_text(ui->ui_home_screen_label_15, "60%");
    lv_label_set_long_mode(ui->ui_home_screen_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_15, 140, 130);
    lv_obj_set_size(ui->ui_home_screen_label_15, 65, 30);

    //Write style for ui_home_screen_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_15, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_15, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_15, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_17
    ui->ui_home_screen_img_17 = lv_img_create(ui->ui_home_screen_cont_13);
    lv_obj_add_flag(ui->ui_home_screen_img_17, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_17, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CuratianS3.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_17, "S:/sdfile/EXT_RESERVED/uipackres/ui/CuratianS3.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_17, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_17, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_17, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_17, 59, 31);

    //Write style for ui_home_screen_img_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_17, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_12
    ui->ui_home_screen_cont_12 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_12, 0, 200);
    lv_obj_set_size(ui->ui_home_screen_cont_12, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_12, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_12, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_12, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_12, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_14
    ui->ui_home_screen_label_14 = lv_label_create(ui->ui_home_screen_cont_12);
    lv_label_set_text(ui->ui_home_screen_label_14, "20%");
    lv_label_set_long_mode(ui->ui_home_screen_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_14, 140, 130);
    lv_obj_set_size(ui->ui_home_screen_label_14, 61, 35);

    //Write style for ui_home_screen_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_14, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_14, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_16
    ui->ui_home_screen_img_16 = lv_img_create(ui->ui_home_screen_cont_12);
    lv_obj_add_flag(ui->ui_home_screen_img_16, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_16, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CuratianS1.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_16, "S:/sdfile/EXT_RESERVED/uipackres/ui/CuratianS1.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_16, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_16, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_16, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_16, 59, 31);

    //Write style for ui_home_screen_img_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_16, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_11
    ui->ui_home_screen_cont_11 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_11, 344, 200);
    lv_obj_set_size(ui->ui_home_screen_cont_11, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_11, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_11, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_11, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_13
    ui->ui_home_screen_label_13 = lv_label_create(ui->ui_home_screen_cont_11);
    lv_label_set_text(ui->ui_home_screen_label_13, "40%");
    lv_label_set_long_mode(ui->ui_home_screen_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_13, 140, 128);
    lv_obj_set_size(ui->ui_home_screen_label_13, 67, 40);

    //Write style for ui_home_screen_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_13, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_13, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_15
    ui->ui_home_screen_img_15 = lv_img_create(ui->ui_home_screen_cont_11);
    lv_obj_add_flag(ui->ui_home_screen_img_15, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_15, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CuratianS2.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_15, "S:/sdfile/EXT_RESERVED/uipackres/ui/CuratianS2.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_15, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_15, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_15, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_15, 59, 31);

    //Write style for ui_home_screen_img_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_15, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_10
    ui->ui_home_screen_cont_10 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_10, 344, 1);
    lv_obj_set_size(ui->ui_home_screen_cont_10, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_10, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_10, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_10, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_12
    ui->ui_home_screen_label_12 = lv_label_create(ui->ui_home_screen_cont_10);
    lv_label_set_text(ui->ui_home_screen_label_12, "窗帘全关");
    lv_label_set_long_mode(ui->ui_home_screen_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_12, 85, 127);
    lv_obj_set_size(ui->ui_home_screen_label_12, 150, 40);

    //Write style for ui_home_screen_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_12, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_14
    ui->ui_home_screen_img_14 = lv_img_create(ui->ui_home_screen_cont_10);
    lv_obj_add_flag(ui->ui_home_screen_img_14, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_14, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CurAllClose.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_14, "S:/sdfile/EXT_RESERVED/uipackres/ui/CurAllClose.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_14, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_14, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_14, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_14, 53, 31);

    //Write style for ui_home_screen_img_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_14, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_9
    ui->ui_home_screen_cont_9 = lv_obj_create(ui->ui_home_screen_tabview_2_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_9, 0, 1);
    lv_obj_set_size(ui->ui_home_screen_cont_9, 330, 185);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_9, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_9, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_cont_9, lv_color_hex(0x333641), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_cont_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_11
    ui->ui_home_screen_label_11 = lv_label_create(ui->ui_home_screen_cont_9);
    lv_label_set_text(ui->ui_home_screen_label_11, "窗帘全开");
    lv_label_set_long_mode(ui->ui_home_screen_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_11, 85, 130);
    lv_obj_set_size(ui->ui_home_screen_label_11, 150, 40);

    //Write style for ui_home_screen_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_11, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_13
    ui->ui_home_screen_img_13 = lv_img_create(ui->ui_home_screen_cont_9);
    lv_obj_add_flag(ui->ui_home_screen_img_13, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_13, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\CurAllOpen.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_13, "S:/sdfile/EXT_RESERVED/uipackres/ui/CurAllOpen.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_13, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_13, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_13, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_13, 53, 31);

    //Write style for ui_home_screen_img_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_13, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_10
    ui->ui_home_screen_label_10 = lv_label_create(ui->ui_home_screen_tileview_1_tile_3);
    lv_label_set_text(ui->ui_home_screen_label_10, "窗帘情景");
    lv_label_set_long_mode(ui->ui_home_screen_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_10, 43, 25);
    lv_obj_set_size(ui->ui_home_screen_label_10, 125, 32);

    //Write style for ui_home_screen_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_10, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes ui_home_screen_tabview_4
    ui->ui_home_screen_tabview_4 = lv_tabview_create(ui->ui_home_screen_tileview_1_tile_4, LV_DIR_TOP, 0);
    lv_obj_set_pos(ui->ui_home_screen_tabview_4, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_tabview_4, 720, 720);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_tabview_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_tabview_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_home_screen_tabview_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_home_screen_tabview_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_home_screen_tabview_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_tabview_4, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_tabview_4, &lv_font_ZiTiQuanWeiJunHeiW22_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_tabview_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_tabview_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_tabview_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_home_screen_tabview_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_tabview_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_tabview_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_4_extra_btnm_main_default
    static lv_style_t style_ui_home_screen_tabview_4_extra_btnm_main_default;
    ui_init_style(&style_ui_home_screen_tabview_4_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_ui_home_screen_tabview_4_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_4_extra_btnm_main_default, lv_color_hex(0x243241));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_4_extra_btnm_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_ui_home_screen_tabview_4_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_4_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_4), &style_ui_home_screen_tabview_4_extra_btnm_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_ui_home_screen_tabview_4_extra_btnm_items_default
    static lv_style_t style_ui_home_screen_tabview_4_extra_btnm_items_default;
    ui_init_style(&style_ui_home_screen_tabview_4_extra_btnm_items_default);

    lv_style_set_text_color(&style_ui_home_screen_tabview_4_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_ui_home_screen_tabview_4_extra_btnm_items_default, &lv_font_ZiTiQuanWeiJunHeiW22_12);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_4_extra_btnm_items_default, 255);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_4), &style_ui_home_screen_tabview_4_extra_btnm_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_ui_home_screen_tabview_4_extra_btnm_items_checked
    static lv_style_t style_ui_home_screen_tabview_4_extra_btnm_items_checked;
    ui_init_style(&style_ui_home_screen_tabview_4_extra_btnm_items_checked);

    lv_style_set_text_color(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, &lv_font_ZiTiQuanWeiJunHeiW22_20);
    lv_style_set_text_opa(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, 255);
    lv_style_set_border_width(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, 0);
    lv_style_set_radius(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, 255);
    lv_style_set_bg_color(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, lv_color_hex(0x0f0f12));
    lv_style_set_bg_grad_dir(&style_ui_home_screen_tabview_4_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->ui_home_screen_tabview_4), &style_ui_home_screen_tabview_4_extra_btnm_items_checked, LV_PART_ITEMS|LV_STATE_CHECKED);

    //Write codes
    ui->ui_home_screen_tabview_4_tab_1 = lv_tabview_add_tab(ui->ui_home_screen_tabview_4,"");
    lv_obj_t * ui_home_screen_tabview_4_tab_1_label = lv_label_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_label_set_text(ui_home_screen_tabview_4_tab_1_label, "");

    //Write codes ui_home_screen_cont_1_8
    ui->ui_home_screen_cont_1_8 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_8, 348, 697);
    lv_obj_set_size(ui->ui_home_screen_cont_1_8, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_82
    ui->ui_home_screen_img_82 = lv_img_create(ui->ui_home_screen_cont_1_8);
    lv_obj_add_flag(ui->ui_home_screen_img_82, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_82, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\Lscene8.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_82, "S:/sdfile/EXT_RESERVED/uipackres/ui/Lscene8.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_82, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_82, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_82, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_82, 320, 210);

    //Write style for ui_home_screen_img_82, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_82, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_82, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_82, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_82, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_44
    ui->ui_home_screen_label_44 = lv_label_create(ui->ui_home_screen_cont_1_8);
    lv_label_set_text(ui->ui_home_screen_label_44, "场景八");
    lv_label_set_long_mode(ui->ui_home_screen_label_44, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_44, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_44, 140, 35);

    //Write style for ui_home_screen_label_44, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_44, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_44, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_44, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_44, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_44, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_69
    ui->ui_home_screen_img_69 = lv_img_create(ui->ui_home_screen_cont_1_8);
    lv_obj_add_flag(ui->ui_home_screen_img_69, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_69, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene8.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_69, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene8.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_69, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_69, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_69, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_69, 45, 45);

    //Write style for ui_home_screen_img_69, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_69, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_69, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_69, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_69, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_7
    ui->ui_home_screen_cont_1_7 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_7, 7, 697);
    lv_obj_set_size(ui->ui_home_screen_cont_1_7, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_81
    ui->ui_home_screen_img_81 = lv_img_create(ui->ui_home_screen_cont_1_7);
    lv_obj_add_flag(ui->ui_home_screen_img_81, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_81, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\Lscene7.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_81, "S:/sdfile/EXT_RESERVED/uipackres/ui/Lscene7.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_81, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_81, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_81, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_81, 320, 210);

    //Write style for ui_home_screen_img_81, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_81, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_81, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_81, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_81, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_43
    ui->ui_home_screen_label_43 = lv_label_create(ui->ui_home_screen_cont_1_7);
    lv_label_set_text(ui->ui_home_screen_label_43, "场景七");
    lv_label_set_long_mode(ui->ui_home_screen_label_43, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_43, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_43, 102, 30);

    //Write style for ui_home_screen_label_43, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_43, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_43, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_43, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_43, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_68
    ui->ui_home_screen_img_68 = lv_img_create(ui->ui_home_screen_cont_1_7);
    lv_obj_add_flag(ui->ui_home_screen_img_68, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_68, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene7.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_68, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene7.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_68, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_68, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_68, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_68, 45, 45);

    //Write style for ui_home_screen_img_68, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_68, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_68, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_68, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_68, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_6
    ui->ui_home_screen_cont_1_6 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_6, 348, 467);
    lv_obj_set_size(ui->ui_home_screen_cont_1_6, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_80
    ui->ui_home_screen_img_80 = lv_img_create(ui->ui_home_screen_cont_1_6);
    lv_obj_add_flag(ui->ui_home_screen_img_80, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_80, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\Lscene6.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_80, "S:/sdfile/EXT_RESERVED/uipackres/ui/Lscene6.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_80, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_80, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_80, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_80, 320, 210);

    //Write style for ui_home_screen_img_80, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_80, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_80, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_80, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_80, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_37
    ui->ui_home_screen_label_37 = lv_label_create(ui->ui_home_screen_cont_1_6);
    lv_label_set_text(ui->ui_home_screen_label_37, "场景六");
    lv_label_set_long_mode(ui->ui_home_screen_label_37, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_37, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_37, 133, 35);

    //Write style for ui_home_screen_label_37, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_37, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_37, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_37, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_37, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_62
    ui->ui_home_screen_img_62 = lv_img_create(ui->ui_home_screen_cont_1_6);
    lv_obj_add_flag(ui->ui_home_screen_img_62, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_62, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene6.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_62, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene6.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_62, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_62, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_62, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_62, 45, 45);

    //Write style for ui_home_screen_img_62, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_62, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_62, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_62, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_62, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_5
    ui->ui_home_screen_cont_1_5 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_5, 8, 467);
    lv_obj_set_size(ui->ui_home_screen_cont_1_5, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_79
    ui->ui_home_screen_img_79 = lv_img_create(ui->ui_home_screen_cont_1_5);
    lv_obj_add_flag(ui->ui_home_screen_img_79, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_79, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\Lscene5.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_79, "S:/sdfile/EXT_RESERVED/uipackres/ui/Lscene5.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_79, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_79, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_79, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_79, 320, 210);

    //Write style for ui_home_screen_img_79, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_79, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_79, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_79, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_79, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_38
    ui->ui_home_screen_label_38 = lv_label_create(ui->ui_home_screen_cont_1_5);
    lv_label_set_text(ui->ui_home_screen_label_38, "场景五");
    lv_label_set_long_mode(ui->ui_home_screen_label_38, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_38, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_38, 119, 30);

    //Write style for ui_home_screen_label_38, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_38, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_38, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_38, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_38, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_38, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_63
    ui->ui_home_screen_img_63 = lv_img_create(ui->ui_home_screen_cont_1_5);
    lv_obj_add_flag(ui->ui_home_screen_img_63, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_63, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene5.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_63, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene5.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_63, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_63, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_63, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_63, 45, 45);

    //Write style for ui_home_screen_img_63, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_63, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_63, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_63, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_63, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_4
    ui->ui_home_screen_cont_1_4 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_4, 348, 237);
    lv_obj_set_size(ui->ui_home_screen_cont_1_4, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_78
    ui->ui_home_screen_img_78 = lv_img_create(ui->ui_home_screen_cont_1_4);
    lv_obj_add_flag(ui->ui_home_screen_img_78, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_78, &_Lscene4_alpha_320x210);
    lv_img_set_pivot(ui->ui_home_screen_img_78, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_78, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_78, 0, -1);
    lv_obj_set_size(ui->ui_home_screen_img_78, 320, 210);

    //Write style for ui_home_screen_img_78, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_78, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_78, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_78, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_78, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_40
    ui->ui_home_screen_label_40 = lv_label_create(ui->ui_home_screen_cont_1_4);
    lv_label_set_text(ui->ui_home_screen_label_40, "场景四");
    lv_label_set_long_mode(ui->ui_home_screen_label_40, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_40, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_40, 124, 40);

    //Write style for ui_home_screen_label_40, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_40, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_40, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_40, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_40, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_65
    ui->ui_home_screen_img_65 = lv_img_create(ui->ui_home_screen_cont_1_4);
    lv_obj_add_flag(ui->ui_home_screen_img_65, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_65, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene4.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_65, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene4.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_65, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_65, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_65, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_65, 45, 45);

    //Write style for ui_home_screen_img_65, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_65, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_65, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_65, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_65, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_3
    ui->ui_home_screen_cont_1_3 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_3, 8, 237);
    lv_obj_set_size(ui->ui_home_screen_cont_1_3, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_77
    ui->ui_home_screen_img_77 = lv_img_create(ui->ui_home_screen_cont_1_3);
    lv_obj_add_flag(ui->ui_home_screen_img_77, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_77, &_Lscene3_alpha_320x210);
    lv_img_set_pivot(ui->ui_home_screen_img_77, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_77, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_77, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_77, 320, 210);

    //Write style for ui_home_screen_img_77, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_77, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_77, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_77, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_77, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_39
    ui->ui_home_screen_label_39 = lv_label_create(ui->ui_home_screen_cont_1_3);
    lv_label_set_text(ui->ui_home_screen_label_39, "场景三");
    lv_label_set_long_mode(ui->ui_home_screen_label_39, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_39, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_39, 122, 35);

    //Write style for ui_home_screen_label_39, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_39, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_39, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_39, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_39, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_64
    ui->ui_home_screen_img_64 = lv_img_create(ui->ui_home_screen_cont_1_3);
    lv_obj_add_flag(ui->ui_home_screen_img_64, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_64, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene3.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_64, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene3.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_64, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_64, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_64, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_64, 45, 45);

    //Write style for ui_home_screen_img_64, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_64, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_64, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_64, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_64, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_2
    ui->ui_home_screen_cont_1_2 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_2, 348, 7);
    lv_obj_set_size(ui->ui_home_screen_cont_1_2, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_76
    ui->ui_home_screen_img_76 = lv_img_create(ui->ui_home_screen_cont_1_2);
    lv_obj_add_flag(ui->ui_home_screen_img_76, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_76, &_Lscene2_alpha_320x210);
    lv_img_set_pivot(ui->ui_home_screen_img_76, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_76, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_76, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_76, 320, 210);

    //Write style for ui_home_screen_img_76, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_76, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_76, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_76, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_76, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_41
    ui->ui_home_screen_label_41 = lv_label_create(ui->ui_home_screen_cont_1_2);
    lv_label_set_text(ui->ui_home_screen_label_41, "场景二");
    lv_label_set_long_mode(ui->ui_home_screen_label_41, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_41, 116, 125);
    lv_obj_set_size(ui->ui_home_screen_label_41, 150, 40);

    //Write style for ui_home_screen_label_41, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_41, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_41, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_41, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_41, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_41, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_66
    ui->ui_home_screen_img_66 = lv_img_create(ui->ui_home_screen_cont_1_2);
    lv_obj_add_flag(ui->ui_home_screen_img_66, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_66, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene2.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_66, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene2.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_66, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_66, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_66, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_66, 45, 45);

    //Write style for ui_home_screen_img_66, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_66, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_66, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_66, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_66, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_cont_1_1
    ui->ui_home_screen_cont_1_1 = lv_obj_create(ui->ui_home_screen_tabview_4_tab_1);
    lv_obj_set_pos(ui->ui_home_screen_cont_1_1, 8, 5);
    lv_obj_set_size(ui->ui_home_screen_cont_1_1, 320, 210);
    lv_obj_set_scrollbar_mode(ui->ui_home_screen_cont_1_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_home_screen_cont_1_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_cont_1_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_70
    ui->ui_home_screen_img_70 = lv_img_create(ui->ui_home_screen_cont_1_1);
    lv_obj_add_flag(ui->ui_home_screen_img_70, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_home_screen_img_70, &_Lscene1_alpha_320x210);
    lv_img_set_pivot(ui->ui_home_screen_img_70, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_70, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_70, 0, 0);
    lv_obj_set_size(ui->ui_home_screen_img_70, 320, 210);

    //Write style for ui_home_screen_img_70, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_70, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_70, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_70, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_70, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_label_42
    ui->ui_home_screen_label_42 = lv_label_create(ui->ui_home_screen_cont_1_1);
    lv_label_set_text(ui->ui_home_screen_label_42, "场景一");
    lv_label_set_long_mode(ui->ui_home_screen_label_42, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_home_screen_label_42, 115, 125);
    lv_obj_set_size(ui->ui_home_screen_label_42, 90, 40);

    //Write style for ui_home_screen_label_42, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_home_screen_label_42, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_home_screen_label_42, &lv_font_MiSansNormal_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_home_screen_label_42, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_home_screen_label_42, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_home_screen_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_home_screen_img_67
    ui->ui_home_screen_img_67 = lv_img_create(ui->ui_home_screen_cont_1_1);
    lv_obj_add_flag(ui->ui_home_screen_img_67, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
    lv_img_set_src(ui->ui_home_screen_img_67, "D:\\7.NXP-GUI-PROJECT\\4_inch_screen_tileview\\import\\image\\sLscene1.png");
#else
    lv_img_set_src(ui->ui_home_screen_img_67, "S:/sdfile/EXT_RESERVED/uipackres/ui/sLscene1.png");
#endif
    lv_img_set_pivot(ui->ui_home_screen_img_67, 50,50);
    lv_img_set_angle(ui->ui_home_screen_img_67, 0);
    lv_obj_set_pos(ui->ui_home_screen_img_67, 135, 40);
    lv_obj_set_size(ui->ui_home_screen_img_67, 45, 45);

    //Write style for ui_home_screen_img_67, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_home_screen_img_67, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_home_screen_img_67, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_home_screen_img_67, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_home_screen_img_67, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of ui_home_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->ui_home_screen);

    //Init events for screen.
    events_init_ui_home_screen(ui);
}
