#include "lvgl.h"
#include "gui_guider.h"
#include "Home.h"

/* GUI-Guider 给每个 lv_img 默认塞 CLICKABLE, 会吃掉首页整屏左滑手势(进设备管理).
 * 首页每次被 auto_del 重建都会重新加上, 故在 Screen Loaded 里每次清一遍. */
/* btn_1/2/3 按下/松开 → bg_opa 128/255 */
static void btn_pressed_cb(lv_event_t *e)
{
    lv_obj_set_style_bg_opa(lv_event_get_target(e), 128, LV_PART_MAIN | LV_STATE_DEFAULT);
}
static void btn_released_cb(lv_event_t *e)
{
    lv_obj_set_style_bg_opa(lv_event_get_target(e), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void home_on_screen_load(void)
{
    /* auto_del 切屏时对象可能已被删, 先判有效防野指针 */
    #define SAFE_CLEAR(obj, flag) if (lv_obj_is_valid(guider_ui.obj)) lv_obj_clear_flag(guider_ui.obj, flag)

    SAFE_CLEAR(ui_home_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_6, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_MainSetImg, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *btns[] = { guider_ui.ui_home_screen_btn_1,
                         guider_ui.ui_home_screen_btn_2,
                         guider_ui.ui_home_screen_btn_3 };
    for (uint8_t i = 0; i < 3; i++) {
        if (!lv_obj_is_valid(btns[i])) continue;
        lv_obj_add_event_cb(btns[i], btn_pressed_cb,  LV_EVENT_PRESSED,  NULL);
        lv_obj_add_event_cb(btns[i], btn_released_cb, LV_EVENT_RELEASED, NULL);
    }
}

/* 下拉面板 4 个图标按钮逻辑已全部移到 pulldown.c(捕获真身指针, 不受主屏重建影响)。
 * 这两个空桩仅兼容当前 events_init.c 的引用; GUI-Guider 里 btn_4/btn_6 事件请留空,
 * 重导出后本桩即可删除。pulldown_init 已在运行时清掉这些按钮的 GUI-Guider 绑定。 */
void home_btn_4_clicked(lv_event_t *e) { LV_UNUSED(e); }
void home_btn_6_clicked(lv_event_t *e) { LV_UNUSED(e); }
