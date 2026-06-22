#include "lvgl.h"
#include "gui_guider.h"
#include "hw_cloud_task.h"
#include "HWDataAccess.h"
#include "AirCondition.h"

/* 电源/模式存中间层(管理屏共享) */
#define s_power  HWInterface.AirCondition.power   /* 电源开关(默认关) */
#define s_mode   HWInterface.AirCondition.mode    /* 0制冷 1制热 2送风 3除湿 */

/* 状态(切屏保留) */
static uint8_t     s_speed;     /* 0/1/2 档, 3=自动 */
static uint8_t     s_wind;      /* 当前风速图 AcSpd 索引 0..2 */
static lv_timer_t *s_auto_tmr;  /* 自动档每秒循环, 只在本屏存活期跑 */
#define AUTO_MS  1000

/* 组内只显 idx 一张, 其余隐藏(隐藏的图不可点, 露出的那张即点击目标) */
static void show_only(lv_obj_t **imgs, uint8_t n, uint8_t idx)
{
    for (uint8_t i = 0; i < n; i++) {
        if (!lv_obj_is_valid(imgs[i])) continue;
        if (i == idx) lv_obj_clear_flag(imgs[i], LV_OBJ_FLAG_HIDDEN);
        else          lv_obj_add_flag (imgs[i], LV_OBJ_FLAG_HIDDEN);
    }
}

static void wind_show(uint8_t idx)
{
    lv_obj_t *w[3] = { guider_ui.AirCondition_AcSpd1, guider_ui.AirCondition_AcSpd2,
                       guider_ui.AirCondition_AcSpd3 };
    show_only(w, 3, idx);
}

static void auto_cb(lv_timer_t *t)
{
    LV_UNUSED(t);
    if (!lv_obj_is_valid(guider_ui.AirCondition_AcSpd1)) return;   /* 兜底 */
    s_wind = (s_wind + 1) % 3;
    wind_show(s_wind);
}

/* 选当前风速图(HIDDEN); 自动档 timer 仅"开机+自动档"时跑 */
static void aircon_apply_wind(void)
{
    if (s_speed != 3) s_wind = s_speed;
    if (s_power && s_speed == 3) {
        if (!s_auto_tmr) s_auto_tmr = lv_timer_create(auto_cb, AUTO_MS, NULL);
    } else {
        if (s_auto_tmr) { lv_timer_del(s_auto_tmr); s_auto_tmr = NULL; }
    }
    wind_show(s_wind);
}

/* 电源刷新(仿色温灯): 关→cont_1 变暗 + AcSpd 透明度归0; 开→恢复 */
static void aircon_refresh(void)
{
    if (s_power) lv_obj_add_state  (guider_ui.AirCondition_ACBtn, LV_STATE_CHECKED);
    else         lv_obj_clear_state(guider_ui.AirCondition_ACBtn, LV_STATE_CHECKED);

    if (s_power) {
        lv_obj_set_style_bg_opa(guider_ui.AirCondition_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_background(guider_ui.AirCondition_cont_1);
    } else {
        lv_obj_set_style_bg_opa(guider_ui.AirCondition_cont_1, 162, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.AirCondition_cont_1);
        lv_obj_move_foreground(guider_ui.AirCondition_ACBtn);   /* 电源键浮在遮罩上仍可点 */
    }
    lv_opa_t o = s_power ? LV_OPA_COVER : LV_OPA_TRANSP;
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd1, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd2, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd3, o, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* 本屏不在 scr_guard 列表里, 自己挂删除回调: 屏一删就干掉 timer, 防野指针 */
static void scr_del_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    if (s_auto_tmr) { lv_timer_del(s_auto_tmr); s_auto_tmr = NULL; }
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void aircon_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.AirCondition, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.AirCondition, scr_del_cb, LV_EVENT_DELETE, NULL);

    lv_obj_t *mode[4]  = { guider_ui.AirCondition_AcCool,   guider_ui.AirCondition_ACHot,
                           guider_ui.AirCondition_ACFan,    guider_ui.AirCondition_ACDry };
    lv_obj_t *speed[4] = { guider_ui.AirCondition_ACSpeed1, guider_ui.AirCondition_ACSpeed2,
                           guider_ui.AirCondition_ACSpeed3, guider_ui.AirCondition_ACSpeedAuto };
    show_only(mode,  4, s_mode);
    show_only(speed, 4, s_speed);
    aircon_apply_wind();
    aircon_refresh();
}

/* 电源键: 逻辑同色温灯开关, 关时整屏变暗 + 风速图透明 */
void aircon_on_power_toggle(lv_event_t *e)
{
    s_power = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    aircon_apply_wind();
    aircon_refresh();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_SWITCH, .on = s_power });
}

/* 左按钮: 制冷→制热→送风→除湿 循环 */
void aircon_on_mode_click(void)
{
    s_mode = (s_mode + 1) % 4;
    lv_obj_t *mode[4] = { guider_ui.AirCondition_AcCool, guider_ui.AirCondition_ACHot,
                          guider_ui.AirCondition_ACFan,  guider_ui.AirCondition_ACDry };
    show_only(mode, 4, s_mode);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_MODE, .val = s_mode });
}

/* 右按钮: 1档→2档→3档→自动 循环, 同步刷新风速显示图 */
void aircon_on_speed_click(void)
{
    s_speed = (s_speed + 1) % 4;
    lv_obj_t *speed[4] = { guider_ui.AirCondition_ACSpeed1, guider_ui.AirCondition_ACSpeed2,
                           guider_ui.AirCondition_ACSpeed3, guider_ui.AirCondition_ACSpeedAuto };
    show_only(speed, 4, s_speed);
    aircon_apply_wind();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_SPEED, .val = s_speed });
}
