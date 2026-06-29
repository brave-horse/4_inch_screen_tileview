#ifndef PULLDOWN_H
#define PULLDOWN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

/* 安卓式顶部下拉面板(单面板版)。
 * 用 GUI-Guider 在主屏画好的 screen_cont_1 作为下拉页:
 * 开机挂到 lv_layer_top 并藏在屏幕上方; 从屏顶下滑露出, 松手按露出比例展开/收起。
 *
 * 在 custom_init() 里调用一次即可(内部建一个 20ms 定时器全局扫触摸, 面板在 layer_top
 * 上任何屏都能下拉)。若 GUI-Guider 里没画 screen_cont_1, 则不启用(空操作)。 */
void pulldown_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif

#endif /* PULLDOWN_H */
