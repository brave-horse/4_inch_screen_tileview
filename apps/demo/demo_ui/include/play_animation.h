#ifndef PLAY_ANIMATION_H
#define PLAY_ANIMATION_H

/* 开机动画入口: 在 layer_top 盖全屏黑底, 居中播放 boot.avi(MJPEG),
 * 播完(或超时兜底)自动移除遮罩露出主屏。
 * 必须在 LVGL 任务上下文调用(app_main.c 的 jl_gui_init 内, setup_ui 之后)。 */
void play_animation_start(void);

#endif /* PLAY_ANIMATION_H */
