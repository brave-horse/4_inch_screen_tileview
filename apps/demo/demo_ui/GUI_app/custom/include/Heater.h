#ifndef HEATER_H
#define HEATER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void heater_on_screen_load(void);
void heater_on_light_click(void);
void heater_on_high_click(void);
void heater_on_low_click(void);
void heater_on_ventilate_click(void);
void heater_on_wind_click(void);
void heater_on_idle_click(void);

#ifdef __cplusplus
}
#endif
#endif
