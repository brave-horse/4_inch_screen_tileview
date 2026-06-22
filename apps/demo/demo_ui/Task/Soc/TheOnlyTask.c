/**
 *  @file   TheOnlyTask.c
 *  @brief  色温灯任务实现, 系统函数用杰理 SDK 的 os。
 *  @details 任务用 task_create 创建, 优先级/栈/队列在 app_main.c 的 task_info_table 登记。
 */

#include <stdio.h>
#include "app_config.h"
#include "system/task.h"        /* task_create */
#include "os/os_api.h"          /* os_time_dly */
#include "HWDataAccess.h"
#include "TheOnlyTask.h"

#define THE_ONLYTASK_NAME      "The_onlytask"
#define THE_ONLYTASK_POLL_TICK 2

/** 任务主体: 开机下发一次, 之后轮询 changed, 有变更就 Apply。@param parm 未使用 */
static void TheOnlyTask(void *parm)
{


    while (1) {



    }
}

/** 创建色温灯任务(task_create, 信息登记在 app_main.c task_info_table)。@return 0 成功 */
int TheOnlyTaskCreate(void)
{
    return task_create(TheOnlyTask, NULL, THE_ONLYTASK_NAME);
}
