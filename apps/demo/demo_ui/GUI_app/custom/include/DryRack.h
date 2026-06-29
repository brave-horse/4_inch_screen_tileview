#ifndef DRYRACK_H
#define DRYRACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void dryrack_on_screen_load(void);
void dryrack_on_light_toggle(lv_event_t *e);  /* imgbtn_1 Clicked */
void dryrack_on_drag(lv_event_t *e);          /* label_1 + img_1 Pressing */
void dryrack_on_open(void);                   /* FabCurtianOpen 上升 */
void dryrack_on_pause(void);                  /* FabCurtianPause 暂停 */
void dryrack_on_close(void);                  /* FabCurtianClose 下降 */

#ifdef __cplusplus
}
#endif

#endif
