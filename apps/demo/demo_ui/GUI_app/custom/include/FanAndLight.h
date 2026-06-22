#ifndef FANANDLIGHT_H
#define FANANDLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void fanlight_on_screen_load(void);
void fanlight_on_power_toggle(lv_event_t *event);        /* imgbtn_1 Clicked */
void fanlight_on_fan_switch_toggle(lv_event_t *event);   /* Fan_off + Fan_on Clicked */
void fanlight_on_speed_click(void);                       /* FanSpeed1/2/3/4 Clicked */
void fanlight_on_light_switch_toggle(lv_event_t *event); /* fLight_off + fLight_on Clicked */
float fanlight_speed_rps(void);                          /* 当前档位转速(管理屏同步用) */

#ifdef __cplusplus
}
#endif

#endif
