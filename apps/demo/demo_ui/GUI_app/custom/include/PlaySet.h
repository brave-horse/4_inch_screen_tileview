#ifndef PLAYSET_H
#define PLAYSET_H

#ifdef __cplusplus
extern "C" {
#endif

/* 显示设置屏加载: tileview 并入 List flex + 手风琴折叠 + 选中更新值。
 * events_init 在 PlaySet 的 SCREEN_LOADED 事件里调用。 */
void playset_on_screen_load(void);

#ifdef __cplusplus
}
#endif

#endif
