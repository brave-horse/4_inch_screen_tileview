/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

/*
 * lv_conf_ext.h for custom lvconf file.
 * Created on: Feb 8, 2023
 * example :
 *	#undef LV_FONT_FMT_TXT_LARGE
 *  #define LV_FONT_FMT_TXT_LARGE 1
 */

#ifndef LV_CONF_EXT_H
#define LV_CONF_EXT_H


/* common code  begin  */

/* 重绘区域可视化诊断：开启后每重绘一个对象就盖一层半透明随机色块+边框，
 * 用于排查"哪里在持续触发重绘"(拖滑块时灯光图区域狂闪 = 重绘太频繁)。
 * 当前=1 开启中。**调试用，问题查清后改回 0**(否则正常使用时满屏闪色块)。 */
// #undef LV_USE_REFR_DEBUG 1
// #define LV_USE_REFR_DEBUG 

/* common code end */


#if LV_USE_GUIDER_SIMULATOR
/* code for simulator begin  */

/* 性能监视器：模拟器右下角显示 FPS + CPU 占用%(LVGL 自估的渲染耗时占比, 用来查卡顿/掉帧)。
 * 放在 simulator 块 → 只在模拟器开, 不影响板子; 写在本文件(custom/, 不被 GUI Guider 覆盖),
 * 所以每次重生成代码 lv_conf.h 被重置也仍生效。
 * 注: lv_conf.h 里 LV_USE_PERF_MONITOR=0 时不会定义 _POS, 这里开启后必须补定义 _POS。 */
#undef  LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR     1
#undef  LV_USE_PERF_MONITOR_POS
#define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

/* 内存监视器：左下角显示已用内存/碎片率。开启时必须同时定义 _POS(同 PERF 的原因,
 * 否则 LV_USE_MEM_MONITOR=1 但 _POS 未定义 → 编译报错)。不需要就把这四行整体注释掉。 */
#undef  LV_USE_MEM_MONITOR
#define LV_USE_MEM_MONITOR      1
#undef  LV_USE_MEM_MONITOR_POS
#define LV_USE_MEM_MONITOR_POS  LV_ALIGN_BOTTOM_LEFT

/* code for simulator end */
#else
/* code for board begin */


/* code for board end */
#endif



#endif  /* LV_CONF_EXT_H */
