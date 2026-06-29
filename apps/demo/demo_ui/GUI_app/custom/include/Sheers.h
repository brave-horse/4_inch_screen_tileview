#ifndef SHEERS_H
#define SHEERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void sheers_on_screen_load(void);
void sheers_on_open(void);
void sheers_on_pause(void);
void sheers_on_close(void);
void sheers_on_drag(lv_event_t *e);

#ifdef __cplusplus
}
#endif

#endif
