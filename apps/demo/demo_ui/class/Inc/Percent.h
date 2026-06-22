#ifndef PERCENT_H
#define PERCENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef struct {
    uint8_t value;   // 0~100, auto-clamped
} Percent;

void    Percent_Init(Percent *p, uint16_t value);
void    Percent_Set(Percent *p, uint16_t value);
uint8_t Percent_Get(const Percent *p);

#ifdef __cplusplus
}
#endif

#endif
