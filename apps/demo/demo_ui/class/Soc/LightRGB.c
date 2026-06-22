#include <stdio.h>
#include <stdlib.h>
#include "LightRGB.h"

static void lightrgb_apply(const Light *self)
{
    const LightRGB *l = (const LightRGB *)self;
    if (!Light_IsOn(self)) {
        printf("  -> [RGB灯 %s] 关\n", Light_Name(self));
        return;
    }
    printf("  -> [RGB灯 %s] RGB=(%u,%u,%u) 亮度=%u%%\n",
           Light_Name(self), l->r, l->g, l->b, Light_GetBrightness(self));
}

static const LightOps LIGHTRGB_OPS = {
    .apply   = lightrgb_apply,
    .destroy = NULL,
};

void LightRGB_Init(LightRGB *light, const char *name, uint32_t id, uint16_t brightness)
{
    if (!light) return;
    Light_BaseInit(&light->base, name, id, brightness, &LIGHTRGB_OPS);
    light->r = 255;
    light->g = 255;
    light->b = 255;
}

LightRGB *LightRGB_New(const char *name, uint32_t id, uint16_t brightness)
{
    LightRGB *light = (LightRGB *)malloc(sizeof(LightRGB));
    if (!light) return NULL;
    LightRGB_Init(light, name, id, brightness);
    return light;
}

void LightRGB_SetColor(LightRGB *light, uint8_t r, uint8_t g, uint8_t b)
{
    if (!light) return;
    light->r = r;
    light->g = g;
    light->b = b;
}
