#ifndef HW_CLOUD_TASK_H
#define HW_CLOUD_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>

enum {
    HW_MSG_NONE = 0,

    HW_MSG_LIGHT_CT_SWITCH,   /* bool on      — 色温灯开关 */
    HW_MSG_LIGHT_CT_BRI,      /* uint16_t val — 色温灯亮度 */
    HW_MSG_LIGHT_CT_CT,       /* uint16_t val — 色温灯色温 */
    HW_MSG_LIGHT_LED_SWITCH,  /* bool on      — LED灯带开关 */
    HW_MSG_LIGHT_MAG_SWITCH,  /* bool on      — 磁吸灯开关 */
    HW_MSG_LIGHT_RGB_SWITCH,
    HW_MSG_LIGHT_RGB_COLOR,
    HW_MSG_CURTAIN_SWITCH,    /* uint8_t idx, bool on */
    HW_MSG_CURTAIN_POS,       /* uint8_t idx, uint16_t pos */
    HW_MSG_CURTAIN_ANGLE,     /* uint16_t val — 梦幻帘旋转角(度) */
    HW_MSG_AIRCON_SWITCH,     /* bool on      — 空调电源 */
    HW_MSG_AIRCON_MODE,       /* uint16_t val — 空调模式 0制冷/1制热/2除湿/3送风 */
    HW_MSG_AIRCON_SPEED,      /* uint16_t val — 空调风速 0/1/2档, 3=自动 */
    HW_MSG_AIRCON_TEMP,       /* uint16_t val — 空调温度 16~32℃ */
    HW_MSG_DRYRACK_POS,       /* uint16_t val — 晾衣机位置 0~100% */
    HW_MSG_DRYRACK_LIGHT,     /* bool on      — 晾衣机照明 */
    HW_MSG_FANLIGHT_POWER,    /* bool on      — 风扇灯电源 */
    HW_MSG_FANLIGHT_FAN,      /* bool on + uint16_t val — 风扇开关+档位 */
    HW_MSG_FANLIGHT_SPEED,    /* uint16_t val — 风扇档位 0~3 */
    HW_MSG_FANLIGHT_LIGHT,    /* bool on      — 风扇灯照明 */
    HW_MSG_CLOUD_CMD,

    HW_MSG_COUNT
};

typedef struct {
    uint8_t  type;
    uint8_t  idx;
    uint16_t val;
    bool     on;
} HW_Msg;

int  hw_cloud_task_create(void);
void hw_cloud_post(HW_Msg *msg);

#ifdef __cplusplus
}
#endif

#endif
