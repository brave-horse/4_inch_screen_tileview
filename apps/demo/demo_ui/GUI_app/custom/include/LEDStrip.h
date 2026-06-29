#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void led_strip_on_screen_load(void);
void led_strip_on_switch_toggle(lv_event_t *e);
void led_strip_on_bri_slider_change(void);
void led_strip_on_ct_slider_change(void);

#ifdef __cplusplus
}
#endif

#endif
