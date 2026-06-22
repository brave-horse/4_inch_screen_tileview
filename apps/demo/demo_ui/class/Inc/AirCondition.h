#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "object.h"
#include "Switch.h"

enum { AC_MODE_COOL = 0, AC_MODE_HEAT, AC_MODE_FAN, AC_MODE_AUTO };

/* 空调 = Object + Switch + 温度 + 模式 */
typedef struct {
    Object   base;       /* name + id + apply */
    Switch   sw;         /* 开关 */
    uint16_t temp;       /* 设定温度 */
    uint8_t  mode;       /* AC_MODE_* */
} AirCondition;

void          AirCondition_Init(AirCondition *dev, const char *name,
                                uint32_t id, uint16_t temp, uint8_t mode);
AirCondition *AirCondition_New(const char *name, uint32_t id,
                                uint16_t temp, uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif
