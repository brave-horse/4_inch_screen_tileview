#ifndef HOME_H
#define HOME_H

/* dev_mgmt_* 声明: events_init.c 只 include Home.h, 经此间接拿到声明, 消 implicit 警告 */
#include "device_management.h"

#ifdef __cplusplus
extern "C" {
#endif

void home_on_screen_load(void);          /* Screen Loaded: 清 img CLICKABLE + btn_1/2/3 按下反馈 */
void home_preload_scene(void);           /* 预解码场景页大图, 由 scr_guard 在 purge 之后调 */
void home_btn_4_clicked(lv_event_t *e);  /* 空桩: 逻辑已移到 pulldown.c, 重导出后可删 */
void home_btn_6_clicked(lv_event_t *e);  /* 空桩: 逻辑已移到 pulldown.c, 重导出后可删 */

#ifdef __cplusplus
}
#endif

#endif
