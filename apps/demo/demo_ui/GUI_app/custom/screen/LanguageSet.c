#include "lvgl.h"
#include "gui_guider.h"
#include "LanguageSet.h"

#define LS_PRESS_BG  0x151414

static void clear_children_clickable(lv_obj_t *obj)
{
	uint32_t cnt = lv_obj_get_child_cnt(obj);
	for (uint32_t ci = 0; ci < cnt; ci++) {
		lv_obj_t *child = lv_obj_get_child(obj, ci);
		lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
		clear_children_clickable(child);
	}
}

void languageset_on_screen_load(void)
{
	lv_obj_t *conts[] = {
		guider_ui.LanguageSet_cont_3,
		guider_ui.LanguageSet_cont_4,
		guider_ui.LanguageSet_cont_5,
		guider_ui.LanguageSet_cont_6,
	};
	const uint8_t n = sizeof(conts) / sizeof(conts[0]);
	for (uint8_t i = 0; i < n; i++) {
		lv_obj_t *cont = conts[i];
		if (!lv_obj_is_valid(cont)) continue;
		clear_children_clickable(cont);
		lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(cont, lv_color_hex(LS_PRESS_BG), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_PRESSED);
	}
}


