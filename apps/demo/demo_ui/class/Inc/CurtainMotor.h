#ifndef CURTAINMOTOR_H
#define CURTAINMOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "object.h"
#include "Switch.h"
#include "Percent.h"

/* 窗帘电机 = Object + Switch + 开合度 */
typedef struct {
    Object   base;       /* name + id + apply */
    Switch   sw;         /* 开关 */
    Percent  pos;        /* 开合度 0=关 100=全开 */
} CurtainMotor;

void          CurtainMotor_Init(CurtainMotor *dev, const char *name,
                                uint32_t id, uint16_t pos);
CurtainMotor *CurtainMotor_New(const char *name, uint32_t id, uint16_t pos);

#ifdef __cplusplus
}
#endif

#endif
