#ifndef MAGLIGHT_H
#define MAGLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void mag_light_on_screen_load(void);
void mag_light_on_switch_toggle(lv_event_t *e);
void mag_light_on_bri_slider_change(void);
void mag_light_on_ct_slider_change(void);

#ifdef __cplusplus
}
#endif

#endif
