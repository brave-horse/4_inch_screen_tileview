/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "Home.h"
#include "nav.h"


#include "light_CT_screen.h"
#include "LEDStrip.h"
#include "RGBLight.h"
#include "MagLight.h"
#include "FabricCurtian.h"
#include "Sheers.h"
#include "RollBlind.h"
#include "Dream.h"
#include "AirCondition.h"
#include "Music.h"
#include "DryRack.h"
#include "FanAndLight.h"
#include "Heater.h"
#include "Setting.h"
#include "NetSetting.h"

#include "PlaySet.h"


static void ui_home_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        home_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_27_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_LIGHT_CT);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_9_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_ct_on_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_26_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_LEDSTRIP);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_led_on_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_25_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_MAGLIGHT);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_mag_on_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_24_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_RGBLIGHT);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_rgb_on_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_23_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_FABRICCURTAIN);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_51_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_fabric_close();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_50_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_fabric_open();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_22_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_SHEERS);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_47_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_sheers_open();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_46_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_sheers_close();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_21_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_ROLLBLIND);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_43_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_rollblind_close();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_42_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_rollblind_open();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_20_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_DREAM);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_39_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_dream_close();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_38_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_dream_open();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_19_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_AIRCONDITION);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_18_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_MUSIC);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_music_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_17_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_DRYRACK);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_31_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_dryrack_down();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_30_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_dryrack_up();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_16_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_FANANDLIGHT);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_fanlight_fan_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_fanlight_light_toggle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_cont_15_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_go(SCR_HEATER);
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_img_27_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dev_mgmt_heater_idle();
        break;
    }
    default:
        break;
    }
}

static void ui_home_screen_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dev_mgmt_heater_light_toggle();
        break;
    }
    default:
        break;
    }
}

