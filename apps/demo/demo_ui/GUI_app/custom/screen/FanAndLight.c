#include "lvgl.h"
#include "gui_guider.h"
#include "hw_cloud_task.h"
#include "HWDataAccess.h"
#include "FanAndLight.h"

#define FAN_TIMER_MS    30         //MS milliseconds

static const float s_speed_rps[] = {0.25f, 0.5f, 0.75f, 1.0f};  //RPS rotations per second, per speed index

/* 供管理屏取当前档位转速(单一数据源, 转速同步) */
float fanlight_speed_rps(void)
{
    uint8_t speed = HWInterface.FanAndLight.speed;
    if (speed > 3) speed = 3;
    return s_speed_rps[speed];
}

static bool        s_power;       /* master power */
static bool        s_fan_on;      /* fan switch */
static bool        s_light_on;    /* light switch */
static uint8_t     s_speed;       /* fan speed index 0..3 */
static lv_timer_t *s_fan_timer;   /* rotation timer */
static int16_t     s_fan_angle;   /* current angle in 0.1° */
static int16_t     s_fan_step;    /* angle step per tick in 0.1° */

static void fan_rotate_cb(lv_timer_t *timer);

/* 组内只显 index, 其余隐藏(同 AC 模式) */
static void show_only(lv_obj_t **group, uint8_t count, uint8_t index)
{
    for (uint8_t i = 0; i < count; i++) {
        if (!lv_obj_is_valid(group[i])) continue;
        if (i == index) lv_obj_clear_flag(group[i], LV_OBJ_FLAG_HIDDEN);
        else           lv_obj_add_flag (group[i], LV_OBJ_FLAG_HIDDEN);
    }
}

/* 条件满足时跑 timer; 否则停 */
static void apply_fan_speed(void)
{
    bool running = s_power && s_fan_on;
    if (running) {
        s_fan_step = (int16_t)(s_speed_rps[s_speed] * 3600.0f * FAN_TIMER_MS / 1000.0f);
        if (!s_fan_timer) s_fan_timer = lv_timer_create(fan_rotate_cb, FAN_TIMER_MS, NULL);
    } else {
        if (s_fan_timer) { lv_timer_del(s_fan_timer); s_fan_timer = NULL; }
    }
}

/* 刷新全部 UI: cont_1 遮罩 + 层级 + 4 组叠图 */
static void apply_ui_refresh(void)
{
    lv_obj_t *fan_switch[2] = { guider_ui.FanAndLight_Fan_off, guider_ui.FanAndLight_Fan_on };
    show_only(fan_switch, 2, s_fan_on ? 1 : 0);

    lv_obj_t *speed[4] = { guider_ui.FanAndLight_FanSpeed1, guider_ui.FanAndLight_FanSpeed2,
                           guider_ui.FanAndLight_FanSpeed3, guider_ui.FanAndLight_FanSpeed4 };
    show_only(speed, 4, s_speed);

    lv_obj_t *light_switch[2] = { guider_ui.FanAndLight_fLight_off, guider_ui.FanAndLight_fLight_on };
    show_only(light_switch, 2, s_light_on ? 1 : 0);

    bool bulb_on = s_power && s_light_on;
    lv_obj_t *bulb[2] = { guider_ui.FanAndLight_FLightOffImg, guider_ui.FanAndLight_FLightOnImg };
    show_only(bulb, 2, bulb_on ? 1 : 0);

    if (!s_power) {
        /* 关机: cont_1 变暗置顶, 但总开关要比它更上面才能点到 */
        lv_obj_set_style_bg_opa(guider_ui.FanAndLight_cont_1, 162, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.FanAndLight_cont_1);
        lv_obj_move_foreground(guider_ui.FanAndLight_imgbtn_1);
    } else if (!s_fan_on) {
        /* 风扇关: 总开关+风扇开关+调速+灯光开关全置顶 */
        lv_obj_set_style_bg_opa(guider_ui.FanAndLight_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.FanAndLight_imgbtn_1);
        lv_obj_move_foreground(guider_ui.FanAndLight_Fan_off);
        lv_obj_move_foreground(guider_ui.FanAndLight_Fan_on);
        lv_obj_move_foreground(guider_ui.FanAndLight_FanSpeed1);
        lv_obj_move_foreground(guider_ui.FanAndLight_FanSpeed2);
        lv_obj_move_foreground(guider_ui.FanAndLight_FanSpeed3);
        lv_obj_move_foreground(guider_ui.FanAndLight_FanSpeed4);
        lv_obj_move_foreground(guider_ui.FanAndLight_fLight_off);
        lv_obj_move_foreground(guider_ui.FanAndLight_fLight_on);
    } else {
        /* 正常运行: cont_1 垫底 */
        lv_obj_set_style_bg_opa(guider_ui.FanAndLight_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_background(guider_ui.FanAndLight_cont_1);
    }
}

static void fan_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *fan = guider_ui.FanAndLight_fan;
    if (!lv_obj_is_valid(fan)) return;
    s_fan_angle += s_fan_step;
    if (s_fan_angle >= 3600) s_fan_angle -= 3600;
    lv_img_set_angle(fan, s_fan_angle);
}

