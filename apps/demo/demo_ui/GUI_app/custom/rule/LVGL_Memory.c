#include "lvgl.h"
#include "LVGL_Memory.h"

#ifndef LV_USE_GUIDER_SIMULATOR
#include "system/malloc.h"   /* get_malloc_remain_heap_size, 杰理系统堆 */
#endif

/* A方案: LV_MEM_CUSTOM=1 已让 LVGL 全走系统堆(lv_conf.h)。
 * 这里只补两件事: 切屏清缓存 + 诊断打印。分配/释放交给杰理 malloc/free。 */

/* 切屏调用: 清空图片缓存。LVGL 遍历缓存对每张图调 free → 大图还回系统堆。
 * 不能自己 free 那些指针(LVGL 还持有), 必须经此让 LVGL 来 free。 */
void lvgl_mem_purge_cache(void)
{
    lv_img_cache_invalidate_src(NULL);
}

/* 诊断: 打印系统堆剩余, 看切屏前后内存有没有被旧图占住不放 */
void lvgl_mem_report(const char *tag)
{
#ifndef LV_USE_GUIDER_SIMULATOR
    printf("[lvgl_mem] %s heap_left=%d\n", tag ? tag : "", get_malloc_remain_heap_size());
#endif
}
