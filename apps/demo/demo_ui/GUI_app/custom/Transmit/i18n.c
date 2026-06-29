#include "i18n.h"
#include "lv_i18n.h"

static i18n_lang_t s_cur_lang = I18N_ZH;
static lv_obj_t   *s_last_scr;

/* 简易存储桩: 变量持久化(阶段4 换 VM) */

static uint8_t s_saved_lang = 1;   /* saved language; 临时=EN验证机制, 验证后改0(ZH) */

void i18n_storage_save_lang(uint8_t lang) { s_saved_lang = lang; }
uint8_t i18n_storage_load_lang(void)       { return s_saved_lang; }

/* 递归遍历 label, 按中文原文查 lv_i18n 翻译表替换 */

static void apply_obj(lv_obj_t *obj)
{
    if (lv_obj_check_type(obj, &lv_label_class)) {
        const char *zh = lv_label_get_text(obj);
        const char *tr = lv_i18n_get_text(zh);
        if (tr != zh) lv_label_set_text(obj, tr);
    }
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t ci = 0; ci < cnt; ci++)
        apply_obj(lv_obj_get_child(obj, ci));
}

void i18n_apply_screen(lv_obj_t *scr)
{
    if (s_cur_lang == I18N_ZH) return;
    if (!lv_obj_is_valid(scr)) return;
    apply_obj(scr);
}

/* 全局 timer: 检测切屏→apply(含诊断, 定位后删除) */

static lv_obj_t *find_first_text_label(lv_obj_t *obj)
{
    if (lv_obj_check_type(obj, &lv_label_class)) {
        const char *t = lv_label_get_text(obj);
        if (t && t[0]) return obj;
    }
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t ci = 0; ci < cnt; ci++) {
        lv_obj_t *r = find_first_text_label(lv_obj_get_child(obj, ci));
        if (r) return r;
    }
    return NULL;
}

static void tick_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    lv_obj_t *scr = lv_scr_act();
    if (scr == s_last_scr) return;
    s_last_scr = scr;

    /* 诊断: 找到第一个有文字 label, 显示查表结果 */
    lv_obj_t *lbl = find_first_text_label(scr);
    lv_obj_t *diag = lv_label_create(lv_layer_top());
    if (lbl) {
        const char *zh = lv_label_get_text(lbl);
        const char *tr = lv_i18n_get_text(zh);
        if (tr != zh) {
            lv_label_set_text(diag, tr);   /* 查到了→显示译文证明机制通 */
        } else {
            lv_label_set_text(diag, "NO-TRANS");  /* 没查到 */
        }
    } else {
        lv_label_set_text(diag, "NO-LABEL");
    }
    lv_obj_set_style_text_color(diag, lv_color_hex(0xff0000), 0);
    lv_obj_set_style_bg_color(diag, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_opa(diag, LV_OPA_COVER, 0);
    lv_obj_align(diag, LV_ALIGN_TOP_MID, 0, 5);

    i18n_apply_screen(scr);
}

void i18n_init(void)
{
    lv_i18n_init(lv_i18n_language_pack);
    s_cur_lang = (i18n_lang_t)i18n_storage_load_lang();
    lv_i18n_set_locale(s_cur_lang == I18N_EN ? "en-GB" : "zh-CN");
    s_last_scr = NULL;
    lv_timer_create(tick_cb, 150, NULL);
}

void i18n_set_lang(i18n_lang_t lang)
{
    s_cur_lang = lang;
    lv_i18n_set_locale(lang == I18N_EN ? "en-GB" : "zh-CN");
    i18n_storage_save_lang((uint8_t)lang);
    s_last_scr = NULL;
    lv_obj_t *scr = lv_scr_act();
    if (lv_obj_is_valid(scr)) i18n_apply_screen(scr);
}

i18n_lang_t i18n_get_lang(void) { return s_cur_lang; }
