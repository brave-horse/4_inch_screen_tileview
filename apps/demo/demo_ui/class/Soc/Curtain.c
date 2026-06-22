#include <stdio.h>
#include <stdlib.h>
#include "Curtain.h"

/* ── 标准窗帘的 ops 实现 ── */

static void curtain_apply(const Curtain *self)
{
    if (!Curtain_IsOn(self)) {
        printf("  -> [窗帘 %s] 电机关\n", Curtain_Name(self));
        return;
    }
    printf("  -> [窗帘 %s] 开合度=%u%%\n", Curtain_Name(self), Curtain_GetPos(self));
}

static const CurtainOps CURTAIN_OPS = {
    .apply   = curtain_apply,
    .destroy = NULL,
};

/* ── 基类初始化(供未来子类复用) ── */

void Curtain_BaseInit(Curtain *self, const char *name, uint32_t id,
                      uint16_t position, const CurtainOps *ops)
{
    if (!self) return;
    Object_Init(&self->base, name, id);
    Switch_Init(&self->sw, false);
    Percent_Init(&self->position, position);
    self->ops = ops;
}

/* ── 公共操作 ── */

void Curtain_SetOn(Curtain *self, bool on)
{
    if (self) Switch_Set(&self->sw, on);
}

bool Curtain_IsOn(const Curtain *self)
{
    return self ? Switch_IsOn(&self->sw) : false;
}

void Curtain_Toggle(Curtain *self)
{
    if (self) Switch_Toggle(&self->sw);
}

void Curtain_SetPos(Curtain *self, uint16_t pos)
{
    if (self) Percent_Set(&self->position, pos);
}

uint8_t Curtain_GetPos(const Curtain *self)
{
    return self ? Percent_Get(&self->position) : 0;
}

const char *Curtain_Name(const Curtain *self)
{
    return self ? self->base.name : "";
}

uint32_t Curtain_Id(const Curtain *self)
{
    return self ? self->base.id : 0;
}

/* ── 多态操作 ── */

void Curtain_Apply(const Curtain *self)
{
    if (self && self->ops && self->ops->apply)
        self->ops->apply(self);
}

void Curtain_Delete(Curtain *self)
{
    if (!self) return;
    if (self->ops && self->ops->destroy)
        self->ops->destroy(self);
    free(self);
}

/* ── 标准窗帘便捷构造 ── */

void Curtain_Init(Curtain *self, const char *name, uint32_t id, uint16_t position)
{
    Curtain_BaseInit(self, name, id, position, &CURTAIN_OPS);
}

Curtain *Curtain_New(const char *name, uint32_t id, uint16_t position)
{
    Curtain *c = (Curtain *)malloc(sizeof(Curtain));
    if (!c) return NULL;
    Curtain_Init(c, name, id, position);
    return c;
}
