#include "i18n.h"
#include "lv_i18n.h"

static i18n_lang_t s_cur_lang = I18N_ZH;
static lv_obj_t   *s_last_scr;

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

static void tick_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    lv_obj_t *scr = lv_scr_act();
    if (scr == s_last_scr) return;
    s_last_scr = scr;
    i18n_apply_screen(scr);
}

void i18n_init(void)
{
    lv_i18n_init(lv_i18n_language_pack);
    /* TODO: read saved lang from storage. Default zh for now. */
    lv_i18n_set_locale("zh-CN");
    s_last_scr = NULL;
    lv_timer_create(tick_cb, 150, NULL);
}

void i18n_set_lang(i18n_lang_t lang)
{
    s_cur_lang = lang;
    lv_i18n_set_locale(lang == I18N_EN ? "en-GB" : "zh-CN");
    /* TODO: save lang to storage */
    s_last_scr = NULL;
    lv_obj_t *scr = lv_scr_act();
    if (lv_obj_is_valid(scr)) i18n_apply_screen(scr);
}

i18n_lang_t i18n_get_lang(void) { return s_cur_lang; }
