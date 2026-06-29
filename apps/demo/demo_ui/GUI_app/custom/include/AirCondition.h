#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void aircon_on_screen_load(void);
void aircon_on_power_toggle(lv_event_t *e);  /* 挂到 ACBtn 电源键 Clicked */
void aircon_on_mode_click(void);    /* 挂到 AcCool/ACHot/ACFan/ACDry 四图 Clicked */
void aircon_on_speed_click(void);   /* 挂到 ACSpeed1/2/3/Auto 四图 Clicked */

#ifdef __cplusplus
}
#endif

#endif
