#include "lvgl.h"
#include "gui_guider.h"
#include "Setting.h"

#define SETTING_PRESS_BG  0x151414

static void clear_children_clickable(lv_obj_t *obj)
{
	uint32_t cnt = lv_obj_get_child_cnt(obj);
	for (uint32_t ci = 0; ci < cnt; ci++) {
		lv_obj_t *child = lv_obj_get_child(obj, ci);
		lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
		clear_children_clickable(child);
	}
}

void setting_on_screen_load(void)
{
	lv_obj_set_scroll_dir(guider_ui.setting_screen_tabview_1, LV_DIR_VER);
	lv_obj_set_scroll_dir(guider_ui.setting_screen_tabview_1_tab_1, LV_DIR_VER);	/* 禁 tab 内容横滚 */

	lv_obj_t *conts[] = {
		guider_ui.setting_screen_cont_3,  guider_ui.setting_screen_cont_4,
		guider_ui.setting_screen_cont_5,  guider_ui.setting_screen_cont_6,
		guider_ui.setting_screen_cont_7,  guider_ui.setting_screen_cont_8,
		guider_ui.setting_screen_cont_9,  guider_ui.setting_screen_cont_10,
		guider_ui.setting_screen_cont_14, guider_ui.setting_screen_cont_15,
	};
	const uint8_t n = sizeof(conts) / sizeof(conts[0]);
	for (uint8_t i = 0; i < n; i++) {
		lv_obj_t *cont = conts[i];
		if (!lv_obj_is_valid(cont)) continue;
		clear_children_clickable(cont);
		lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(cont, lv_color_hex(SETTING_PRESS_BG), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_PRESSED);
	}
}
