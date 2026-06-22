#ifndef ROLLBLIND_H
#define ROLLBLIND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void roll_blind_on_screen_load(void);
void roll_blind_on_open(void);
void roll_blind_on_pause(void);
void roll_blind_on_close(void);
void roll_blind_on_drag(lv_event_t *event);

#ifdef __cplusplus
}
#endif

#endif
