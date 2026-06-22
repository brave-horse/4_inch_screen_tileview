#ifndef __CUSTOM_IMG_H_
#define __CUSTOM_IMG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "gui_guider.h"



const char *custom_img_get_path(const char *name);
void custom_img_set_src(lv_obj_t *img, const char *name);
lv_obj_t *custom_img_create(lv_obj_t *parent, const char *name);

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_IMG_H_ */
