#ifndef DEVICE_MANAGEMENT_H
#define DEVICE_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* 设备槽位索引 */
enum {
    DEV_SLOT_CT_LIGHT = 0,   /* cont_1: 色温灯 */
    DEV_SLOT_LEDSTRIP,        /* cont_2: LED灯带 */
    DEV_SLOT_MAGLIGHT,        /* cont_3: 磁吸灯 */
    DEV_SLOT_RGBLIGHT,        /* cont_4: 彩色灯 */
    DEV_SLOT_CURTAIN,         /* 窗帘(暂未实现) */
    DEV_SLOT_COUNT
};

/* SCREEN_LOADED 事件里调用: 从中间层读所有设备状态, 刷新 UI */
void dev_mgmt_on_load(void);

/* 各灯开关(VALUE_CHANGED)事件里调用: 读 CHECKED → 写中间层 → 刷指示器 */
void dev_mgmt_ct_on_toggle(void);
void dev_mgmt_led_on_toggle(void);
void dev_mgmt_mag_on_toggle(void);
void dev_mgmt_rgb_on_toggle(void);

/* 各窗帘 开/关 按钮(CLICKED)事件里调用: 全开/全关 → 写中间层 → 刷状态图 */
void dev_mgmt_fabric_open(void);
void dev_mgmt_fabric_close(void);
void dev_mgmt_sheers_open(void);
void dev_mgmt_sheers_close(void);
void dev_mgmt_rollblind_open(void);
void dev_mgmt_rollblind_close(void);
void dev_mgmt_dream_open(void);
void dev_mgmt_dream_close(void);

/* 晾衣机 升/降 按钮(CLICKED): 定时升降 → 写中间层 → 刷状态图 */
void dev_mgmt_dryrack_up(void);
void dev_mgmt_dryrack_down(void);

/* 音乐 播放/暂停(imgbtn_9 VALUE_CHANGED): 转盘随播放转 */
void dev_mgmt_music_toggle(void);

/* 风扇灯 灯/风扇 开关(sFanLightBtn / sSourceBtn VALUE_CHANGED) */
void dev_mgmt_fanlight_light_toggle(void);
void dev_mgmt_fanlight_fan_toggle(void);

/* 浴霸 灯暖开关(sHeaterLightBtn VALUE_CHANGED) / 待机键(IdleBtn CLICKED) */
void dev_mgmt_heater_light_toggle(void);
void dev_mgmt_heater_idle(void);

/* 空调 电源(imgbtn_6 VALUE_CHANGED) */
void dev_mgmt_aircon_toggle(void);

#ifdef __cplusplus
}
#endif

#endif
