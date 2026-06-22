#ifndef CUSTOM_SCREEN_H
#define CUSTOM_SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void light_CT_screen_apply_light(void);
void light_ct_on_screen_load(void);
void light_ct_on_switch_toggle(lv_event_t *e);
void light_ct_on_bri_slider_change(void);
void light_ct_on_ct_slider_change(void);

#ifdef __cplusplus
}
#endif

#endif
