#ifndef I18N_H
#define I18N_H

#include "lvgl.h"

typedef enum { I18N_ZH = 0, I18N_EN = 1 } i18n_lang_t;

void        i18n_init(void);                  // 开机: lv_i18n_init + 读存储 + set_locale
void        i18n_apply_screen(lv_obj_t *scr); // 遍历 scr 所有 label, 按中文查表换当前语言
void        i18n_set_lang(i18n_lang_t lang);  // 切换 + 存储 + 刷新当前屏
i18n_lang_t i18n_get_lang(void);

#endif
