/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include "lvgl.h"
#include "scr_guard.h"
#include "gui_guider.h"

/*********************
 *      DEFINES
 *********************/

/* 轮询周期：用来发现"当前活动屏换了"并给新屏补挂删除回调。
 * 只在切屏时才真正做事，平时就是一次指针比较，开销可忽略。 */
#define SCR_GUARD_POLL_PERIOD_MS  30

/**********************
 *  STATIC VARIABLES
 **********************/

/* 需要"删除即置 NULL"保护的全局屏指针槽位。
 * —— 原则：凡是 custom/ 里有代码会去读的屏，就把它的槽位地址列进来。
 * 本工程 6 个屏在 events_init.c 里互相 auto_del 切换，img/scr_noscroll 等又会读
 * guider_ui.screen*，所以这里把全部 6 个屏都列上，最稳。
 * 新增屏时在这里加一行 &guider_ui.screen_xxx 即可。 */
static lv_obj_t **const s_slots[] = {
    &guider_ui.ui_home_screen,
    &guider_ui.setting_screen,
    &guider_ui.light_CT_screen,
};
#define SLOT_CNT  (sizeof(s_slots) / sizeof(s_slots[0]))

/* 注：原先这里还守护 ui_home_screen_digital_clock_1(数字时钟有常驻 timer 会写野指针)，
 * 首页改版后该控件已删除、其 timer 也不存在，子控件守护机制随之移除。
 * 若以后再加"被 generated 常驻代码引用的子控件"，需恢复子控件守护表。 */

/* 已经挂过删除回调的当前活动屏。仅用作指针相等比较，从不解引用，野了也安全。 */
static lv_obj_t *s_guarded = NULL;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void scr_guard_del_cb(lv_event_t *e);
static void scr_guard_poll_cb(lv_timer_t *timer);

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

void scr_guard_init(void)
{
    lv_timer_create(scr_guard_poll_cb, SCR_GUARD_POLL_PERIOD_MS, NULL);
}

/**********************
 *  STATIC FUNCTIONS
 **********************/

/* 屏被 lv_obj_del 销毁前会收到 LV_EVENT_DELETE。此刻把所有指向它的槽位清成 NULL，
 * 是在"对象还活着、地址尚未被复用"的时间点完成的，因此能彻底切断后续的地址别名。 */
static void scr_guard_del_cb(lv_event_t *e)
{
    lv_obj_t *dying = lv_event_get_target(e);
    size_t i;

    for (i = 0; i < SLOT_CNT; i++) {
        if (*s_slots[i] == dying) {
            *s_slots[i] = NULL;
        }
    }

    /* 允许新屏（哪怕复用了同一地址）重新被识别为“未挂过回调”。 */
    if (dying == s_guarded) {
        s_guarded = NULL;
    }
}

/* 给每个新成为当前活动屏的屏挂上删除回调。
 * 关键：注册对象取自 lv_scr_act()，绝不会是野指针；而“成为活动屏/刚建好”
 * 必然早于“被切走删除”，所以删除回调一定在对象被删前就位。 */
static void scr_guard_poll_cb(lv_timer_t *timer)
{
    lv_obj_t *act = lv_scr_act();

    LV_UNUSED(timer);

    if (act == NULL) {
        return;
    }

    if (act == s_guarded) {
        return;
    }

    lv_obj_add_event_cb(act, scr_guard_del_cb, LV_EVENT_DELETE, NULL);
    s_guarded = act;
}
