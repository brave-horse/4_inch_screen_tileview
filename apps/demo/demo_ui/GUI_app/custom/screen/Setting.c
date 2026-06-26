#include "lvgl.h"
#include "gui_guider.h"
#include "Setting.h"

/* 设置项容器按下时的底色——后续换色改这一个宏即可 */
#define SETTING_PRESS_BG  0x151414

/* 递归清掉容器内所有子孙的 CLICKABLE, 让点击穿透到容器本身(触发跳转事件) */
static void clear_children_clickable(lv_obj_t *obj)
{
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t ci = 0; ci < cnt; ci++) {        /* ci child index */
        lv_obj_t *child = lv_obj_get_child(obj, ci);
        lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
        clear_children_clickable(child);
    }
}

void setting_on_screen_load(void)
{
    lv_obj_t *conts[7] = {
        guider_ui.setting_screen_cont_3, guider_ui.setting_screen_cont_4,
        guider_ui.setting_screen_cont_5, guider_ui.setting_screen_cont_6,
        guider_ui.setting_screen_cont_7, guider_ui.setting_screen_cont_8,
        guider_ui.setting_screen_cont_9,
    };
    for (uint8_t idx = 0; idx < 7; idx++) {        /* idx index */
        lv_obj_t *cont = conts[idx];
        if (!lv_obj_is_valid(cont)) continue;
        /* ① 容器内图片/文字的 CLICKABLE 清掉, 点击才落到容器、触发跳转 */
        clear_children_clickable(cont);
        /* ② 容器按下时底色变 SETTING_PRESS_BG(松手/切屏自动恢复) */
        lv_obj_set_style_bg_color(cont, lv_color_hex(SETTING_PRESS_BG), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}
