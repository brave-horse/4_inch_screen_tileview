#ifndef _I18N_TRANSMIT_H
#define _I18N_TRANSMIT_H
#include "lvgl.h"

typedef enum { I18N_ZH = 0, I18N_EN = 1 } i18n_lang_t;

void        i18n_init(void);
void        i18n_apply_screen(lv_obj_t *scr);
void        i18n_set_lang(i18n_lang_t lang);
i18n_lang_t i18n_get_lang(void);
#endif
