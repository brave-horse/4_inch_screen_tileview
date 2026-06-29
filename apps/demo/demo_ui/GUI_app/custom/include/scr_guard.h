#ifndef SCR_GUARD_H
#define SCR_GUARD_H

#ifdef __cplusplus
extern "C" {
#endif

/* 屏指针守卫：解决 gui_guider 切屏时 auto_del 删掉旧屏、却不清空 guider_ui.screen_*
 * 全局指针，导致指针变野(指向已释放内存，且地址被对象池复用后会"别名"到别的屏)的问题。
 *
 * 本工程 events_init.c 的切屏全部是 ui_load_scr_animation(..., auto_del=true)，
 * 正好会触发这个坑，所以必须装。
 *
 * 做法：给每个"成为当前活动屏"的屏挂一个 LV_EVENT_DELETE 回调；屏被删的瞬间(地址尚未
 * 被复用之前)把指向它的 guider_ui.screen_* 槽位清成 NULL。此后该指针只会是"有效"或
 * "NULL"，永不变野。下次 setup_scr_screen_X 重建时会把新对象地址写回该槽位(gui_guider
 * 自带，无需我们管)。
 *
 * 在 custom_init() 里、其它模块初始化之前调用一次即可。 */
void scr_guard_init(void);

#ifdef __cplusplus
}
#endif

#endif /* SCR_GUARD_H */
