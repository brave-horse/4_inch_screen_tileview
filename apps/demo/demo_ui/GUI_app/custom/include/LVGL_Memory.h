#ifndef LVGL_MEMORY_H
#define LVGL_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

/* 切屏时调用: 清空 LVGL 图片缓存, 上一屏的解码大图随之 free 回系统堆 */
void lvgl_mem_purge_cache(void);

/* 诊断: 打印当前系统堆剩余字节(tag 标记调用点) */
void lvgl_mem_report(const char *tag);

#ifdef __cplusplus
}
#endif

#endif
