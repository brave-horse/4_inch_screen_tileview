#include "i18n.h"
#include "lv_i18n.h"
#include "i18n_storage.h"

/* 方案: GUI-Guider 中文当 key。setup 永远先设中文, 进屏后按中文查表换当前语言。
 * 用全局 timer 检测屏幕切换自动 apply, 不依赖各屏 on_screen_load。 */

static i18n_lang_t s_cur_lang  = I18N_ZH;   // current language
static lv_obj_t   *s_last_scr;              // 上次 apply 的屏, 用于检测切换

static const char *locale_of(i18n_lang_t lang)
{
    return lang == I18N_EN ? "en" : "zh";
}

/* 递归: 对每个 label 用其中文查表, 查到才换(查不到 lv_i18n 返回原 key) */
static void apply_obj(lv_obj_t *obj)
{
    if (lv_obj_check_type(obj, &lv_label_class)) {
        const char *zh = lv_label_get_text(obj);
        const char *tr = lv_i18n_get_text(zh);
        if (tr != zh) lv_label_set_text(obj, tr);
    }
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t ci = 0; ci < cnt; ci++)   /* ci child index */
        apply_obj(lv_obj_get_child(obj, ci));
}

void i18n_apply_screen(lv_obj_t *scr)
{
    if (s_cur_lang == I18N_ZH) return;   // 中文即 setup 原文, 不动
    if (!lv_obj_is_valid(scr)) return;
    apply_obj(scr);
}

/* 周期检测当前屏, 切换屏时自动 apply。首次触发时也 apply(可能已过 SCREEN_LOADED)。 */
static void find_first_label(lv_obj_t *obj, lv_obj_t **found)
{
    if (*found) return;
    if (lv_obj_check_type(obj, &lv_label_class)) {
        const char *t = lv_label_get_text(obj);
        if (t && t[0] != '\0') { *found = obj; return; }
    }
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t ci = 0; ci < cnt && !*found; ci++)
        find_first_label(lv_obj_get_child(obj, ci), found);
}
static void tick_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    lv_obj_t *scr = lv_scr_act();
    if (scr == s_last_scr) return;
    s_last_scr = scr;

    /* 诊断: 显示第一个有文字 label 的原文 */
    lv_obj_t *first = NULL;
    find_first_label(scr, &first);
    lv_obj_t *diag = lv_label_create(lv_layer_top());
    if (first) {
        const char *zh = lv_label_get_text(first);
        const char *tr = lv_i18n_get_text(zh);
        if (tr == zh) {
            lv_label_set_text(diag, "I18N: SAME (no trans)");
        } else {
            lv_label_set_text(diag, tr);  /* 显示查到的译文 */
        }
    } else {
        lv_label_set_text(diag, "I18N: no label found");
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
    lv_i18n_set_locale(locale_of(s_cur_lang));
    s_last_scr = NULL;                         // 强制首次 tick 立即 apply
    lv_timer_create(tick_cb, 150, NULL);       // 切屏后约 150ms 自动换语言
}

i18n_lang_t i18n_get_lang(void)
{
    return s_cur_lang;
}

void i18n_set_lang(i18n_lang_t lang)
{
    s_cur_lang = lang;
    lv_i18n_set_locale(locale_of(lang));
    i18n_storage_save_lang((uint8_t)lang);
    s_last_scr = NULL;   // 强制下个 tick 重 apply 当前屏
    /* 切回中文因 label 已是英文无法直接回, 阶段4 改用"重载当前屏"解决。 */
    lv_obj_t *scr = lv_scr_act();
    if (lv_obj_is_valid(scr)) i18n_apply_screen(scr);
}
