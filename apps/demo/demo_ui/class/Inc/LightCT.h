#ifndef LIGHTCT_H
#define LIGHTCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "Light.h"

// 色温灯: Light + 色温
typedef struct {
    Light    base;         // 父类(first member → 可上溯)
    uint16_t color_temp;   // K
} LightCT;

void      LightCT_Init(LightCT *light, const char *name, uint32_t id,
                       uint16_t color_temp, uint16_t brightness);
LightCT  *LightCT_New(const char *name, uint32_t id,
                       uint16_t color_temp, uint16_t brightness);
void      LightCT_SetColorTemp(LightCT *light, uint16_t color_temp);
uint16_t  LightCT_GetColorTemp(const LightCT *light);

#ifdef __cplusplus
}
#endif

#endif
