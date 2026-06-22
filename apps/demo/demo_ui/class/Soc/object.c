#include <string.h>
#include <stdlib.h>
#include "object.h"

void Object_Init(Object *obj, const char *name, uint32_t id)
{
    if (!obj) return;
    if (name) {
        strncpy(obj->name, name, OBJ_NAME_MAX - 1);
        obj->name[OBJ_NAME_MAX - 1] = '\0';
    } else {
        obj->name[0] = '\0';
    }
    obj->id = id;
    obj->apply = NULL;
}

Object *Object_New(const char *name, uint32_t id)
{
    Object *obj = (Object *)malloc(sizeof(Object));
    if (!obj) return NULL;
    Object_Init(obj, name, id);
    return obj;
}

void Object_Delete(Object *obj)
{
    if (obj) free(obj);
}
