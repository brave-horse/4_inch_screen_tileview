/**
 *  @file   lightct.c
 *  @brief  色温灯硬件驱动(BSP) 实现。当前为桩, 待接 AC792 的 PWM/调光硬件。
 */

#include "lightct.h"

/** 初始化色温灯硬件(暖/冷两路 PWM)。 */
void LightCT_Init(void)
{
    /* TODO(硬件): 配置暖光/冷光两路 PWM 的 GPIO 与定时器。 */
}

/**
 * 按亮度/色温驱动色温灯。
 * @param brightness 亮度(%), 0..100
 * @param color_temp 色温(K), 2700..6500
 */
void LightCT_Set(uint16_t brightness, uint16_t color_temp)
{
    /* TODO(硬件): 由 color_temp 算暖/冷占比, 由 brightness 定总亮度, 写两路 PWM 占空比。 */
    (void)brightness;
    (void)color_temp;
}
