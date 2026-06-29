#ifndef I18N_STORAGE_H
#define I18N_STORAGE_H

#include <stdint.h>

/* 语言持久化接口(平台无关声明)。实现在 i18n_storage.c, 移植换芯片只改实现。 */
void    i18n_storage_save_lang(uint8_t lang);   // lang: 0=中文 1=英文
uint8_t i18n_storage_load_lang(void);

#endif
