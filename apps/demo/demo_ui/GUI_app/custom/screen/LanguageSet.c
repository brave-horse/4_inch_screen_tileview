#include "lvgl.h"
#include "gui_guider.h"
#include "LanguageSet.h"
#include "i18n.h"

#define LS_PRESS_BG  0x151414   /* 语言栏按下底色 */
#define POPUP_X      96         /* 确认弹窗显示位置(528 宽居中) */
#define POPUP_Y      260        /* 200 高居中 */

typedef struct {
	lv_obj_t *cont;   /* 语言栏容器 */
	lv_obj_t *mark;   /* 栏内选中标记图片 */
} LangRow;

static LangRow s_rows[2];       /* [0]=中文 cont_3, [1]=English cont_4 */
static uint8_t s_current;       /* 当前已确认语言 0=中文 1=英文(跨进屏保留) */
static uint8_t s_pending;       /* 待确认语言 */

/* 递归清子孙 CLICKABLE, 让点击落到容器本身 */
static void clear_children_clickable(lv_obj_t *obj)
{
	uint32_t cnt = lv_obj_get_child_cnt(obj);
	for (uint32_t ci = 0; ci < cnt; ci++) {
		lv_obj_t *child = lv_obj_get_child(obj, ci);
		lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
		clear_children_clickable(child);
	}
}

/* 找容器内第一张图片(选中标记) */
static lv_obj_t *find_mark_img(lv_obj_t *cont)
{
	uint32_t cnt = lv_obj_get_child_cnt(cont);
	for (uint32_t i = 0; i < cnt; i++) {
		lv_obj_t *child = lv_obj_get_child(cont, i);
		if (lv_obj_check_type(child, &lv_img_class)) return child;
	}
	return NULL;
}

/* 只显示 sel 栏的标记图片, 其余隐藏 */
static void refresh_mark(uint8_t sel)
{
	for (uint8_t i = 0; i < 2; i++) {
		if (!lv_obj_is_valid(s_rows[i].mark)) continue;
		if (i == sel) lv_obj_clear_flag(s_rows[i].mark, LV_OBJ_FLAG_HIDDEN);
		else          lv_obj_add_flag(s_rows[i].mark, LV_OBJ_FLAG_HIDDEN);
	}
}

/* 显示确认弹窗(直接显示, 无动画) */
static void popup_show(bool chinese)
{
	lv_label_set_text_fmt(guider_ui.LanguageSet_label_17,
	                      "是否将语言更改为:%s", chinese ? "中文(简体)" : "English");
	lv_obj_set_pos(guider_ui.LanguageSet_cont_5, POPUP_X, POPUP_Y);
	lv_obj_clear_flag(guider_ui.LanguageSet_cont_5, LV_OBJ_FLAG_HIDDEN);
	lv_obj_move_foreground(guider_ui.LanguageSet_cont_5);
}

static void popup_hide(void)
{
	lv_obj_add_flag(guider_ui.LanguageSet_cont_5, LV_OBJ_FLAG_HIDDEN);
}

/* 点语言栏: 先把标记移到本栏, 再弹确认框 */
static void on_row_click(lv_event_t *e)
{
	uint8_t idx = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
	s_pending = idx;
	refresh_mark(idx);          /* 立即把图片切到点击栏 */
	popup_show(idx == 0);       /* 0=中文 */
}

/* 取消: 标记恢复到当前已确认语言 + 收起 */
static void on_cancel(lv_event_t *e)
{
	LV_UNUSED(e);
	refresh_mark(s_current);
	popup_hide();
}

/* 确定: 全局切换语言 + 收起(标记保持在 pending 栏) */
static void on_ok(lv_event_t *e)
{
	LV_UNUSED(e);
	s_current = s_pending;
	i18n_set_lang(s_pending == 0 ? I18N_ZH : I18N_EN);
	popup_hide();
}

void languageset_on_screen_load(void)
{
	popup_hide();   /* 弹窗默认隐藏 */

	s_rows[0].cont = guider_ui.LanguageSet_cont_3;
	s_rows[1].cont = guider_ui.LanguageSet_cont_4;

	for (uint8_t i = 0; i < 2; i++) {
		lv_obj_t *cont = s_rows[i].cont;
		if (!lv_obj_is_valid(cont)) { s_rows[i].mark = NULL; continue; }
		s_rows[i].mark = find_mark_img(cont);
		clear_children_clickable(cont);
		lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(cont, lv_color_hex(LS_PRESS_BG), LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_PRESSED);
		lv_obj_add_event_cb(cont, on_row_click, LV_EVENT_CLICKED, (void *)(uintptr_t)i);
	}

	refresh_mark(s_current);   /* 进屏: 只亮当前语言的标记 */

	if (lv_obj_is_valid(guider_ui.LanguageSet_ok_btn))
		lv_obj_add_event_cb(guider_ui.LanguageSet_ok_btn, on_ok, LV_EVENT_CLICKED, NULL);
	if (lv_obj_is_valid(guider_ui.LanguageSet_cancel_btn))
		lv_obj_add_event_cb(guider_ui.LanguageSet_cancel_btn, on_cancel, LV_EVENT_CLICKED, NULL);
}
