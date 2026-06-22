/*
 * 兼容垫片：把 #include "lvgl/lvgl.h" 转向真正的 lvgl.h
 *
 * 背景：GUI Guider 默认生成的 .c 文件使用 #include "lvgl/lvgl.h"
 *       （上游 LVGL 标准写法，假设项目里 lvgl 是一个目录）。
 *       本工程把 LVGL 放在 apps/common/lvgl_v8/，所以缺少 lvgl/ 子目录。
 *       本文件即"lvgl/lvgl.h"，转发到上一级真正的 lvgl.h，
 *       使两种写法都能用：
 *           #include "lvgl.h"        // 短写法
 *           #include "lvgl/lvgl.h"   // GUI Guider 默认写法
 *
 * 注意：lvgl.h 内部的 #include "src/..." 是相对它所在目录解析的，
 *       绕这层垫片不会破坏它的内部 include。
 */
#include "../lvgl.h"
