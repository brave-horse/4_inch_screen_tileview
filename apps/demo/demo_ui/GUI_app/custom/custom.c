/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "custom_modules.h"

#ifndef LV_USE_GUIDER_SIMULATOR
#include "app_config.h"      /* PERF_LOG_EN / CPU_CORE_NUM */
#include "os/os_api.h"       /* os_cpu_usage */
#include "system/malloc.h"   /* get_malloc_remain_heap_size / xPortGetMinimumEverFreeHeapSize */
#endif

#ifndef PERF_LOG_EN
#define PERF_LOG_EN 0        /* fallback: 模拟器或总开关注释掉时默认关 */
#endif

/*********************
 *      DEFINES
 *********************/
#define EN_SCR_GUARD     1   /* 屏指针守卫,防野指针 */
#define EN_SCR_NOSCROLL  1   /* 主屏禁滚 */

#if PERF_LOG_EN && !defined(LV_USE_GUIDER_SIMULATOR)
/* 待机CPU排查: 逐个任务名查占用,找出谁在空转。定位完可整段删回原样。 */
static const char *const perf_task_names[] = {
    "video_engine_server", //视频/显示引擎(待机大头嫌疑)
    "fb_combine_task0",    //帧缓冲合成
    "lvgl_v8_main_task",   //LVGL主任务(渲染+事件)
    "tp_task",             //触摸面板任务
    "app_core",            //系统事件核心
    "sys_event",           //系统事件
    "systimer",            //系统硬定时器
    "sys_timer",           //软定时器
    "The_onlytask",        //色温灯任务(已加延时)
};

static void perf_mon_cb(lv_timer_t *timer)
{
    int core_usage[CPU_CORE_NUM] = {0};
    os_cpu_usage(NULL, core_usage);
    int total_usage = 0;
    for (int core = 0; core < CPU_CORE_NUM; core++) {
        total_usage += core_usage[core];
    }
    printf("[perf] cpu_avg=%d%% c0=%d%% c1=%d%% heap=%d min_heap=%d\n",
           total_usage / CPU_CORE_NUM, core_usage[0], core_usage[CPU_CORE_NUM - 1],
           get_malloc_remain_heap_size(), (int)xPortGetMinimumEverFreeHeapSize());

    static int dumped_once = 0;   //dumped_once: 首次tick打印完整任务表,抓漏网任务
    if (!dumped_once) {
        dumped_once = 1;
        os_dump_user_tcb_info();
    }

    int task_count = sizeof(perf_task_names) / sizeof(perf_task_names[0]);
    for (int idx = 0; idx < task_count; idx++) {
        int task_core[CPU_CORE_NUM] = {0};
        int used = os_cpu_usage(perf_task_names[idx], task_core);   //used: 该任务CPU占用%
        printf("[perf]   %-18s = %d%%\n", perf_task_names[idx], used);
    }
}
#endif

void custom_init(lv_ui *ui)
{
    printf("[custom] init: guard=%d noscroll=%d perf=%d\n",
           EN_SCR_GUARD, EN_SCR_NOSCROLL, PERF_LOG_EN);

#ifndef LV_USE_GUIDER_SIMULATOR
    /* 挂起空转占满一个核的 ADAS 视觉引擎(video_engine.a 的 initcall 自启,本UI工程用不到)。
       要恢复就 os_task_resume("video_engine_server")。根治改用 Makefile 去掉 video_engine.a。 */
    os_task_suspend("video_engine_server");
#endif

#if EN_SCR_GUARD
    scr_guard_init();
#endif

#if EN_SCR_NOSCROLL
    scr_noscroll_init(ui);
#endif

    pulldown_init(ui);

#if PERF_LOG_EN && !defined(LV_USE_GUIDER_SIMULATOR)
    lv_timer_create(perf_mon_cb, 1000, NULL);
#endif
}

#ifdef LV_USE_GUIDER_SIMULATOR
#include "hw_cloud_task.h"
void hw_cloud_post(HW_Msg *msg)
{
    (void)msg;
    printf("[sim] hw_cloud_post type=%u\n", msg ? msg->type : 0);
}
#endif
