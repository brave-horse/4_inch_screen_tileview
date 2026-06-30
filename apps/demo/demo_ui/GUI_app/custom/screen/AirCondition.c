#include "lvgl.h"
#include "gui_guider.h"
#include "hw_cloud_task.h"
#include "HWDataAccess.h"
#include "AirCondition.h"

/* 电源/模式存中间层(管理屏共享)
 * mode 顺序(=GUI-Guider 控件顺序): 0制冷 1制热 2除湿 3送风 */
#define s_power  HWInterface.AirCondition.power
#define s_mode   HWInterface.AirCondition.mode

/* ── 滚轮 UI(新增,不动下面老三组开关) ── */
typedef struct {
    lv_obj_t *roller;
    lv_obj_t *wind_icon;
    lv_obj_t *dev_icon;
} RollerUI;

extern const lv_font_t lv_font_MiSansNormal_30;
#define IMG(p) "0:img/device/airCond/" p

/* ── 状态(切屏保留; 温度和模式从中间层读) ── */
static uint8_t     s_speed;
static uint8_t     s_temp;
static uint8_t     s_wind;
static lv_timer_t *s_auto_tmr;
static RollerUI    s_rui;
#define AUTO_MS  1000

/* ── 前向声明 ── */
static void aircond_set_mode(void);
static void aircond_set_speed(void);
static void aircond_set_power(void);
static void aircon_apply_wind(void);
static void dev_page_sync(void);

/* ══════ 老三组开关(不动, 原有逻辑) ══════ */

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
    if (!lv_obj_is_valid(guider_ui.AirCondition_AcSpd1)) return;
    s_wind = (s_wind + 1) % 3;
    wind_show(s_wind);
}

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
        lv_obj_move_foreground(guider_ui.AirCondition_ACBtn);
    }
    lv_opa_t o = s_power ? LV_OPA_COVER : LV_OPA_TRANSP;
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd1, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd2, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.AirCondition_AcSpd3, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    aircond_set_power();   /* 滚轮 wind/dev icon 同步 */
}

static void scr_del_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    if (s_auto_tmr) { lv_timer_del(s_auto_tmr); s_auto_tmr = NULL; }
}

/* ══════ 滚轮(新增, 温度+出风图+设备图) ══════ */

static const char *s_temp_opts = "16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32";

static void aircond_set_mode(void)
{
    if (!lv_obj_is_valid(s_rui.roller)) return;
    lv_color_t c;
    if (s_mode == 0) c = lv_palette_main(LV_PALETTE_BLUE);    /* 制冷→蓝 */
    else if (s_mode == 1) c = lv_palette_main(LV_PALETTE_ORANGE); /* 制热→橙 */
    else c = lv_color_white();                                  /* 除湿/送风→白 */
    lv_obj_set_style_text_color(s_rui.roller, c, LV_PART_SELECTED);
}

static void aircond_set_speed(void)
{
    if (!lv_obj_is_valid(s_rui.wind_icon)) return;
    const char *w[3] = { IMG("wind_spd_1.png"), IMG("wind_spd_2.png"), IMG("wind_spd_3.png") };
    lv_img_set_src(s_rui.wind_icon, w[s_wind < 3 ? s_wind : 0]);
}

static void aircond_set_power(void)
{
    if (!lv_obj_is_valid(s_rui.wind_icon)) return;
    lv_opa_t o = s_power ? LV_OPA_COVER : LV_OPA_TRANSP;
    lv_obj_set_style_img_opa(s_rui.wind_icon, o, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (lv_obj_is_valid(s_rui.dev_icon))
        lv_obj_set_style_img_opa(s_rui.dev_icon, o, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void temp_roller_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    s_temp = (uint8_t)(lv_roller_get_selected(s_rui.roller) + 16);
    HWInterface.AirCondition.temperature = s_temp;   /* 同步中间层, 设备页可读 */
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_TEMP, .val = s_temp });
    dev_page_sync();
}

/* ══════ 设备页同步 ══════ */

