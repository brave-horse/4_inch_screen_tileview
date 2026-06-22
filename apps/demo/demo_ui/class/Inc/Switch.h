#ifndef SWITCH_H
#define SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
    bool on;
} Switch;

void Switch_Init(Switch *sw, bool on);
void Switch_Set(Switch *sw, bool on);
void Switch_Toggle(Switch *sw);
bool Switch_IsOn(const Switch *sw);

#ifdef __cplusplus
}
#endif

#endif
