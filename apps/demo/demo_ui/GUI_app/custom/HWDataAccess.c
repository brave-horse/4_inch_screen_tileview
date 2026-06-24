#include "lvgl.h"
#include "HWDataAccess.h"
#include "LightCT.h"
#include "CurtainMotor.h"

static LightCT      g_light_ct;
static LightCT      g_led_strip;
static CurtainMotor g_curtain[CURTAIN_COUNT_MAX];
static uint8_t      g_curtain_cnt;

static uint16_t clamp_to(uint16_t v, uint16_t lo, uint16_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

/* ═══════════ 色温灯 ═══════════ */

static void impl_LightCT_SetOnOff(bool btn_status)
{
    Switch_Set(&g_light_ct.base.sw, btn_status);
    HWInterface.LightCT.switch_status = btn_status;
}

static void impl_LightCT_SetBrightness(uint16_t bri)
{
    bri = clamp_to(bri, LIGHTCT_BRIGHTNESS_MIN, LIGHTCT_BRIGHTNESS_MAX);
    Percent_Set(&g_light_ct.base.brightness, bri);
    HWInterface.LightCT.brightness = bri;
}

static void impl_LightCT_SetColorTemp(uint16_t ct)
{
    ct = clamp_to(ct, LIGHTCT_COLOR_TEMP_MIN, LIGHTCT_COLOR_TEMP_MAX);
    g_light_ct.color_temp = ct;
    HWInterface.LightCT.color_temp = ct;
}

static void impl_LightCT_Apply(void)
{
    uint16_t bri = HWInterface.LightCT.switch_status
                   ? HWInterface.LightCT.brightness : 0;
    Percent_Set(&g_light_ct.base.brightness, bri);
    Light_Apply(&g_light_ct.base);
}

/* ═══════════ LED灯带 ═══════════ */

static void impl_LEDStrip_SetOnOff(bool btn_status)
{
    Switch_Set(&g_led_strip.base.sw, btn_status);
    HWInterface.LEDStrip.switch_status = btn_status;
}

static void impl_LEDStrip_SetBrightness(uint16_t bri)
{
    bri = clamp_to(bri, LIGHTCT_BRIGHTNESS_MIN, LIGHTCT_BRIGHTNESS_MAX);
    Percent_Set(&g_led_strip.base.brightness, bri);
    HWInterface.LEDStrip.brightness = bri;
}

static void impl_LEDStrip_SetColorTemp(uint16_t ct)
{
    ct = clamp_to(ct, LIGHTCT_COLOR_TEMP_MIN, LIGHTCT_COLOR_TEMP_MAX);
    g_led_strip.color_temp = ct;
    HWInterface.LEDStrip.color_temp = ct;
}

static void impl_LEDStrip_Apply(void)
{
    uint16_t bri = HWInterface.LEDStrip.switch_status
                   ? HWInterface.LEDStrip.brightness : 0;
    Percent_Set(&g_led_strip.base.brightness, bri);
    Light_Apply(&g_led_strip.base);
}

/* ═══════════ 窗帘 ═══════════ */

static void impl_Curtain_SetOnOff(uint8_t idx, bool btn_status)
{
    if (idx >= g_curtain_cnt) return;
    Switch_Set(&g_curtain[idx].sw, btn_status);
    HWInterface.Curtain.switch_status[idx] = btn_status;
}

static void impl_Curtain_SetPos(uint8_t idx, uint16_t pos)
{
    if (idx >= g_curtain_cnt) return;
    pos = clamp_to(pos, CURTAIN_POS_MIN, CURTAIN_POS_MAX);
    Percent_Set(&g_curtain[idx].pos, pos);
    HWInterface.Curtain.position[idx] = pos;
}

static void impl_Curtain_Apply(uint8_t idx)
{
    if (idx >= g_curtain_cnt) return;
    uint16_t pos = Switch_IsOn(&g_curtain[idx].sw)
                   ? Percent_Get(&g_curtain[idx].pos) : 0;
    Percent_Set(&g_curtain[idx].pos, pos);
    if (g_curtain[idx].base.apply)
        g_curtain[idx].base.apply(&g_curtain[idx]);
}

/* ═══════════ 磁吸灯 / 彩色灯 (仅存开关状态) ═══════════ */

static void impl_MagLight_SetOnOff(bool on)
{
    HWInterface.MagLight.switch_status = on;
}

static void impl_RGBLight_SetOnOff(bool on)
{
    HWInterface.RGBLight.switch_status = on;
}

/* ═══════════ 风扇灯 ═══════════ */

static void impl_FanAndLight_SetPower(bool on)
{
    HWInterface.FanAndLight.power = on;
}

static void impl_FanAndLight_SetFan(bool on)
{
    HWInterface.FanAndLight.fan_on = on;
}

static void impl_FanAndLight_SetSpeed(uint8_t speed)
{
    HWInterface.FanAndLight.speed = speed;
}

static void impl_FanAndLight_SetLight(bool on)
{
    HWInterface.FanAndLight.light_on = on;
}

static void impl_FanAndLight_Apply(void)
{
    /* TODO 接硬件驱动: 按 power/fan_on/speed/light_on 下发 */
}

/* ═══════════ 全局实例 ═══════════ */

/* 显示设置: 只存 idx, 预留硬件/云端下发钩子 */
static void impl_Display_SetStandbyDelay(uint8_t idx)   { HWInterface.Display.standby_delay   = idx; }
static void impl_Display_SetStandbyDisplay(uint8_t idx) { HWInterface.Display.standby_display = idx; }
static void impl_Display_SetProximity(uint8_t idx)      { HWInterface.Display.proximity       = idx; }

HW_InterfaceTypeDef HWInterface = {
    .LightCT = {
        .switch_status = false,
        .brightness    = 50,
        .color_temp    = 4600,
        .SetOnOff      = impl_LightCT_SetOnOff,
        .SetBrightness = impl_LightCT_SetBrightness,
        .SetColorTemp  = impl_LightCT_SetColorTemp,
        .Apply         = impl_LightCT_Apply,
    },
    .LEDStrip = {
        .switch_status = false,
        .brightness    = 50,
        .color_temp    = 4600,
        .SetOnOff      = impl_LEDStrip_SetOnOff,
        .SetBrightness = impl_LEDStrip_SetBrightness,
        .SetColorTemp  = impl_LEDStrip_SetColorTemp,
        .Apply         = impl_LEDStrip_Apply,
    },
    .MagLight = {
        .switch_status = false,
        .SetOnOff      = impl_MagLight_SetOnOff,
    },
    .RGBLight = {
        .switch_status = false,
        .SetOnOff      = impl_RGBLight_SetOnOff,
    },
    .Curtain = {
        /* switch_status[]/position[] 默认全 0 (关) */
        .SetOnOff      = impl_Curtain_SetOnOff,
        .SetPos        = impl_Curtain_SetPos,
        .Apply         = impl_Curtain_Apply,
    },
    .FanAndLight = {
        .power     = false,
        .fan_on    = false,
        .light_on  = false,
        .speed     = 0,
        .SetPower  = impl_FanAndLight_SetPower,
        .SetFan    = impl_FanAndLight_SetFan,
        .SetSpeed  = impl_FanAndLight_SetSpeed,
        .SetLight  = impl_FanAndLight_SetLight,
        .Apply     = impl_FanAndLight_Apply,
    },
    .Heater = {
        .light = false,
        .mode  = -1,   /* 默认无模式 */
    },
    .Display = {
        .standby_delay     = 0,   /* 默认 15秒 */
        .standby_display   = 0,   /* 默认 熄屏 */
        .proximity         = 0,   /* 默认 关闭 */
        .SetStandbyDelay   = impl_Display_SetStandbyDelay,
        .SetStandbyDisplay = impl_Display_SetStandbyDisplay,
        .SetProximity      = impl_Display_SetProximity,
    },
};/*  */

/* ═══════════ 窗帘定时运动模型 ═══════════ */

static uint16_t s_mv_start_pos[CURTAIN_COUNT_MAX];   /* 本段起点(%) */
static uint16_t s_mv_target[CURTAIN_COUNT_MAX];      /* 目标(%) */
static uint32_t s_mv_start_tick[CURTAIN_COUNT_MAX];  /* 起始 tick */

uint16_t curtain_motion_current(uint8_t idx)
{
    if (idx >= CURTAIN_COUNT_MAX) return 0;
    int32_t start  = s_mv_start_pos[idx];
    int32_t target = s_mv_target[idx];
    int32_t dist   = target - start;
    int32_t cur;
    if (dist == 0) {
        cur = target;
    } else {
        int32_t abs_dist = dist < 0 ? -dist : dist;
        uint32_t dur     = (uint32_t)abs_dist * CURTAIN_FULL_MS / 100;   /* 本段耗时 */
        uint32_t elapsed = lv_tick_elaps(s_mv_start_tick[idx]);
        if (elapsed >= dur) cur = target;
        else                cur = start + dist * (int32_t)elapsed / (int32_t)dur;
    }
    if (cur < 0)   cur = 0;
    if (cur > 100) cur = 100;
    HWInterface.Curtain.position[idx] = (uint16_t)cur;     /* 同步缓存 */
    return (uint16_t)cur;
}

void curtain_motion_start(uint8_t idx, uint16_t target)
{
    if (idx >= CURTAIN_COUNT_MAX) return;
    s_mv_start_pos[idx]  = curtain_motion_current(idx);    /* 从当前位置起步(可能在移动中) */
    s_mv_target[idx]     = target > 100 ? 100 : target;
    s_mv_start_tick[idx] = lv_tick_get();
}

void curtain_motion_set(uint8_t idx, uint16_t pos)
{
    if (idx >= CURTAIN_COUNT_MAX) return;
    if (pos > 100) pos = 100;
    s_mv_start_pos[idx]  = pos;
    s_mv_target[idx]     = pos;
    s_mv_start_tick[idx] = lv_tick_get();
    HWInterface.Curtain.position[idx] = pos;
}

uint16_t curtain_motion_target(uint8_t idx)
{
    if (idx >= CURTAIN_COUNT_MAX) return 0;
    return s_mv_target[idx];
}

uint32_t curtain_motion_remaining_ms(uint8_t idx)
{
    if (idx >= CURTAIN_COUNT_MAX) return 0;
    int32_t dist = (int32_t)s_mv_target[idx] - (int32_t)curtain_motion_current(idx);
    if (dist < 0) dist = -dist;
    return (uint32_t)dist * CURTAIN_FULL_MS / 100;
}

void HW_Init(void)
{
    LightCT_Init(&g_light_ct,  "CT主灯", 1, 50, 4600);
    LightCT_Init(&g_led_strip, "LED灯带", 2, 50, 4600);
    g_curtain_cnt = CURTAIN_IDX_COUNT;
    CurtainMotor_Init(&g_curtain[CURTAIN_IDX_FABRIC],    "布帘",   10, 0);
    CurtainMotor_Init(&g_curtain[CURTAIN_IDX_SHEERS],    "纱帘",   11, 0);
    CurtainMotor_Init(&g_curtain[CURTAIN_IDX_ROLLBLIND], "卷帘",   12, 0);
    CurtainMotor_Init(&g_curtain[CURTAIN_IDX_DREAM],     "梦幻帘", 13, 0);
}
