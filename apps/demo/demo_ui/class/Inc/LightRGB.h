#ifndef LIGHTRGB_H
#define LIGHTRGB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "Light.h"

// RGB灯: Light + RGB三色
typedef struct {
    Light   base;    // 父类(first member → 可上溯)
    uint8_t r;       // 0~255
    uint8_t g;
    uint8_t b;
} LightRGB;

void     LightRGB_Init(LightRGB *light, const char *name, uint32_t id, uint16_t brightness);
LightRGB *LightRGB_New(const char *name, uint32_t id, uint16_t brightness);
void     LightRGB_SetColor(LightRGB *light, uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
}
#endif

#endif
