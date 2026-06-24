#ifndef NETSETTING_H
#define NETSETTING_H

#ifdef __cplusplus
extern "C" {
#endif

/* 网络设置屏加载: 初始为未绑定态(二维码+开始绑定), 其余状态控件 HIDDEN;
 * 挂"开始绑定"→绑定中、"解除设备"→未绑定。GUI-Guider 在 Screen Loaded 事件调。 */
void netsetting_on_screen_load(void);

/* 配网完成回调(外部/云端调): 切到已绑定状态(显示解除按钮) */
void netsetting_set_bound(void);

#ifdef __cplusplus
}
#endif

#endif
