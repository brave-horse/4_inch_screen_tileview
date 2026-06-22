#include <stdlib.h>
#include "Light.h"

void Light_BaseInit(Light *self, const char *name, uint32_t id,
                    uint16_t brightness, const LightOps *ops)
{
    if (!self) return;
    Object_Init(&self->base, name, id);
    Switch_Init(&self->sw, false);
    Percent_Init(&self->brightness, brightness);
    self->ops = ops;
}

/* ── 公共操作 ── */

void Light_SetOn(Light *self, bool on)
{
    if (self) Switch_Set(&self->sw, on);
}

bool Light_IsOn(const Light *self)
{
    return self ? Switch_IsOn(&self->sw) : false;
}

void Light_Toggle(Light *self)
{
    if (self) Switch_Toggle(&self->sw);
}

void Light_SetBrightness(Light *self, uint16_t percent)
{
    if (self) Percent_Set(&self->brightness, percent);
}

uint16_t Light_GetBrightness(const Light *self)
{
    return self ? Percent_Get(&self->brightness) : 0;
}

const char *Light_Name(const Light *self)
{
    return self ? self->base.name : "";
}

uint32_t Light_Id(const Light *self)
{
    return self ? self->base.id : 0;
}

/* ── 多态操作 ── */

void Light_Apply(const Light *self)
{
    if (self && self->ops && self->ops->apply)
        self->ops->apply(self);
}

void Light_Delete(Light *self)
{
    if (!self) return;
    if (self->ops && self->ops->destroy)
        self->ops->destroy(self);
    free(self);
}