void events_init_ui_home_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->ui_home_screen, ui_home_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_27, ui_home_screen_cont_27_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_9, ui_home_screen_imgbtn_9_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_26, ui_home_screen_cont_26_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_8, ui_home_screen_imgbtn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_25, ui_home_screen_cont_25_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_7, ui_home_screen_imgbtn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_24, ui_home_screen_cont_24_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_6, ui_home_screen_imgbtn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_23, ui_home_screen_cont_23_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_51, ui_home_screen_img_51_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_50, ui_home_screen_img_50_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_22, ui_home_screen_cont_22_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_47, ui_home_screen_img_47_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_46, ui_home_screen_img_46_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_21, ui_home_screen_cont_21_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_43, ui_home_screen_img_43_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_42, ui_home_screen_img_42_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_20, ui_home_screen_cont_20_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_39, ui_home_screen_img_39_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_38, ui_home_screen_img_38_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_19, ui_home_screen_cont_19_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_18, ui_home_screen_cont_18_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_4, ui_home_screen_imgbtn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_17, ui_home_screen_cont_17_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_31, ui_home_screen_img_31_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_30, ui_home_screen_img_30_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_16, ui_home_screen_cont_16_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_3, ui_home_screen_imgbtn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_2, ui_home_screen_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_cont_15, ui_home_screen_cont_15_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_img_27, ui_home_screen_img_27_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->ui_home_screen_imgbtn_1, ui_home_screen_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void light_CT_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.light_CT_screen_label_2, 600, 0, lv_obj_get_x(guider_ui.light_CT_screen_label_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.light_CT_screen_slider_1, 600, 0, lv_obj_get_x(guider_ui.light_CT_screen_slider_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.light_CT_screen_slider_2, 600, 0, lv_obj_get_x(guider_ui.light_CT_screen_slider_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.light_CT_screen_label_1, 600, 0, lv_obj_get_x(guider_ui.light_CT_screen_label_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        light_ct_on_screen_load();
        ui_animation(guider_ui.light_CT_screen_ct_bar, 600, 0, lv_obj_get_x(guider_ui.light_CT_screen_ct_bar), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_slider_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        light_ct_on_ct_slider_change();
        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        light_ct_on_bri_slider_change();
        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {

        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_on_off_2_img_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        light_ct_on_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void light_CT_screen_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_light_CT_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->light_CT_screen, light_CT_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_slider_2, light_CT_screen_slider_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_slider_1, light_CT_screen_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_btn_1, light_CT_screen_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_imgbtn_1, light_CT_screen_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_on_off_2_img, light_CT_screen_on_off_2_img_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->light_CT_screen_btn_2, light_CT_screen_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void LedStrip_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.LedStrip_label_1, 600, 0, lv_obj_get_x(guider_ui.LedStrip_label_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.LedStrip_slider_1, 600, 0, lv_obj_get_x(guider_ui.LedStrip_slider_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.LedStrip_slider_2, 600, 0, lv_obj_get_x(guider_ui.LedStrip_slider_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.LedStrip_label_2, 600, 0, lv_obj_get_x(guider_ui.LedStrip_label_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.LedStrip_ct_bar, 600, 0, lv_obj_get_x(guider_ui.LedStrip_ct_bar), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        led_strip_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void LedStrip_slider_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        led_strip_on_ct_slider_change();
        break;
    }
    default:
        break;
    }
}

static void LedStrip_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        led_strip_on_bri_slider_change();
        break;
    }
    default:
        break;
    }
}

static void LedStrip_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void LedStrip_on_off_2_img_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        led_strip_on_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void LedStrip_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_LedStrip (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->LedStrip, LedStrip_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->LedStrip_slider_2, LedStrip_slider_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->LedStrip_slider_1, LedStrip_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->LedStrip_btn_1, LedStrip_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->LedStrip_on_off_2_img, LedStrip_on_off_2_img_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->LedStrip_btn_4, LedStrip_btn_4_event_handler, LV_EVENT_ALL, ui);
}

static void RGBLight_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.RGBLight_label_1, 600, 0, lv_obj_get_x(guider_ui.RGBLight_label_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.RGBLight_slider_2, 600, 0, lv_obj_get_x(guider_ui.RGBLight_slider_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.RGBLight_ct_bar, 600, 0, lv_obj_get_x(guider_ui.RGBLight_ct_bar), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.RGBLight_label_2, 600, 0, lv_obj_get_x(guider_ui.RGBLight_label_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.RGBLight_slider_1, 600, 0, lv_obj_get_x(guider_ui.RGBLight_slider_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        rgb_light_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void RGBLight_slider_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        rgb_light_on_color_slider_change();
        break;
    }
    default:
        break;
    }
}

static void RGBLight_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        rgb_light_on_bri_slider_change();
        break;
    }
    default:
        break;
    }
}

static void RGBLight_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void RGBLight_on_off_2_img_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        rgb_light_on_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void RGBLight_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_RGBLight (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->RGBLight, RGBLight_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RGBLight_slider_2, RGBLight_slider_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RGBLight_slider_1, RGBLight_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RGBLight_btn_1, RGBLight_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RGBLight_on_off_2_img, RGBLight_on_off_2_img_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RGBLight_btn_2, RGBLight_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void MagLight_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.MagLight_label_1, 600, 0, lv_obj_get_x(guider_ui.MagLight_label_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.MagLight_slider_1, 600, 0, lv_obj_get_x(guider_ui.MagLight_slider_1), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.MagLight_slider_2, 600, 0, lv_obj_get_x(guider_ui.MagLight_slider_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.MagLight_ct_bar, 600, 0, lv_obj_get_x(guider_ui.MagLight_ct_bar), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        ui_animation(guider_ui.MagLight_label_2, 600, 0, lv_obj_get_x(guider_ui.MagLight_label_2), 33, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
        mag_light_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void MagLight_slider_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        mag_light_on_ct_slider_change();
        break;
    }
    default:
        break;
    }
}

static void MagLight_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        mag_light_on_bri_slider_change();
        break;
    }
    default:
        break;
    }
}

static void MagLight_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void MagLight_on_off_2_img_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        mag_light_on_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void MagLight_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_MagLight (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->MagLight, MagLight_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MagLight_slider_2, MagLight_slider_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MagLight_slider_1, MagLight_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MagLight_btn_1, MagLight_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MagLight_on_off_2_img, MagLight_on_off_2_img_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MagLight_btn_2, MagLight_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void FabricCurtian_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.FabricCurtian_FabCurtianPause, 300, 0, lv_obj_get_y(guider_ui.FabricCurtian_FabCurtianPause), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.FabricCurtian_FabCurtianClose, 300, 0, lv_obj_get_y(guider_ui.FabricCurtian_FabCurtianClose), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.FabricCurtian_FabCurtianOpen, 300, 0, lv_obj_get_y(guider_ui.FabricCurtian_FabCurtianOpen), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        fab_curtain_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianOpen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fab_curtain_on_open();
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianClose_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fab_curtain_on_close();
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianPause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fab_curtain_on_pause();
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianLeft_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianright_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianPull2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianPull1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianPull3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void FabricCurtian_FabCurtianPull4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        fab_curtain_on_drag(e);
        break;
    }
    default:
        break;
    }
}

