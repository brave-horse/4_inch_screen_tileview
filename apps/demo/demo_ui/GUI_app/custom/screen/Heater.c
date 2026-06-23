#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "Heater.h"

/* 状态存中间层(管理屏共享): 照明独立, 模式互斥 */
#define s_light  HWInterface.Heater.light   /* 照明独立开关 */
#define s_mode   HWInterface.Heater.mode    /* -1=无 1暖风高 2暖风低 3换气 4吹风 5待机 */

#define BLUE  lv_color_hex(0x2195f6)
#define GRAY  lv_color_hex(0x2f2d31)
#define GRAY_OPA 244

/* ══════ 内部辅助 ══════ */

/* HeatDev 底 → idleMode 默认 → 当前模式图 → 照明图(独立, 开则盖最上, 关则隐藏) */
static void heater_apply(void)
{
    lv_obj_t *modeimg[6] = {
        NULL,
        guider_ui.Heater_HeatHighMode,   /* 1 暖风高 */
        guider_ui.Heater_heaterlowMode,  /* 2 暖风低 */
        guider_ui.Heater_VentilateMode,  /* 3 换气 */
        guider_ui.Heater_WindMode,       /* 4 吹风 */
        guider_ui.Heater_idleMode,       /* 5 待机 */
    };
    lv_obj_move_foreground(guider_ui.Heater_HeatDev);
    lv_obj_move_foreground(guider_ui.Heater_idleMode);
    if (s_mode >= 1 && s_mode <= 5) lv_obj_move_foreground(modeimg[s_mode]);

    if (s_light) {
        lv_obj_clear_flag(guider_ui.Heater_HeatLight, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(guider_ui.Heater_HeatLight);
    } else {
        lv_obj_add_flag(guider_ui.Heater_HeatLight, LV_OBJ_FLAG_HIDDEN);
    }
}

/* 激活按钮蓝底, 其余灰底; 照明按钮按 s_light 独立 */
static void btn_color(void)
{
    lv_obj_t *modebtn[6] = {
        NULL,
        guider_ui.Heater_HeatHighBtn,  /* 1 */
        guider_ui.Heater_HeatLowBtn,   /* 2 */
        guider_ui.Heater_VentilateBtn, /* 3 */
        guider_ui.Heater_WindBtn,      /* 4 */
        guider_ui.Heater_IdleBtn,      /* 5 */
    };
    for (uint8_t i = 1; i <= 5; i++) {
        lv_obj_set_style_bg_color(modebtn[i], (i == s_mode) ? BLUE : GRAY, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(modebtn[i],   (i == s_mode) ? 255  : GRAY_OPA, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    lv_obj_set_style_bg_color(guider_ui.Heater_LightBtn, s_light ? BLUE : GRAY, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(guider_ui.Heater_LightBtn,   s_light ? 255  : GRAY_OPA, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* 模式键: 同键再点→取消(回无模式), 不同键→切换 */
static void mode_click(int8_t mode)
{
    s_mode = (s_mode == mode) ? -1 : mode;
    heater_apply();
    btn_color();
}

/* ══════ 事件接口(events_init.c 调用) ══════ */

void heater_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.Heater, LV_OBJ_FLAG_SCROLLABLE);
    heater_apply();
    btn_color();

    /* 按钮按下反馈: 50% 透明, 每个按钮+配图各一组 */
    {
        lv_obj_t *b[] = {
            guider_ui.Heater_HeatHighBtn,  guider_ui.Heater_HeatHighImg,
            guider_ui.Heater_HeatLowBtn,   guider_ui.Heater_HeatLowImg,
            guider_ui.Heater_VentilateBtn, guider_ui.Heater_VentilateImg,
            guider_ui.Heater_WindBtn,      guider_ui.Heater_WindImg,
            guider_ui.Heater_LightBtn,     guider_ui.Heater_LightOnImg,
            guider_ui.Heater_IdleBtn,      guider_ui.Heater_IdleImg,
        };
        for (uint8_t i = 0; i < 12; i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

/* 照明: 独立开关, 不影响模式 */
void heater_on_light_click(void)
{
    s_light = !s_light;
    heater_apply();
    btn_color();
}

void heater_on_high_click(void)      { mode_click(1); }
void heater_on_low_click(void)       { mode_click(2); }
void heater_on_ventilate_click(void) { mode_click(3); }
void heater_on_wind_click(void)      { mode_click(4); }
void heater_on_idle_click(void)      { mode_click(5); }
