#include <stdio.h>
#include <stdlib.h>
#include "CurtainMotor.h"

static void curtain_apply(void *dev)
{
    CurtainMotor *c = (CurtainMotor *)dev;
    if (!Switch_IsOn(&c->sw)) {
        printf("  -> [窗帘 %s] 电机关\n", c->base.name);
        return;
    }
    printf("  -> [窗帘 %s] 开合度=%u%%\n",
           c->base.name, Percent_Get(&c->pos));
}

void CurtainMotor_Init(CurtainMotor *dev, const char *name,
                       uint32_t id, uint16_t pos)
{
    if (!dev) return;
    Object_Init(&dev->base, name, id);
    dev->base.apply = curtain_apply;
    Switch_Init(&dev->sw, false);
    Percent_Init(&dev->pos, pos);
}

CurtainMotor *CurtainMotor_New(const char *name, uint32_t id, uint16_t pos)
{
    CurtainMotor *dev = (CurtainMotor *)malloc(sizeof(CurtainMotor));
    if (!dev) return NULL;
    CurtainMotor_Init(dev, name, id, pos);
    return dev;
}