void events_init_FabricCurtian (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->FabricCurtian, FabricCurtian_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_btn_1, FabricCurtian_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianOpen, FabricCurtian_FabCurtianOpen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianClose, FabricCurtian_FabCurtianClose_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianPause, FabricCurtian_FabCurtianPause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianLeft, FabricCurtian_FabCurtianLeft_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianright, FabricCurtian_FabCurtianright_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianPull2, FabricCurtian_FabCurtianPull2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianPull1, FabricCurtian_FabCurtianPull1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_btn_2, FabricCurtian_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianPull3, FabricCurtian_FabCurtianPull3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FabricCurtian_FabCurtianPull4, FabricCurtian_FabCurtianPull4_event_handler, LV_EVENT_ALL, ui);
}

static void Sheers_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.Sheers_FabCurtianPause, 300, 0, lv_obj_get_y(guider_ui.Sheers_FabCurtianPause), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.Sheers_FabCurtianClose, 300, 0, lv_obj_get_y(guider_ui.Sheers_FabCurtianClose), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.Sheers_FabCurtianOpen, 300, 0, lv_obj_get_y(guider_ui.Sheers_FabCurtianOpen), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        sheers_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void Sheers_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianOpen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sheers_on_open();
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianClose_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sheers_on_close();
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianPause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sheers_on_pause();
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianLeft_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianright_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianPull2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianPull1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Sheers_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianPull4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Sheers_FabCurtianPull3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        sheers_on_drag(e);
        break;
    }
    default:
        break;
    }
}

void events_init_Sheers (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Sheers, Sheers_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_btn_1, Sheers_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianOpen, Sheers_FabCurtianOpen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianClose, Sheers_FabCurtianClose_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianPause, Sheers_FabCurtianPause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianLeft, Sheers_FabCurtianLeft_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianright, Sheers_FabCurtianright_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianPull2, Sheers_FabCurtianPull2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianPull1, Sheers_FabCurtianPull1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_btn_2, Sheers_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianPull4, Sheers_FabCurtianPull4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Sheers_FabCurtianPull3, Sheers_FabCurtianPull3_event_handler, LV_EVENT_ALL, ui);
}

static void RollBlind_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.RollBlind_FabCurtianPause, 300, 0, lv_obj_get_y(guider_ui.RollBlind_FabCurtianPause), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.RollBlind_FabCurtianClose, 300, 0, lv_obj_get_y(guider_ui.RollBlind_FabCurtianClose), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.RollBlind_FabCurtianOpen, 300, 0, lv_obj_get_y(guider_ui.RollBlind_FabCurtianOpen), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        roll_blind_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianOpen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        roll_blind_on_open();
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianClose_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        roll_blind_on_close();
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianPause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        roll_blind_on_pause();
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianLeft_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSED:
    {
        roll_blind_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianPull1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        roll_blind_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void RollBlind_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void RollBlind_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void RollBlind_FabCurtianPull2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        roll_blind_on_drag(e);
        break;
    }
    default:
        break;
    }
}

void events_init_RollBlind (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->RollBlind, RollBlind_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianOpen, RollBlind_FabCurtianOpen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianClose, RollBlind_FabCurtianClose_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianPause, RollBlind_FabCurtianPause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianLeft, RollBlind_FabCurtianLeft_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianPull1, RollBlind_FabCurtianPull1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_btn_1, RollBlind_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_btn_2, RollBlind_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->RollBlind_FabCurtianPull2, RollBlind_FabCurtianPull2_event_handler, LV_EVENT_ALL, ui);
}

