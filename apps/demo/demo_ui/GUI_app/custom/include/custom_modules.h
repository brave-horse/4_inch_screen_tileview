#ifndef CUSTOM_MODULES_H
#define CUSTOM_MODULES_H

#ifdef __cplusplus
extern "C" {
#endif

/* custom 层各模块的聚合头，仅供 custom.c 使用，不要被 generated 引用。
 * 新增模块时在这里加一行对应的头文件即可。 */
#include "scr_guard.h"    /* rule/   : 屏指针守卫(防野指针) */
#include "scr_noscroll.h" /* rule/   : 指定屏禁滚(防原地重绘/吞手势) */
#include "light_CT_screen.h"       /* screen/ : light_CT_screen 色温灯控件 */
#include "pulldown.h"     /* widget/ : 主屏顶部下拉面板(单面板) */

#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_MODULES_H */
