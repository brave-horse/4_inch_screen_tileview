#ifndef HWDATAACCESS_H
#define HWDATAACCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>

#define LIGHTCT_BRIGHTNESS_MIN   0
#define LIGHTCT_BRIGHTNESS_MAX   100
#define LIGHTCT_COLOR_TEMP_MIN   2700
#define LIGHTCT_COLOR_TEMP_MAX   6500

#define CURTAIN_COUNT_MAX        10
#define CURTAIN_POS_MIN          0
#define CURTAIN_POS_MAX          100

/* 窗帘 idx: 每帘独立一路 */
enum {
    CURTAIN_IDX_FABRIC = 0,   /* 布帘 */
    CURTAIN_IDX_SHEERS,       /* 纱帘 */
    CURTAIN_IDX_ROLLBLIND,    /* 卷帘 */
    CURTAIN_IDX_DREAM,        /* 梦幻帘 */
    CURTAIN_IDX_COUNT
};

#define CURTAIN_FULL_MS  2200    /* 0→100% 全行程耗时(ms), 调开合速度改这里 */

/* 晾衣机复用同一运动模型的独立槽位(在 CURTAIN_COUNT_MAX 范围内, 不与窗帘冲突) */
#define MOTION_IDX_DRYRACK  CURTAIN_IDX_COUNT

/* 窗帘定时运动模型: 按时间算位置, 跨界面共享(管理界面起步, 子界面续播) */
void     curtain_motion_start(uint8_t idx, uint16_t target);  /* 起步移动到 target(%) */
void     curtain_motion_set(uint8_t idx, uint16_t pos);       /* 手动定位(拖动/暂停): 停在 pos */
uint16_t curtain_motion_current(uint8_t idx);                 /* 按已过时间算当前位置(%) */
uint16_t curtain_motion_target(uint8_t idx);                  /* 目标位置(%) */
uint32_t curtain_motion_remaining_ms(uint8_t idx);            /* 到达 target 还需(ms) */
void     curtain_motion_set_speed(uint8_t idx, uint32_t full_ms); /* 设本槽位 0→100% 全程耗时(各屏单独调速) */

typedef struct
{
    bool     switch_status;
    uint16_t brightness;
    uint16_t color_temp;

    void (*SetOnOff)(bool on);
    void (*SetBrightness)(uint16_t brightness);
    void (*SetColorTemp)(uint16_t color_temp);
    void (*Apply)(void);
} HW_LightCT_InterfaceTypeDef;

typedef struct
{
    bool     switch_status;
    uint16_t brightness;
    uint16_t color_temp;

    void (*SetOnOff)(bool on);
    void (*SetBrightness)(uint16_t brightness);
    void (*SetColorTemp)(uint16_t color_temp);
    void (*Apply)(void);
} HW_LEDStrip_InterfaceTypeDef;

typedef struct
{
    bool     switch_status[CURTAIN_COUNT_MAX];
    uint16_t position[CURTAIN_COUNT_MAX];

    void (*SetOnOff)(uint8_t idx, bool on);
    void (*SetPos)(uint8_t idx, uint16_t pos);
    void (*Apply)(uint8_t idx);
} HW_Curtain_InterfaceTypeDef;

typedef struct
{
    bool     power;      /* master power */
    bool     fan_on;     /* fan switch */
    bool     light_on;   /* light switch */
    uint8_t  speed;      /* fan speed 0..3 */

    void (*SetPower)(bool on);
    void (*SetFan)(bool on);
    void (*SetSpeed)(uint8_t speed);
    void (*SetLight)(bool on);
    void (*Apply)(void);
} HW_FanAndLight_InterfaceTypeDef;

typedef struct
{
    bool playing;   /* 音乐播放中(管理屏/子屏共享) */
} HW_Music_InterfaceTypeDef;

typedef struct
{
    bool light;     /* 晾衣机照明(管理屏/子屏共享; 位置走 curtain_motion) */
} HW_DryRack_InterfaceTypeDef;

typedef struct
{
    bool   light;   /* 浴霸照明: 独立开关, 可与模式同时存在 */
    int8_t mode;    /* 浴霸模式(互斥): -1=无 1暖风高 2暖风低 3换气 4吹风 5待机 */
} HW_Heater_InterfaceTypeDef;

typedef struct
{
    bool    power;       /* 空调电源 */
    uint8_t mode;        /* 0制冷 1制热 2送风 3除湿 */
    uint8_t temperature; /* 温度 16~32℃ */
} HW_AirCondition_InterfaceTypeDef;

typedef struct
{
    uint8_t standby_delay;    /* 延时进待机 idx 0-6: 15秒/30秒/1分/2分/5分/10分/永久 */
    uint8_t standby_display;  /* 待机显示  idx 0-6: 熄屏/屏保/场景/开关/设备/灯光/窗帘 */
    uint8_t proximity;        /* 接近亮屏  idx 0-3: 关闭/近/中/远 */

    void (*SetStandbyDelay)(uint8_t idx);
    void (*SetStandbyDisplay)(uint8_t idx);
    void (*SetProximity)(uint8_t idx);
} HW_Display_InterfaceTypeDef;

typedef struct
{
    HW_LightCT_InterfaceTypeDef     LightCT;
    HW_LEDStrip_InterfaceTypeDef    LEDStrip;
    HW_LEDStrip_InterfaceTypeDef    MagLight;   /* 复用 LEDStrip 结构, 只用 switch_status */
    HW_LEDStrip_InterfaceTypeDef    RGBLight;   /* 复用 LEDStrip 结构, 只用 switch_status */
    HW_Curtain_InterfaceTypeDef     Curtain;
    HW_FanAndLight_InterfaceTypeDef FanAndLight;
    HW_Music_InterfaceTypeDef       Music;
    HW_DryRack_InterfaceTypeDef     DryRack;
    HW_Heater_InterfaceTypeDef      Heater;
    HW_AirCondition_InterfaceTypeDef AirCondition;
    HW_Display_InterfaceTypeDef      Display;
} HW_InterfaceTypeDef;

extern HW_InterfaceTypeDef HWInterface;

void HW_Init(void);

#ifdef __cplusplus
}
#endif

#endif
