#ifndef MUSIC_H
#define MUSIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void music_on_screen_load(void);
void music_on_play_toggle(lv_event_t *event);   /* Music_play Clicked */

#ifdef __cplusplus
}
#endif

#endif
