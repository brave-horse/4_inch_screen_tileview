#ifndef SETTING_H
#define SETTING_H

#ifdef __cplusplus
extern "C" {
#endif

/* 设置主屏加载: 把右箭头 img_2~8 并入对应 list item, 跟 list 滑动(否则独立定位不滑)。
 * GUI-Guider 在 setting_screen 的 Screen Loaded 事件里调用(custom code)。 */
void setting_on_screen_load(void);

#ifdef __cplusplus
}
#endif

#endif
