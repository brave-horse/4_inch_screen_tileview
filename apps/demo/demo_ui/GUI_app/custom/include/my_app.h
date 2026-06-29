#ifndef MY_APP_H
#define MY_APP_H

#include "gui_guider.h"

#ifdef __cplusplus
extern "C" {
#endif

/* event 层：UI 给上层 App 业务提供的统一接口入口(对应需求文档 custom/event)。
 *
 * 职责：把 generated 控件产生的 UI 事件(触摸/按键/值变化)桥接成 App 业务事件，
 * 以及对外暴露"刷新某控件"之类的稳定接口。App 业务层不直接操作 LVGL 控件，
 * 一律经由这一层，保证 UI 与业务解耦。
 *
 * 在 custom_init() 里调用一次。当前为骨架，按业务逐步填充。 */
void my_app_event_init(lv_ui *ui);

typedef enum {
    MY_APP_EVENT_HOME_BTN_2_CLICKED = 1,
} my_app_event_t;

typedef void (*my_app_event_cb_t)(my_app_event_t event, void *user_data);

void my_app_set_event_cb(my_app_event_cb_t cb, void *user_data);
void my_app_refresh_home_date(const char *date, const char *week);
void my_app_refresh_home_button_text(unsigned char index, const char *text);
void my_app_refresh_screen5_slider_value(unsigned char index, int value);

#ifdef __cplusplus
}
#endif

#endif /* MY_APP_H */
