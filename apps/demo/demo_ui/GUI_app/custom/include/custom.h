/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

/* GUI-Guider 生成的 setup_scr_*.c 会 #include "custom.h" 并在建屏末尾调用 custom_init()。
 * 这是 custom 层唯一对 generated 暴露的入口：禁止在这里聚合各模块头(如 custom_modules.h)，
 * 否则 generated 编译时会被迫去找 scr_guard.h 等，破坏分层。模块聚合只在 custom.c 里做。 */
void custom_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* __CUSTOM_H_ */
