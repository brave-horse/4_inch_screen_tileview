/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void events_init(lv_ui *ui);

void events_init_ui_home_screen(lv_ui *ui);
void events_init_light_CT_screen(lv_ui *ui);
void events_init_LedStrip(lv_ui *ui);
void events_init_RGBLight(lv_ui *ui);
void events_init_MagLight(lv_ui *ui);
void events_init_FabricCurtian(lv_ui *ui);
void events_init_Sheers(lv_ui *ui);
void events_init_RollBlind(lv_ui *ui);
void events_init_Dream(lv_ui *ui);
void events_init_AirCondition(lv_ui *ui);
void events_init_Music(lv_ui *ui);
void events_init_DryRack(lv_ui *ui);
void events_init_FanAndLight(lv_ui *ui);
void events_init_Heater(lv_ui *ui);
void events_init_setting_screen(lv_ui *ui);
void events_init_PlaySet(lv_ui *ui);
void events_init_SwitchSet(lv_ui *ui);
void events_init_SensorSet(lv_ui *ui);
void events_init_Reset(lv_ui *ui);
void events_init_huifuchuchangshezhi(lv_ui *ui);
void events_init_NetSett(lv_ui *ui);
void events_init_Helper(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
