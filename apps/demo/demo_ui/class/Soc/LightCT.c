#include <stdio.h>
#include <stdlib.h>
#include "LightCT.h"

static void lightct_apply(const Light *self)
{
    const LightCT *l = (const LightCT *)self;
    if (!Light_IsOn(self)) {
        printf("  -> [CT灯 %s] 关\n", Light_Name(self));
        return;
    }
    printf("  -> [CT灯 %s] 色温=%uK 亮度=%u%%\n",
           Light_Name(self), l->color_temp, Light_GetBrightness(self));
}

static const LightOps LIGHTCT_OPS = {
    .apply   = lightct_apply,
    .destroy = NULL,
};

void LightCT_Init(LightCT *light, const char *name, uint32_t id,
                  uint16_t color_temp, uint16_t brightness)
{
    if (!light) return;
    Light_BaseInit(&light->base, name, id, brightness, &LIGHTCT_OPS);
    light->color_temp = color_temp;
}

LightCT *LightCT_New(const char *name, uint32_t id,
                     uint16_t color_temp, uint16_t brightness)
{
    LightCT *light = (LightCT *)malloc(sizeof(LightCT));
    if (!light) return NULL;
    LightCT_Init(light, name, id, color_temp, brightness);
    return light;
}

void LightCT_SetColorTemp(LightCT *light, uint16_t color_temp)
{
    if (light) light->color_temp = color_temp;
}

uint16_t LightCT_GetColorTemp(const LightCT *light)
{
    return light ? light->color_temp : 0;
}
