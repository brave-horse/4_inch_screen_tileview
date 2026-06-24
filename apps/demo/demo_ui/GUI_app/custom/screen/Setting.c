#include "lvgl.h"
#include "gui_guider.h"
#include "Setting.h"

/* 设置主屏: 7 个右箭头(img_2~8)是 setting_screen 的独立子, list_1 滑动时
 * 栏(list item)滑、箭头不滑 → 错位。
 * 策略: 箭头不放进 list(避免 item 的 flex 布局副作用), 留在原 parent;
 *       监听 list 滚动, 手动把箭头按对应栏的位移一起上下移; 滚出 list 可视区就隐藏。
 * 箭头的 x 和初始 y 完全用 GUI-Guider 里设的, custom 不写死。 */

#define ARROW_CNT  7

static lv_obj_t *s_list;
static lv_obj_t *s_arrows[ARROW_CNT];
static lv_coord_t s_arrow_y0[ARROW_CNT];        /* 箭头初始 y(GUI-Guider 设的) */
static lv_coord_t s_view_top, s_view_bottom;    /* list 可视区上下界(绝对 y) */

/* list 滚动: 箭头跟对应栏一起移, 滚出可视区隐藏 */
static void list_scroll_cb(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_coord_t scroll = lv_obj_get_scroll_y(s_list);
    for (uint8_t idx = 0; idx < ARROW_CNT; idx++) {     /* idx index */
        if (!lv_obj_is_valid(s_arrows[idx])) continue;
        lv_coord_t pos_y = s_arrow_y0[idx] - scroll;    /* 跟栏一起滚 */
        lv_obj_set_y(s_arrows[idx], pos_y);
        lv_coord_t mid = pos_y + lv_obj_get_height(s_arrows[idx]) / 2;
        if (mid < s_view_top || mid > s_view_bottom)
            lv_obj_add_flag(s_arrows[idx], LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_clear_flag(s_arrows[idx], LV_OBJ_FLAG_HIDDEN);
    }
}

void setting_on_screen_load(void)
{
    s_list = guider_ui.setting_screen_list_1;

    /* 箭头按 y 对应栏: 网络→img_2 显示→img_5 开关→img_3 传感器→img_4
     * 重启→img_7 恢复→img_6 关于→img_8 */
    lv_obj_t *arrows[ARROW_CNT] = {
        guider_ui.setting_screen_img_2, guider_ui.setting_screen_img_5,
        guider_ui.setting_screen_img_3, guider_ui.setting_screen_img_4,
        guider_ui.setting_screen_img_7, guider_ui.setting_screen_img_6,
        guider_ui.setting_screen_img_8,
    };

    lv_obj_update_layout(guider_ui.setting_screen);     /* 先布局, 取准坐标 */

    /* list 可视区(绝对 y), 用来裁剪滚出去的箭头 */
    lv_area_t list_co;
    lv_obj_get_coords(s_list, &list_co);
    s_view_top = list_co.y1;
    s_view_bottom = list_co.y2;

    for (uint8_t idx = 0; idx < ARROW_CNT; idx++) {
        s_arrows[idx] = arrows[idx];
        if (lv_obj_is_valid(arrows[idx]))
            s_arrow_y0[idx] = lv_obj_get_y(arrows[idx]);    /* 记录 GUI-Guider 设的初始 y */
    }

    lv_obj_add_event_cb(s_list, list_scroll_cb, LV_EVENT_SCROLL, NULL);
    list_scroll_cb(NULL);    /* 初始对齐一次 */
}
