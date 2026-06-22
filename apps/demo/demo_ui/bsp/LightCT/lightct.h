/**
 *  @file   lightct.h
 *  @brief  色温灯硬件驱动(BSP): 暖光/冷光双路 PWM。供中间层 HWDataAccess 调用。
 */

#ifndef LIGHTCT_BSP_H
#define LIGHTCT_BSP_H

#include "stdint.h"

/** 初始化色温灯硬件(暖/冷两路 PWM)。 */
void LightCT_Init(void);

/**
 * 按亮度/色温驱动色温灯。
 * @param brightness 亮度(%), 0..100
 * @param color_temp 色温(K), 2700..6500
 */
void LightCT_Set(uint16_t brightness, uint16_t color_temp);

#endif /* LIGHTCT_BSP_H */
