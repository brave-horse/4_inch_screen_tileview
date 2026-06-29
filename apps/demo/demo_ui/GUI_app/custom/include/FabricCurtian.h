#ifndef FABRICCURTIAN_H
#define FABRICCURTIAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void fab_curtain_on_screen_load(void);
void fab_curtain_on_open(void);
void fab_curtain_on_pause(void);
void fab_curtain_on_close(void);
void fab_curtain_on_drag(lv_event_t *e);

#ifdef __cplusplus
}
#endif

#endif
