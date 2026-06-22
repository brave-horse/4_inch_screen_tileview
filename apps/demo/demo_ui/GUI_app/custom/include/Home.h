#ifndef HOME_H
#define HOME_H

#ifdef __cplusplus
extern "C" {
#endif

void home_on_screen_load(void);          /* Screen Loaded: 清 img CLICKABLE + btn_1/2/3 按下反馈 */
void home_btn_4_clicked(lv_event_t *e);  /* 空桩: 逻辑已移到 pulldown.c, 重导出后可删 */
void home_btn_6_clicked(lv_event_t *e);  /* 空桩: 逻辑已移到 pulldown.c, 重导出后可删 */

#ifdef __cplusplus
}
#endif

#endif