static void fanlight_on_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    if (s_fan_timer) { lv_timer_del(s_fan_timer); s_fan_timer = NULL; }
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void fanlight_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.FanAndLight, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.FanAndLight, fanlight_on_screen_delete, LV_EVENT_DELETE, NULL);

    /* 从中间层读状态 */
    s_power    = HWInterface.FanAndLight.power;
    s_fan_on   = HWInterface.FanAndLight.fan_on;
    s_light_on = HWInterface.FanAndLight.light_on;
    s_speed    = HWInterface.FanAndLight.speed;

    /* 总开关按钮勾选态跟随 power(管理屏开了风扇/灯→这里也显示开) */
    if (s_power) lv_obj_add_state  (guider_ui.FanAndLight_imgbtn_1, LV_STATE_CHECKED);
    else         lv_obj_clear_state(guider_ui.FanAndLight_imgbtn_1, LV_STATE_CHECKED);

    apply_fan_speed();
    apply_ui_refresh();

    /* 按下反馈 */
    lv_obj_set_style_img_opa(guider_ui.FanAndLight_imgbtn_1, 100, LV_PART_MAIN | LV_STATE_PRESSED);
}

void fanlight_on_power_toggle(lv_event_t *event)
{
    s_power = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    HWInterface.FanAndLight.power = s_power;
    HWInterface.FanAndLight.SetPower(s_power);
    HWInterface.FanAndLight.Apply();
    apply_fan_speed();
    apply_ui_refresh();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_FANLIGHT_POWER, .on = s_power });
}

void fanlight_on_fan_switch_toggle(lv_event_t *event)
{
    lv_obj_t *target = lv_event_get_target(event);
    s_fan_on = (target == guider_ui.FanAndLight_Fan_off);   /* 点到 off → 切为 on */
    HWInterface.FanAndLight.fan_on = s_fan_on;
    HWInterface.FanAndLight.SetFan(s_fan_on);
    HWInterface.FanAndLight.Apply();
    apply_fan_speed();
    apply_ui_refresh();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_FANLIGHT_FAN, .on = s_fan_on, .val = s_speed });
}

void fanlight_on_speed_click(void)
{
    s_speed = (s_speed + 1) % 4;
    HWInterface.FanAndLight.speed = s_speed;
    HWInterface.FanAndLight.SetSpeed(s_speed);
    HWInterface.FanAndLight.Apply();
    apply_fan_speed();
    apply_ui_refresh();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_FANLIGHT_SPEED, .val = s_speed });
}

void fanlight_on_light_switch_toggle(lv_event_t *event)
{
    lv_obj_t *target = lv_event_get_target(event);
    s_light_on = (target == guider_ui.FanAndLight_fLight_off);  /* 点到 off → 切为 on */
    HWInterface.FanAndLight.light_on = s_light_on;
    HWInterface.FanAndLight.SetLight(s_light_on);
    HWInterface.FanAndLight.Apply();
    apply_ui_refresh();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_FANLIGHT_LIGHT, .on = s_light_on });
}
