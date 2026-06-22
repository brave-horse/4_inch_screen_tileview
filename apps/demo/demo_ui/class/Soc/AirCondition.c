#include <stdio.h>
#include <stdlib.h>
#include "AirCondition.h"

static const char *mode_name[] = { "制冷", "制热", "送风", "自动" };

static void ac_apply(void *dev)
{
    AirCondition *ac = (AirCondition *)dev;
    if (!Switch_IsOn(&ac->sw)) {
        printf("  -> [空调 %s] 关\n", ac->base.name);
        return;
    }
    printf("  -> [空调 %s] 温度=%u 模式=%s\n",
           ac->base.name, ac->temp,
           ac->mode < 4 ? mode_name[ac->mode] : "?");
}

void AirCondition_Init(AirCondition *dev, const char *name,
                       uint32_t id, uint16_t temp, uint8_t mode)
{
    if (!dev) return;
    Object_Init(&dev->base, name, id);
    dev->base.apply = ac_apply;
    Switch_Init(&dev->sw, false);
    dev->temp = temp;
    dev->mode = mode;
}

AirCondition *AirCondition_New(const char *name, uint32_t id,
                                uint16_t temp, uint8_t mode)
{
    AirCondition *dev = (AirCondition *)malloc(sizeof(AirCondition));
    if (!dev) return NULL;
    AirCondition_Init(dev, name, id, temp, mode);
    return dev;
}