static void Dream_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.Dream_FabCurtianPause, 300, 0, lv_obj_get_y(guider_ui.Dream_FabCurtianPause), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.Dream_FabCurtianClose, 300, 0, lv_obj_get_y(guider_ui.Dream_FabCurtianClose), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.Dream_FabCurtianOpen, 300, 0, lv_obj_get_y(guider_ui.Dream_FabCurtianOpen), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        dream_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void Dream_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianOpen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dream_on_open();
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianClose_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dream_on_close();
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianPause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dream_on_pause();
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianLeft_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianright_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianPull2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianPull1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Dream_slider_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        dream_on_angle_slider_change();
        break;
    }
    default:
        break;
    }
}

static void Dream_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianPull3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void Dream_FabCurtianPull4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dream_on_drag(e);
        break;
    }
    default:
        break;
    }
}

void events_init_Dream (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Dream, Dream_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_btn_1, Dream_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianOpen, Dream_FabCurtianOpen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianClose, Dream_FabCurtianClose_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianPause, Dream_FabCurtianPause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianLeft, Dream_FabCurtianLeft_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianright, Dream_FabCurtianright_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianPull2, Dream_FabCurtianPull2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianPull1, Dream_FabCurtianPull1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_slider_1, Dream_slider_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_btn_2, Dream_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianPull3, Dream_FabCurtianPull3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Dream_FabCurtianPull4, Dream_FabCurtianPull4_event_handler, LV_EVENT_ALL, ui);
}

static void AirCondition_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        aircon_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_power_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACSpeedAuto_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACSpeed3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACSpeed2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACSpeed1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_AcCool_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_mode_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACFan_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_mode_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACHot_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_mode_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_ACDry_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        aircon_on_mode_click();
        break;
    }
    default:
        break;
    }
}

static void AirCondition_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_AirCondition (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->AirCondition, AirCondition_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_btn_1, AirCondition_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACBtn, AirCondition_ACBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACSpeedAuto, AirCondition_ACSpeedAuto_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACSpeed3, AirCondition_ACSpeed3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACSpeed2, AirCondition_ACSpeed2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACSpeed1, AirCondition_ACSpeed1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_AcCool, AirCondition_AcCool_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACFan, AirCondition_ACFan_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACHot, AirCondition_ACHot_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_ACDry, AirCondition_ACDry_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->AirCondition_btn_2, AirCondition_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void Music_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        music_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void Music_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void Music_play_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        music_on_play_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void Music_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_Music (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Music, Music_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Music_btn_1, Music_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Music_play, Music_play_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Music_btn_2, Music_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void DryRack_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.DryRack_FabCurtianPause, 300, 0, lv_obj_get_y(guider_ui.DryRack_FabCurtianPause), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.DryRack_FabCurtianClose, 300, 0, lv_obj_get_y(guider_ui.DryRack_FabCurtianClose), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        ui_animation(guider_ui.DryRack_FabCurtianOpen, 300, 0, lv_obj_get_y(guider_ui.DryRack_FabCurtianOpen), 588, &lv_anim_path_linear, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
        dryrack_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void DryRack_FabCurtianOpen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dryrack_on_open();
        break;
    }
    default:
        break;
    }
}

static void DryRack_FabCurtianClose_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dryrack_on_close();
        break;
    }
    default:
        break;
    }
}

static void DryRack_FabCurtianPause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dryrack_on_pause();
        break;
    }
    default:
        break;
    }
}

static void DryRack_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dryrack_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void DryRack_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        dryrack_on_light_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void DryRack_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void DryRack_label_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dryrack_on_drag(e);
        break;
    }
    default:
        break;
    }
}

static void DryRack_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void DryRack_dry_rack_pull_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_PRESSING:
    {
        dryrack_on_drag(e);
        break;
    }
    default:
        break;
    }
}

void events_init_DryRack (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->DryRack, DryRack_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_FabCurtianOpen, DryRack_FabCurtianOpen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_FabCurtianClose, DryRack_FabCurtianClose_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_FabCurtianPause, DryRack_FabCurtianPause_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_img_1, DryRack_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_imgbtn_1, DryRack_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_btn_1, DryRack_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_label_1, DryRack_label_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_btn_2, DryRack_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->DryRack_dry_rack_pull, DryRack_dry_rack_pull_event_handler, LV_EVENT_ALL, ui);
}

