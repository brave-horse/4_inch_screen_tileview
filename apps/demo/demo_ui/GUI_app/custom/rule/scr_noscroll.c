/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include "lvgl.h"
#include "scr_noscroll.h"
#include "gui_guider.h"

/*********************
 *      DEFINES
 *********************/

/* 轮询周期: 用来发现"当前活动屏切换了"并对新屏关一次滚动。
 * 只在切屏时才真正做事, 平时就是一次指针比较, 开销可忽略(同 scr_guard)。 */
#define SCR_NOSCROLL_POLL_PERIOD_MS  30

/* 1=连深层滚动区(卡片列表)的弹性/惯性也关(防不溢出容器原地弹性重绘);
 * 0=保留深层弹性 → 卡片滚动有橡皮筋回弹+惯性。
 * 早期为防"弹性重绘CPU拉满"设1, 但那卡死真因其实是图片缓存太小每帧重解码SD图(已调大
 * LV_IMG_CACHE_DEF_SIZE修复), 故改回 0 恢复橡皮筋。若回弹仍致卡再设回 1。 */
#define SCR_KILL_DEEP_ELASTIC  0

/**********************
 *  STATIC VARIABLES
 **********************/

/* 上次已处理过的活动屏。仅作指针相等比较, 从不解引用, 屏删除后变野也安全。 */
static lv_obj_t *s_last_scr;

/* 需要禁止整屏(上下)滚动的屏槽位。
 * - 主屏 ui_home_screen: 720x720 大图超出 480x800 屏, 屏容器可滚 + 橡皮筋, 原地重绘吞手势。
 * - 其余子屏(device_management/light_scence/curtain_scene/setting/light_CT_screen): tabview 屏。每个 tabview 只有 1 个 tab(无需左右切), 但屏/tabview 整体
 *   能上下滑, 会把 tabview 拖出屏外。列进来禁掉。
 * 注意: 只关"屏 + 屏的直接子(tabview 对象本身)", 不递归进 tab 内部, 所以 tab 里
 * list/slider 自身的滚动不受影响。 */
static lv_obj_t **const s_targets[] = {
    &guider_ui.ui_home_screen,
    &guider_ui.device_management_screen,
    &guider_ui.setting_screen,
    &guider_ui.light_CT_screen,
};
#define TARGET_CNT  (sizeof(s_targets) / sizeof(s_targets[0]))

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void scr_noscroll_poll_cb(lv_timer_t *timer);

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

void scr_noscroll_init(lv_ui *ui)
{
    LV_UNUSED(ui);
    lv_timer_create(scr_noscroll_poll_cb, SCR_NOSCROLL_POLL_PERIOD_MS, NULL);
}

/**********************
 *  STATIC FUNCTIONS
 **********************/

/* 关掉一个对象自身的滚动行为。
 * 只清 SCROLLABLE 不够: LVGL 默认还给对象加了 SCROLL_ELASTIC(橡皮筋), 内容即使不溢出,
 * 手指拖动也会被"弹性"接管成滚动 → 在原地反复 invalidate 重绘(画面几乎不动但 CPU 拉满),
 * 同时让 indev_gesture() 因 scroll_obj 非空而直接 return, 吞掉 GESTURE 手势。
 * 所以 ELASTIC / MOMENTUM 一并关掉。 */
static void obj_kill_scroll(lv_obj_t *obj)
{
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_MOMENTUM);
}

#if SCR_KILL_DEEP_ELASTIC
/* 递归只摘 ELASTIC+MOMENTUM、保留 SCROLLABLE: 让深层滚动区(tabview content→tab page,
 * 屏的曾孙级,单层循环够不到)还能拖动滚卡片, 但不再有"原地弹性重绘 CPU 拉满"和惯性甩动
 * 余震。list/slider 整棵跳过, 不动它们自身的滚动/拖动交互。 */
static void kill_elastic_deep(lv_obj_t *obj)
{
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    uint32_t c;
    for (c = 0; c < cnt; c++) {
        lv_obj_t *child = lv_obj_get_child(obj, c);
        if (lv_obj_check_type(child, &lv_list_class) ||
            lv_obj_check_type(child, &lv_slider_class)) {
            continue;
        }
        lv_obj_clear_flag(child, LV_OBJ_FLAG_SCROLL_ELASTIC);
        lv_obj_clear_flag(child, LV_OBJ_FLAG_SCROLL_MOMENTUM);
        kill_elastic_deep(child);
    }
}
#endif

static void scr_noscroll_poll_cb(lv_timer_t *timer)
{
    lv_obj_t *act = lv_scr_act();
    size_t i;

    LV_UNUSED(timer);

    if (act == NULL || act == s_last_scr) {
        return;
    }
    s_last_scr = act;

    /* 活动屏切换了: 若它是某个目标屏, 关掉滚动行为。
     * 关键: find_scroll_obj 是从"手指按住的对象"沿父链向上找可滚动祖先, 而屏上的
     * 全屏大图(lv_img)自己默认也可能带 SCROLLABLE+ELASTIC —— 只关屏不关图, 手指按在图上时
     * scroll_obj 仍命中图, 问题照旧。所以必须把屏**及其所有后代**(图/按钮)一起关掉。
     * 屏每次重建都是新对象, 靠"活动屏指针变化"重新命中。 */
    for (i = 0; i < TARGET_CNT; i++) {
        if (act == *s_targets[i]) {
            uint32_t cnt = lv_obj_get_child_cnt(act);
            uint32_t c;
            obj_kill_scroll(act);
            for (c = 0; c < cnt; c++) {
                lv_obj_t *child = lv_obj_get_child(act, c);
                /* list / slider 这类靠自身拖动交互的控件: 既不关滚动, 也不挂 GESTURE_BUBBLE。
                 * - list  : 直接建在屏上(setting_screen), 关了滚动就翻不动条目;
                 * - slider: 横向拖动就是调节(亮度/色温), 一旦冒泡会被当成左右切屏手势吞掉。 */
                if (lv_obj_check_type(child, &lv_list_class) ||
                    lv_obj_check_type(child, &lv_slider_class)) {
                    continue;
                }
                /* 其余(全屏大图 / 容器 / tabview / 按钮)挂 GESTURE_BUBBLE, 让切屏手势能冒泡到屏:
                 * LVGL 的 LV_EVENT_GESTURE 只发给"手指按住的对象", 全屏大图会把它吃掉, 屏收不到。
                 * 挂上后 indev 会沿父链上溯把手势交给屏(见 lv_indev.c: gesture_obj 仅当对象带
                 * GESTURE_BUBBLE 才向上走)。slider 在 tabview 内部(非屏直接子), 不受这里影响。 */
                lv_obj_add_flag(child, LV_OBJ_FLAG_GESTURE_BUBBLE);
                obj_kill_scroll(child);
            }
#if SCR_KILL_DEEP_ELASTIC
            /* 深层滚动区(如 tabview 内的卡片页)单独摘弹性/惯性, 保留可滚。 */
            kill_elastic_deep(act);
#endif
            break;
        }
    }
}
