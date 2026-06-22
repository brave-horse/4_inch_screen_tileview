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
}
#endif

void custom_init(lv_ui *ui)
{
    printf("[custom] init: guard=%d noscroll=%d perf=%d\n",
           EN_SCR_GUARD, EN_SCR_NOSCROLL, PERF_LOG_EN);

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