static void FanAndLight_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        fanlight_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_fLight_off_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_light_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_fLight_on_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_light_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_FanSpeed4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_FanSpeed3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_FanSpeed2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_FanSpeed1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_speed_click();
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_Fan_on_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_fan_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_Fan_off_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_fan_switch_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        fanlight_on_power_toggle(e);
        break;
    }
    default:
        break;
    }
}

static void FanAndLight_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_FanAndLight (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->FanAndLight, FanAndLight_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_fLight_off, FanAndLight_fLight_off_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_fLight_on, FanAndLight_fLight_on_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_FanSpeed4, FanAndLight_FanSpeed4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_FanSpeed3, FanAndLight_FanSpeed3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_FanSpeed2, FanAndLight_FanSpeed2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_FanSpeed1, FanAndLight_FanSpeed1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_Fan_on, FanAndLight_Fan_on_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_Fan_off, FanAndLight_Fan_off_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_btn_1, FanAndLight_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_imgbtn_1, FanAndLight_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->FanAndLight_btn_2, FanAndLight_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void Heater_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        heater_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void Heater_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void Heater_LightBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_light_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_LightOnImg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_light_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_IdleBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_idle_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_VentilateBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_ventilate_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_VentilateImg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_ventilate_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_HeatLowBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_low_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_HeatLowImg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_low_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_WindBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_wind_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_WindImg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_wind_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_HeatHighBtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_high_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_HeatHighImg_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        heater_on_high_click();
        break;
    }
    default:
        break;
    }
}

static void Heater_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_Heater (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Heater, Heater_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_btn_1, Heater_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_LightBtn, Heater_LightBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_LightOnImg, Heater_LightOnImg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_IdleBtn, Heater_IdleBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_VentilateBtn, Heater_VentilateBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_VentilateImg, Heater_VentilateImg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_HeatLowBtn, Heater_HeatLowBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_HeatLowImg, Heater_HeatLowImg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_WindBtn, Heater_WindBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_WindImg, Heater_WindImg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_HeatHighBtn, Heater_HeatHighBtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_HeatHighImg, Heater_HeatHighImg_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Heater_btn_2, Heater_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void setting_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        setting_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void setting_screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.ui_home_screen, guider_ui.ui_home_screen_del, &guider_ui.setting_screen_del, setup_scr_ui_home_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void setting_screen_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

static void setting_screen_cont_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.NetSetting, guider_ui.NetSetting_del, &guider_ui.setting_screen_del, setup_scr_NetSetting, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_setting_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->setting_screen, setting_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->setting_screen_btn_1, setting_screen_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->setting_screen_btn_2, setting_screen_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->setting_screen_cont_3, setting_screen_cont_3_event_handler, LV_EVENT_ALL, ui);
}

static void NetSetting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        netsetting_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void NetSetting_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.NetSetting_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_NetSetting (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->NetSetting, NetSetting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->NetSetting_btn_1, NetSetting_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void PlaySet_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        playset_on_screen_load();
        break;
    }
    default:
        break;
    }
}

static void PlaySet_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.PlaySet_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_PlaySet (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->PlaySet, PlaySet_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->PlaySet_btn_2, PlaySet_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void SwitchSet_btn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.SwitchSet_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_SwitchSet (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->SwitchSet_btn_8, SwitchSet_btn_8_event_handler, LV_EVENT_ALL, ui);
}

static void SensorSet_btn_13_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.SensorSet_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_SensorSet (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->SensorSet_btn_13, SensorSet_btn_13_event_handler, LV_EVENT_ALL, ui);
}

static void Reset_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.Reset_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Reset (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Reset_btn_4, Reset_btn_4_event_handler, LV_EVENT_ALL, ui);
}

static void huifuchuchangshezhi_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.huifuchuchangshezhi_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_huifuchuchangshezhi (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->huifuchuchangshezhi_btn_4, huifuchuchangshezhi_btn_4_event_handler, LV_EVENT_ALL, ui);
}

static void RelativeProduct_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.RelativeProduct_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_RelativeProduct (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->RelativeProduct_btn_4, RelativeProduct_btn_4_event_handler, LV_EVENT_ALL, ui);
}

static void Helper_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        nav_back();
        break;
    }
    default:
        break;
    }
}

void events_init_Helper (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Helper_btn_1, Helper_btn_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
