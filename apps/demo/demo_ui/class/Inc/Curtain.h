#ifndef CURTAIN_H
#define CURTAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>
#include "object.h"
#include "Switch.h"
#include "Percent.h"

typedef struct Curtain Curtain;

// vtable: 窗帘硬件下发
typedef struct {
    void (*apply)  (const Curtain *self);
    void (*destroy)(Curtain *self);
} CurtainOps;

// 窗帘: Object + Switch(电机开关) + Percent(开合度 0=关 100=全开)
struct Curtain {
    Object           base;
    Switch           sw;
    Percent          position;   // 0~100
    const CurtainOps *ops;
};

// 供子类(未来扩展)初始化公共部分
void Curtain_BaseInit(Curtain *self, const char *name, uint32_t id,
                      uint16_t position, const CurtainOps *ops);

// 公共操作
void     Curtain_SetOn(Curtain *self, bool on);
bool     Curtain_IsOn(const Curtain *self);
void     Curtain_Toggle(Curtain *self);
void     Curtain_SetPos(Curtain *self, uint16_t pos);   // 0=关 100=全开
uint8_t  Curtain_GetPos(const Curtain *self);
const char *Curtain_Name(const Curtain *self);
uint32_t    Curtain_Id(const Curtain *self);

// 多态操作
void Curtain_Apply(const Curtain *self);
void Curtain_Delete(Curtain *self);

// 标准窗帘(无子类扩展)的便捷构造
void      Curtain_Init(Curtain *self, const char *name, uint32_t id, uint16_t position);
Curtain  *Curtain_New(const char *name, uint32_t id, uint16_t position);

#ifdef __cplusplus
}
#endif

#endif
