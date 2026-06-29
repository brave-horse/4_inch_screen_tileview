#ifndef SCR_NOSCROLL_H
#define SCR_NOSCROLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

/* 指定屏禁滚：某些屏放了比屏幕大的整屏图(本工程主屏 ui_home_screen 的 720x720 大图就超出 480x800
 * 屏宽)，屏容器默认带 SCROLLABLE+ELASTIC，手指拖动会被"橡皮筋"接管 → 原地反复 invalidate
 * 重绘(画面几乎不动但 CPU 拉满)，同时吞掉 GESTURE 手势。
 *
 * 在 custom_init() 里调用一次，内部用轮询发现"活动屏切换"后，对目标屏及其子控件关掉滚动。
 * 注意：tabview 屏(除主屏外的各子屏)靠滑动切 tab，**不要**列入目标，否则会破坏翻页。 */
void scr_noscroll_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif

#endif /* SCR_NOSCROLL_H */
