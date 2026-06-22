#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "board_config.h"

#define CONFIG_DEBUG_ENABLE                                         //打印开关
#define CONFIG_MPU_DEBUG_ENABLE
#define CONFIG_RTOS_STACK_CHECK_ENABLE                              //是否启用定时检查任务栈
// #define CONFIG_MEM_LEAK_CHECK_ENABLE                             //是否启用内存泄漏检查(需要包含mem_leak_test.h头文件)
#define CONFIG_CXX_SUPPORT                                          //使能C++支持
#define CONFIG_LZ4_COMPRESS_APP_CODE_ENABLE                         //使用LZ4压缩代码
/* 原 USE_SD_PLAY_AVI_DEMO(开机全屏循环播 1.avi)已废弃: 它常驻后台按帧率解码
   JPEG+YUV->RGB 并把全屏 canvas 压在最前, 导致静止 CPU ~50% 且 UI 图片反复重绘闪烁。
   纯家居控制 UI 不需要该视频, avi_player.c 已删除。 */

//*********************************************************************************//
//                          预留区UI和AUDIO资源配置                                //
//*********************************************************************************//
//注意：ui和audio资源的起始地址和大小, 根据产品生命周期最大情况定义,根据实际需求进行配置
//FLASH后面4K用于一些配置存储，所以禁止覆盖
//具体说明和注意事项请阅读文档

//(1)ui和audio资源 ,如果存在ui资源则位于扩展预留区末尾,
//还存在audio则位于ui项前面，其他配置项则位于它们之前.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----CONFIG_UI_PACKRES_ADR - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_UI_PACKRES_LEN = CONFIG_UI_PACKRES_ADR
#  (CONFIG_UI_PACKRES_LEN)     |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

//(2)只有audio资源,则将其位于扩展预留区末尾.
/*
#------------------------------|
#  (其他预留区配置项)          |
#------------------------------|<----__FLASH_SIZE__ - 0x1000 - CONFIG_AUDIO_PACKRES_LEN = CONFIG_AUDIO_PACKRES_ADR
#  (CONFIG_AUDIO_PACKRES_LEN)  |
#------------------------------|<----__FLASH_SIZE__ - 0x1000
#  (4K Reserved)               |
#------------------------------+<----__FLASH_SIZE__
*/

#if defined CONFIG_UI_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
#define CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //UI资源打包后放在扩展预留区
#endif

#if defined CONFIG_AUDIO_ENABLE && !defined CONFIG_SDFILE_EXT_ENABLE
//#define CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE //AUDIO资源打包后放在扩展预留区
#endif

#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_UI_PACKRES_LEN 0x400000   //4M: 容纳720x720开机动画(VM区自动缩,仅需32K)
#define CONFIG_UI_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000)
#else
#define CONFIG_UI_PACKRES_LEN 0
#define CONFIG_UI_PACKRES_ADR 0
#endif

#if defined CONFIG_VOICE_PROMPT_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#if defined CONFIG_UI_FILE_SAVE_IN_RESERVED_EXPAND_ZONE
#define CONFIG_AUDIO_PACKRES_LEN 0x180000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - (CONFIG_UI_PACKRES_LEN) - 0x1000 - CONFIG_AUDIO_PACKRES_LEN)
#else
#define CONFIG_AUDIO_PACKRES_LEN 0x180000
#define CONFIG_AUDIO_PACKRES_ADR ((__FLASH_SIZE__) - CONFIG_AUDIO_PACKRES_LEN - 0x1000)
#endif
#else
#define CONFIG_AUDIO_PACKRES_LEN 0
#define CONFIG_AUDIO_PACKRES_ADR 0
#endif

//*********************************************************************************//
//                                  路径配置                                       //
//*********************************************************************************//
#define CONFIG_JLFAT_ENABLE

#if TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                         "storage/sd0"   //定义对应SD0的路径
#define SDX_DEV                                     "sd0"
#endif

#if TCFG_SD1_ENABLE && !TCFG_SD0_ENABLE
#define CONFIG_STORAGE_PATH                         "storage/sd1"   //定义对应SD1的路径
#define SDX_DEV                                     "sd1"
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH                         "storage/sdx"   //不使用SD定义对应别的路径，防止编译出错
#define SDX_DEV                                     "sdx"
#endif

#define CONFIG_ROOT_PATH                            CONFIG_STORAGE_PATH"/C/"    //定义对应SD文件系统的根目录路径

/* GUI Guider external image root, packed from cpu/wl83/tools/demo_ui_res. */
#define CONFIG_UI_FILE_PATH                         "s:/sdfile/EXT_RESERVED/uipackres/ui/"


//*********************************************************************************//
//                                UI DEMO配置                                      //
//*********************************************************************************//
#if TCFG_LCD_ENABLE
/* #define USE_LVGL_V9_UI_DEMO */ 

#define USE_LVGL_V8_UI_DEMO
#define LV_DISP_UI_FB_NUM 2//注意当修改为0时,需要设置lv_conf.h:LV_COLOR_DEPTH_EXTEN = LV_COLOR_DEPTH
#define FB_LCD_BUF_NUM    2

/* ───── UI性能调试日志总开关(唯一控制点) ─────
 * 1 = 串口每秒打印[perf]: 渲染帧率/耗时(lv_port_disp.c) + CPU占用/堆余量(custom.c),定位UI卡顿用。
 * 不需要时改0或直接注释本行 → 两处日志一起关。 */
#define PERF_LOG_EN  1

// #define USE_AWTK_UI_DEMO

// #define USE_ARM2D_UI_DEMO
#endif


#ifdef CONFIG_RELEASE_ENABLE
#define LIB_DEBUG    0
#else
#define LIB_DEBUG    1
#endif
#define CONFIG_DEBUG_LIB(x)         (x & LIB_DEBUG)

#endif
