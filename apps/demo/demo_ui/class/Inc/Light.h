#ifndef LIGHT_H
#define LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>
#include "object.h"
#include "Switch.h"
#include "Percent.h"

typedef struct Light Light;

// vtable: 每种灯不同的操作
typedef struct {
    void (*apply)  (const Light *self);
    void (*destroy)(Light *self);
} LightOps;

// 抽象父类: 所有灯的公共部分
struct Light {
    Object          base;
    Switch          sw;
    Percent         brightness;   // 0~100
    const LightOps *ops;
};

// 供子类构造调用: 初始化公共部分并挂 vtable
void Light_BaseInit(Light *self, const char *name, uint32_t id,
                    uint16_t brightness, const LightOps *ops);

// 公共操作(不走 vtable)
void     Light_SetOn(Light *self, bool on);
bool     Light_IsOn(const Light *self);
void     Light_Toggle(Light *self);
void     Light_SetBrightness(Light *self, uint16_t percent);
uint16_t Light_GetBrightness(const Light *self);
const char *Light_Name(const Light *self);
uint32_t    Light_Id(const Light *self);

// 多态操作(走 vtable)
void Light_Apply(const Light *self);
void Light_Delete(Light *self);

#ifdef __cplusplus
}
#endif

#endif
