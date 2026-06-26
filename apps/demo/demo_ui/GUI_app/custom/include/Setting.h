#ifndef SETTING_H
#define SETTING_H

#ifdef __cplusplus
extern "C" {
#endif

/* 设置主屏加载。原"箭头跟 list 滑动"逻辑已废弃(list 改成 cont 容器, 箭头随容器自带跟随),
 * 此函数现留空; 如需设置屏初始化逻辑可在此补充。GUI-Guider Screen Loaded 仍可调它(空函数无害)。 */
void setting_on_screen_load(void);

#ifdef __cplusplus
}
#endif

#endif