static void dev_page_sync(void)
{
    if (lv_obj_is_valid(guider_ui.ui_home_screen_label_27))
        lv_label_set_text_fmt(guider_ui.ui_home_screen_label_27, "%d℃", (int)s_temp);

    /* ml 按 mode: 0制冷→24 1制热→23 2除湿→22 3送风→25, [4]=关 */
    lv_obj_t *ml[5] = { guider_ui.ui_home_screen_label_24, guider_ui.ui_home_screen_label_23,
                        guider_ui.ui_home_screen_label_22, guider_ui.ui_home_screen_label_25,
                        guider_ui.ui_home_screen_label_26 };
    if (!s_power) {
        for (uint8_t i = 0; i < 4; i++) if (lv_obj_is_valid(ml[i])) lv_obj_add_flag(ml[i], LV_OBJ_FLAG_HIDDEN);
        if (lv_obj_is_valid(ml[4])) lv_obj_clear_flag(ml[4], LV_OBJ_FLAG_HIDDEN);
    } else {
        if (lv_obj_is_valid(ml[4])) lv_obj_add_flag(ml[4], LV_OBJ_FLAG_HIDDEN);
        for (uint8_t i = 0; i < 4; i++) {
            if (!lv_obj_is_valid(ml[i])) continue;
            if (i == s_mode) lv_obj_clear_flag(ml[i], LV_OBJ_FLAG_HIDDEN);
            else             lv_obj_add_flag(ml[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void aircon_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.AirCondition, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.AirCondition, scr_del_cb, LV_EVENT_DELETE, NULL);

    s_temp = HWInterface.AirCondition.temperature;  /* 从中间层读初始温度 */
    if (s_temp < 16) s_temp = 16;

    /* ── 老三组开关: show_only 初始态(模式顺序: 制冷→制热→除湿→送风) ── */
    {
        lv_obj_t *mode[4]  = { guider_ui.AirCondition_AcCool,   guider_ui.AirCondition_ACHot,
                               guider_ui.AirCondition_ACDry,    guider_ui.AirCondition_ACFan };
        lv_obj_t *speed[4] = { guider_ui.AirCondition_ACSpeed1, guider_ui.AirCondition_ACSpeed2,
                               guider_ui.AirCondition_ACSpeed3, guider_ui.AirCondition_ACSpeedAuto };
        show_only(mode,  4, s_mode);
        show_only(speed, 4, s_speed);
    }
    aircon_apply_wind();

    /* ── 滚轮: roller + wind/dev icon(直接挂屏, 不走容器) ── */
    {
        s_rui.roller = lv_roller_create(guider_ui.AirCondition);
        lv_roller_set_options(s_rui.roller, s_temp_opts, LV_ROLLER_MODE_NORMAL);
        lv_obj_set_size(s_rui.roller, 100, 150);
        lv_obj_set_pos(s_rui.roller, 560, 180);
        lv_obj_set_style_pad_all(s_rui.roller, 0, LV_PART_MAIN);
        lv_obj_set_style_border_width(s_rui.roller, 0, LV_PART_MAIN);
        lv_obj_set_style_bg_color(s_rui.roller, lv_color_make(16, 16, 16), LV_PART_MAIN);
        lv_obj_set_style_text_color(s_rui.roller, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_line_space(s_rui.roller, 50, LV_PART_MAIN);
        lv_obj_set_style_text_font(s_rui.roller, &lv_font_MiSansNormal_18, LV_PART_MAIN);
        lv_obj_set_style_bg_color(s_rui.roller, lv_color_make(60, 60, 60), LV_PART_SELECTED);
        lv_obj_set_style_text_color(s_rui.roller, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_SELECTED);
        lv_obj_set_style_text_font(s_rui.roller, &lv_font_MiSansNormal_30, LV_PART_SELECTED);
        lv_obj_set_style_text_align(s_rui.roller, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED);
        lv_roller_set_selected(s_rui.roller, s_temp - 16, LV_ANIM_OFF);
        lv_obj_add_event_cb(s_rui.roller, temp_roller_cb, LV_EVENT_VALUE_CHANGED, NULL);

        lv_obj_t *unit = lv_label_create(s_rui.roller);
        lv_label_set_text(unit, "℃");
        lv_obj_set_style_text_font(unit, &lv_font_MiSansNormal_30, 0);
        lv_obj_set_style_text_color(unit, lv_color_white(), 0);
        lv_obj_align(unit, LV_ALIGN_CENTER, 35, -5);

        s_rui.wind_icon = lv_img_create(guider_ui.AirCondition);
        lv_img_set_src(s_rui.wind_icon, IMG("wind_spd_1.png"));
        lv_obj_align(s_rui.wind_icon, LV_ALIGN_CENTER, -50, -10);

        s_rui.dev_icon = lv_img_create(guider_ui.AirCondition);
        lv_img_set_src(s_rui.dev_icon, IMG("dev.png"));
        lv_obj_align(s_rui.dev_icon, LV_ALIGN_CENTER, -50, -120);
    }

    aircon_refresh();   /* 在滚轮之后调: 关状态时 cont_1 遮罩在最上, 盖住滚轮+旧控件 */

    /* ── 按钮按下反馈: 老三组(不动) ── */
    {
        lv_obj_t *b[] = { guider_ui.AirCondition_AcCool,   guider_ui.AirCondition_ACHot,
                          guider_ui.AirCondition_ACFan,    guider_ui.AirCondition_ACDry,
                          guider_ui.AirCondition_ACSpeed1, guider_ui.AirCondition_ACSpeed2,
                          guider_ui.AirCondition_ACSpeed3, guider_ui.AirCondition_ACSpeedAuto,
                          guider_ui.AirCondition_ACBtn };
        for (uint8_t i = 0; i < sizeof(b)/sizeof(b[0]); i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }

    dev_page_sync();
}

/* ── 老三组事件(GUI-Guider 已注册, 这里不动签名) ── */

void aircon_on_power_toggle(lv_event_t *e)
{
    s_power = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    aircond_set_power();
    aircon_apply_wind();
    aircon_refresh();
    dev_page_sync();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_SWITCH, .on = s_power });
}

void aircon_on_mode_click(void)
{
    s_mode = (s_mode + 1) % 4;   /* 0制冷→1制热→2除湿→3送风 */
    lv_obj_t *mode[4] = { guider_ui.AirCondition_AcCool, guider_ui.AirCondition_ACHot,
                          guider_ui.AirCondition_ACDry,  guider_ui.AirCondition_ACFan };
    show_only(mode, 4, s_mode);
    aircond_set_mode();
    dev_page_sync();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_MODE, .val = s_mode });
}

void aircon_on_speed_click(void)
{
    s_speed = (s_speed + 1) % 4;
    lv_obj_t *speed[4] = { guider_ui.AirCondition_ACSpeed1, guider_ui.AirCondition_ACSpeed2,
                           guider_ui.AirCondition_ACSpeed3, guider_ui.AirCondition_ACSpeedAuto };
    show_only(speed, 4, s_speed);
    aircond_set_speed();
    aircon_apply_wind();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_AIRCON_SPEED, .val = s_speed });
}
