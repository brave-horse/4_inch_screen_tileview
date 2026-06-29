#include "i18n_storage.h"

/* 平台相关: 语言断电持久化。当前为静态桩(掉电丢失);
 * 阶段4 换成杰理 VM/syscfg 真存储。移植换芯片只改本文件。 */

static uint8_t s_saved_lang = 1;   // saved language: 0=中文 1=英文; 临时=1验证机制, 验证后改回 0

void i18n_storage_save_lang(uint8_t lang)
{
    s_saved_lang = lang;
}

uint8_t i18n_storage_load_lang(void)
{
    return s_saved_lang;
}
