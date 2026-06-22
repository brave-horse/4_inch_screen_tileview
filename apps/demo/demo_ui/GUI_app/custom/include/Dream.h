#ifndef DREAM_H
#define DREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void dream_on_screen_load(void);
void dream_on_open(void);
void dream_on_pause(void);
void dream_on_close(void);
void dream_on_drag(lv_event_t *e);
void dream_on_angle_slider_change(void);

#ifdef __cplusplus
}
#endif

#endif
