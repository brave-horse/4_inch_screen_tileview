#ifndef RGBLIGHT_H
#define RGBLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void rgb_light_on_screen_load(void);
void rgb_light_on_switch_toggle(lv_event_t *e);
void rgb_light_on_bri_slider_change(void);
void rgb_light_on_color_slider_change(void);

#ifdef __cplusplus
}
#endif

#endif
