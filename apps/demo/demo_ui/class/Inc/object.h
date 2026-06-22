#ifndef OBJECT_H
#define OBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define OBJ_NAME_MAX 24

typedef struct {
    char     name[OBJ_NAME_MAX];
    uint32_t id;
    void   (*apply)(void *dev);   /* 旧式设备(窗帘/空调)的简单回调; Light 子类不用(走 ops) */
} Object;

void     Object_Init(Object *obj, const char *name, uint32_t id);
Object  *Object_New(const char *name, uint32_t id);
void     Object_Delete(Object *obj);

#ifdef __cplusplus
}
#endif

#endif
