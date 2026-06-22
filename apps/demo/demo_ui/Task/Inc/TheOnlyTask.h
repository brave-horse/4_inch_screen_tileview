/**
 *  @file   TheOnlyTask.h
 *  @brief  色温灯任务: 周期检查 HWInterface.LightCT 是否被 UI 改过, 有则 Apply 下发硬件。
 */

#ifndef THEONLYTASK_H
#define THEONLYTASK_H

#ifdef __cplusplus
extern "C" {
#endif

/** 创建唯一任务(thread_fork)。@return 0 成功, 其它失败。 */
int TheOnlyTaskCreate(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*THEONLYTASK_H*/
