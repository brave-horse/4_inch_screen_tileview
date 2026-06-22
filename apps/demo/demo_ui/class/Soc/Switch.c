#include "Switch.h"

void Switch_Init(Switch *sw, bool on)
{
    if (sw) sw->on = on;
}

void Switch_Set(Switch *sw, bool on)
{
    if (sw) sw->on = on;
}

void Switch_Toggle(Switch *sw)
{
    if (sw) sw->on = !sw->on;
}

bool Switch_IsOn(const Switch *sw)
{
    return sw ? sw->on : false;
}
