#include "lvgl.h"
#include "gui_guider.h"
#include "Home.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "FanAndLight.h"
#include "device_management.h"

/* ── 首页按钮按下/松开反馈 ── */
static void btn_pressed_cb(lv_event_t *e)
{
    lv_obj_set_style_bg_opa(lv_event_get_target(e), 128, LV_PART_MAIN | LV_STATE_DEFAULT);
}
static void btn_released_cb(lv_event_t *e)
{
    lv_obj_set_style_bg_opa(lv_event_get_target(e), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* ── 灯开关槽位 ── */
typedef struct {
    lv_obj_t *sw;
    lv_obj_t *on;
    lv_obj_t *off;
    uint8_t (*is_on)(void);
    void    (*set_on)(bool on);
} DevSlot;

static uint8_t ct_is_on(void)        { return HWInterface.LightCT.switch_status; }
static void    ct_set_on(bool on)    { HWInterface.LightCT.SetOnOff(on); }
static uint8_t led_is_on(void)       { return HWInterface.LEDStrip.switch_status; }
static void    led_set_on(bool on)   { HWInterface.LEDStrip.SetOnOff(on); }
static uint8_t mag_is_on(void)       { return HWInterface.MagLight.switch_status; }
static void    mag_set_on(bool on)   { HWInterface.MagLight.SetOnOff(on); }
static uint8_t rgb_is_on(void)       { return HWInterface.RGBLight.switch_status; }
static void    rgb_set_on(bool on)   { HWInterface.RGBLight.SetOnOff(on); }

static DevSlot g_slots[DEV_SLOT_COUNT] = {
    [DEV_SLOT_CT_LIGHT] = { .is_on = ct_is_on,  .set_on = ct_set_on  },
    [DEV_SLOT_LEDSTRIP] = { .is_on = led_is_on, .set_on = led_set_on },
    [DEV_SLOT_MAGLIGHT] = { .is_on = mag_is_on, .set_on = mag_set_on },
    [DEV_SLOT_RGBLIGHT] = { .is_on = rgb_is_on, .set_on = rgb_set_on },
};

static void slot_bind(DevSlot *slot, lv_obj_t *sw, lv_obj_t *on, lv_obj_t *off)
{
    slot->sw  = sw;
    slot->on  = on;
    slot->off = off;
}

static void slot_refresh(DevSlot *slot)
{
    if (!slot || !slot->sw) return;
    bool on = slot->is_on();
    if (on) lv_obj_add_state(slot->sw, LV_STATE_CHECKED);
    else    lv_obj_clear_state(slot->sw, LV_STATE_CHECKED);
    if (slot->on)  lv_obj_set_style_img_opa(slot->on,  on ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (slot->off) lv_obj_set_style_img_opa(slot->off, on ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* ── 窗帘行 ── */
typedef struct {
    lv_obj_t *on;
    lv_obj_t *off;
    uint8_t   idx;
} CurtainRow;

static CurtainRow g_curtain_rows[CURTAIN_IDX_COUNT];

static void curtain_refresh(CurtainRow *row)
{
    if (!row->on) return;
    bool open = curtain_motion_target(row->idx) > 0;
    lv_obj_set_style_img_opa(row->on,  open ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(row->off, open ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static lv_obj_t *s_dr_down_img;
static lv_obj_t *s_dr_up_img;
static void dryrack_img_refresh(void)
{
    if (!s_dr_down_img) return;
    bool down = curtain_motion_target(MOTION_IDX_DRYRACK) > 0;
    lv_obj_set_style_img_opa(s_dr_down_img, down ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(s_dr_up_img,   down ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* ── 音乐 ── */
#define MUSIC_TIMER_MS  30
#define MUSIC_RPS       0.5f
static lv_timer_t *s_music_timer;
static int16_t     s_music_angle;
static void music_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *disc = guider_ui.ui_home_screen_img_35;   /* small_disc 唱片碟 */
    if (!lv_obj_is_valid(disc)) return;
    s_music_angle += (int16_t)(MUSIC_RPS * 3600.0f * MUSIC_TIMER_MS / 1000.0f);
    if (s_music_angle >= 3600) s_music_angle -= 3600;
    lv_img_set_angle(disc, s_music_angle);
}
static void music_apply(void)
{
    bool playing = HWInterface.Music.playing;
    if (playing) lv_obj_add_state  (guider_ui.ui_home_screen_imgbtn_4, LV_STATE_CHECKED);
    else         lv_obj_clear_state(guider_ui.ui_home_screen_imgbtn_4, LV_STATE_CHECKED);
    if (playing) {
        if (!s_music_timer) s_music_timer = lv_timer_create(music_rotate_cb, MUSIC_TIMER_MS, NULL);
    } else {
        if (s_music_timer) { lv_timer_del(s_music_timer); s_music_timer = NULL; }
    }
}

/* ── 风扇灯 ── */
#define FAN_TIMER_MS  30
static lv_timer_t *s_fan_timer;
static int16_t     s_fan_angle;
static void fan_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *fan_on  = guider_ui.ui_home_screen_img_29;   /* sFanAndLTon 灯亮+转 */
    lv_obj_t *fan_off = guider_ui.ui_home_screen_img_28;   /* sFanAndLToff 灯灭+转 */
    s_fan_angle += (int16_t)(fanlight_speed_rps() * 3600.0f * FAN_TIMER_MS / 1000.0f);
    if (s_fan_angle >= 3600) s_fan_angle -= 3600;
    if (lv_obj_is_valid(fan_on))  lv_img_set_angle(fan_on,  s_fan_angle);
    if (lv_obj_is_valid(fan_off)) lv_img_set_angle(fan_off, s_fan_angle);
}
static void fanlight_apply(void)
{
    bool power = HWInterface.FanAndLight.power;
    bool light = power && HWInterface.FanAndLight.light_on;
    bool fan   = power && HWInterface.FanAndLight.fan_on;
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_29, light ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_28, light ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (light) lv_obj_add_state  (guider_ui.ui_home_screen_imgbtn_2, LV_STATE_CHECKED);
    else       lv_obj_clear_state(guider_ui.ui_home_screen_imgbtn_2, LV_STATE_CHECKED);
    if (fan)   lv_obj_add_state  (guider_ui.ui_home_screen_imgbtn_3, LV_STATE_CHECKED);
    else       lv_obj_clear_state(guider_ui.ui_home_screen_imgbtn_3, LV_STATE_CHECKED);
    if (fan) {
        if (!s_fan_timer) s_fan_timer = lv_timer_create(fan_rotate_cb, FAN_TIMER_MS, NULL);
    } else {
        if (s_fan_timer) { lv_timer_del(s_fan_timer); s_fan_timer = NULL; }
    }
}

/* ── 浴霸 ── */
static void heater_apply(void)
{
    lv_obj_t *modeimg[6] = {
        NULL,
        guider_ui.ui_home_screen_img_24,   /* 1 暖风高 sHeatMode */
        guider_ui.ui_home_screen_img_25,   /* 2 暖风低 sLowHeatMode */
        guider_ui.ui_home_screen_img_23,   /* 3 换气 sventilate */
        guider_ui.ui_home_screen_img_22,   /* 4 吹风 sFanMode */
        guider_ui.ui_home_screen_img_20,   /* 5 待机 sIdleMode */
    };
    lv_obj_move_foreground(guider_ui.ui_home_screen_img_21);   /* 设备底 sDev */
    lv_obj_move_foreground(guider_ui.ui_home_screen_img_20);   /* 待机模式 */
    int8_t mode = HWInterface.Heater.mode;
    if (mode >= 1 && mode <= 5) lv_obj_move_foreground(modeimg[mode]);
    if (HWInterface.Heater.light) {
        lv_obj_clear_flag(guider_ui.ui_home_screen_img_26, LV_OBJ_FLAG_HIDDEN);   /* 灯光 sHlight */
        lv_obj_move_foreground(guider_ui.ui_home_screen_img_26);
        lv_obj_add_state(guider_ui.ui_home_screen_imgbtn_1, LV_STATE_CHECKED);
    } else {
        lv_obj_add_flag(guider_ui.ui_home_screen_img_26, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(guider_ui.ui_home_screen_imgbtn_1, LV_STATE_CHECKED);
    }
}

/* ── 屏删除: 停 timer 防野指针 ── */
static void home_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    if (s_music_timer) { lv_timer_del(s_music_timer); s_music_timer = NULL; }
    if (s_fan_timer)   { lv_timer_del(s_fan_timer);   s_fan_timer   = NULL; }
}

/* ── 非对称热区 ── */
static void hit_test_bl(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_hit_test_info_t *info = lv_event_get_hit_test_info(e);
    lv_area_t a;
    lv_obj_get_coords(obj, &a);
    a.x1 -= 40; a.x2 += 40;
    a.y1 -= 40; a.y2 += 80;
    const lv_point_t *p = info->point;
    if (p->x < a.x1 || p->x > a.x2 || p->y < a.y1 || p->y > a.y2) info->res = false;
}
static void set_hit_area_bl(lv_obj_t *obj)
{
    if (!obj) return;
    lv_obj_set_ext_click_area(obj, 100);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(obj, hit_test_bl, LV_EVENT_HIT_TEST, NULL);
}

/* ═══════════ 首页 + 设备页合并加载 ═══════════ */
void home_on_screen_load(void)
{
    /* 清各 tile 自身滚动, 让横滑手势直达 tileview 切页(防 tile_0 大按键区吞手势)。
     * 纵向看设备卡片由 tabview 的 tab page 自己滚, 不受影响。 */
    {
        lv_obj_t *tiles[] = { guider_ui.ui_home_screen_tileview_1_tile_0,
                              guider_ui.ui_home_screen_tileview_1_tile_1,
                              guider_ui.ui_home_screen_tileview_1_tile_2,
                              guider_ui.ui_home_screen_tileview_1_tile_3 };
        for (uint8_t i = 0; i < 4; i++)
            if (lv_obj_is_valid(tiles[i])) lv_obj_clear_flag(tiles[i], LV_OBJ_FLAG_SCROLLABLE);
    }

    /* ── 首页: 清大图 CLICKABLE ── */
    #define SAFE_CLEAR(obj, flag) if (lv_obj_is_valid(guider_ui.obj)) lv_obj_clear_flag(guider_ui.obj, flag)
    SAFE_CLEAR(ui_home_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_6, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_MainSetImg, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *btns[] = { guider_ui.ui_home_screen_btn_1,
                         guider_ui.ui_home_screen_btn_2,
                         guider_ui.ui_home_screen_btn_7 };
    for (uint8_t i = 0; i < 3; i++) {
        if (!lv_obj_is_valid(btns[i])) continue;
        lv_obj_add_event_cb(btns[i], btn_pressed_cb,  LV_EVENT_PRESSED,  NULL);
        lv_obj_add_event_cb(btns[i], btn_released_cb, LV_EVENT_RELEASED, NULL);
    }

    /* ── 设备页: 绑定控件 + 刷状态 ── */
    lv_obj_add_event_cb(guider_ui.ui_home_screen, home_screen_delete, LV_EVENT_DELETE, NULL);

    /* 灯槽位绑定: sw=imgbtn, on/off=状态图(需要你在 GUI-Guider 里确认控件名后更新) */
    slot_bind(&g_slots[DEV_SLOT_CT_LIGHT],
              guider_ui.ui_home_screen_imgbtn_9,    /* 色温灯开关 */
              guider_ui.ui_home_screen_img_61,       /* sdev_on */
              guider_ui.ui_home_screen_img_60);      /* sdev_off */
    slot_bind(&g_slots[DEV_SLOT_LEDSTRIP],
              guider_ui.ui_home_screen_imgbtn_8,     /* 灯带开关 */
              guider_ui.ui_home_screen_img_59,       /* sLSOn */
              guider_ui.ui_home_screen_img_58);      /* sLSOff */
    slot_bind(&g_slots[DEV_SLOT_MAGLIGHT],
              guider_ui.ui_home_screen_imgbtn_7,     /* 磁吸灯开关 */
              guider_ui.ui_home_screen_img_57,       /* sMLOn */
              guider_ui.ui_home_screen_img_56);      /* sMLOff */
    slot_bind(&g_slots[DEV_SLOT_RGBLIGHT],
              guider_ui.ui_home_screen_imgbtn_6,     /* 彩色灯开关 */
              guider_ui.ui_home_screen_img_55,       /* sRGBLOn */
              guider_ui.ui_home_screen_img_54);      /* sRGBLOff */

    /* 开关热区 + 按下反馈 */
    set_hit_area_bl(guider_ui.ui_home_screen_imgbtn_9);
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_9, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.ui_home_screen_imgbtn_8);
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_8, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.ui_home_screen_imgbtn_7);
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_7, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.ui_home_screen_imgbtn_6);
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_6, 128, LV_PART_MAIN | LV_STATE_PRESSED);

    /* 窗帘/晾衣机/风扇灯/浴霸 按钮热区 */
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_50, 15);   /* 布帘开 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_50, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_51, 15);   /* 布帘合 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_51, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_47, 15);   /* 纱帘开 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_47, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_46, 15);   /* 纱帘合 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_46, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_42, 15);   /* 卷帘开 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_42, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_43, 15);   /* 卷帘合 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_43, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_38, 15);   /* 梦幻帘开 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_38, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_39, 15);   /* 梦幻帘合 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_39, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_30, 15);   /* 晾衣机上 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_30, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_31, 15);   /* 晾衣机下 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_31, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_imgbtn_2, 15); /* 风扇灯-灯 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_imgbtn_3, 15); /* 风扇灯-风扇 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_3, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_imgbtn_1, 15); /* 浴霸灯 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.ui_home_screen_img_27, 15);   /* 浴霸待机 */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_27, 128, LV_PART_MAIN | LV_STATE_PRESSED);

    /* 刷灯槽位 */
    for (uint8_t i = 0; i < DEV_SLOT_COUNT; i++) slot_refresh(&g_slots[i]);

    /* 窗帘行 on/off 状态图 */
    g_curtain_rows[CURTAIN_IDX_FABRIC]    = (CurtainRow){ guider_ui.ui_home_screen_img_53, guider_ui.ui_home_screen_img_52, CURTAIN_IDX_FABRIC };    /* sFCOn/Off */
    g_curtain_rows[CURTAIN_IDX_SHEERS]    = (CurtainRow){ guider_ui.ui_home_screen_img_49, guider_ui.ui_home_screen_img_48, CURTAIN_IDX_SHEERS };    /* sheers on/off */
    g_curtain_rows[CURTAIN_IDX_ROLLBLIND] = (CurtainRow){ guider_ui.ui_home_screen_img_45, guider_ui.ui_home_screen_img_44, CURTAIN_IDX_ROLLBLIND }; /* sRBOn/Off */
    g_curtain_rows[CURTAIN_IDX_DREAM]     = (CurtainRow){ guider_ui.ui_home_screen_img_41, guider_ui.ui_home_screen_img_40, CURTAIN_IDX_DREAM };     /* sDreamOn/Off */
    for (uint8_t i = 0; i < CURTAIN_IDX_COUNT; i++) curtain_refresh(&g_curtain_rows[i]);

    /* 晾衣机状态图 sDryRackOn(放下)/Off(收起) */
    s_dr_down_img = guider_ui.ui_home_screen_img_33;
    s_dr_up_img   = guider_ui.ui_home_screen_img_32;
    dryrack_img_refresh();

    /* 晾衣机照明: 只显示, 跟随子界面 HWInterface.DryRack.light */
    lv_obj_set_style_img_opa(guider_ui.ui_home_screen_img_19,   /* sDryRackL */
                             HWInterface.DryRack.light ? LV_OPA_COVER : LV_OPA_TRANSP,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_move_foreground(guider_ui.ui_home_screen_img_19);

    /* 音乐 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_35, 25, 25);   /* 唱片碟 51x51 */
    music_apply();

    /* 风扇灯 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_29, 30, 30);   /* 灯亮+扇叶 60x60 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_28, 30, 30);   /* 灯灭+扇叶 */
    fanlight_apply();

    /* 浴霸 */
    heater_apply();
}

/* ═══════════ 对外接口(供 events_init 调用) ═══════════ */

static void slot_toggle(uint8_t idx)
{
    DevSlot *slot = &g_slots[idx];
    if (!slot->sw) return;
    bool on = lv_obj_has_state(slot->sw, LV_STATE_CHECKED);
    slot->set_on(on);
    slot_refresh(slot);
}

void dev_mgmt_ct_on_toggle(void)     { slot_toggle(DEV_SLOT_CT_LIGHT); }
void dev_mgmt_led_on_toggle(void)    { slot_toggle(DEV_SLOT_LEDSTRIP); }
void dev_mgmt_mag_on_toggle(void)    { slot_toggle(DEV_SLOT_MAGLIGHT); }
void dev_mgmt_rgb_on_toggle(void)    { slot_toggle(DEV_SLOT_RGBLIGHT); }

static void curtain_move(uint8_t idx, uint16_t target)
{
    curtain_motion_start(idx, target);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_POS, .idx = idx, .val = target });
    curtain_refresh(&g_curtain_rows[idx]);
}

void dev_mgmt_fabric_open(void)      { curtain_move(CURTAIN_IDX_FABRIC,    CURTAIN_POS_MAX); }
void dev_mgmt_fabric_close(void)     { curtain_move(CURTAIN_IDX_FABRIC,    CURTAIN_POS_MIN); }
void dev_mgmt_sheers_open(void)      { curtain_move(CURTAIN_IDX_SHEERS,    CURTAIN_POS_MAX); }
void dev_mgmt_sheers_close(void)     { curtain_move(CURTAIN_IDX_SHEERS,    CURTAIN_POS_MIN); }
void dev_mgmt_rollblind_open(void)   { curtain_move(CURTAIN_IDX_ROLLBLIND, CURTAIN_POS_MAX); }
void dev_mgmt_rollblind_close(void)  { curtain_move(CURTAIN_IDX_ROLLBLIND, CURTAIN_POS_MIN); }
void dev_mgmt_dream_open(void)       { curtain_move(CURTAIN_IDX_DREAM,     CURTAIN_POS_MAX); }
void dev_mgmt_dream_close(void)      { curtain_move(CURTAIN_IDX_DREAM,     CURTAIN_POS_MIN); }

void dev_mgmt_dryrack_down(void)
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 100);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_POS, .val = 100 });
    dryrack_img_refresh();
}
void dev_mgmt_dryrack_up(void)
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 0);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_POS, .val = 0 });
    dryrack_img_refresh();
}

void dev_mgmt_music_toggle(void)
{
    HWInterface.Music.playing = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_4, LV_STATE_CHECKED);
    music_apply();
}

void dev_mgmt_fanlight_light_toggle(void)
{
    HWInterface.FanAndLight.light_on = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_2, LV_STATE_CHECKED);
    HWInterface.FanAndLight.power = HWInterface.FanAndLight.fan_on || HWInterface.FanAndLight.light_on;
    fanlight_apply();
}

void dev_mgmt_fanlight_fan_toggle(void)
{
    HWInterface.FanAndLight.fan_on = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_3, LV_STATE_CHECKED);
    HWInterface.FanAndLight.power = HWInterface.FanAndLight.fan_on || HWInterface.FanAndLight.light_on;
    fanlight_apply();
}

void dev_mgmt_heater_light_toggle(void)
{
    HWInterface.Heater.light = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_1, LV_STATE_CHECKED);
    heater_apply();
}

void dev_mgmt_heater_idle(void)
{
    HWInterface.Heater.mode = (HWInterface.Heater.mode == 5) ? -1 : 5;
    heater_apply();
}

/* 下拉面板空桩 */
void home_btn_4_clicked(lv_event_t *e) { LV_UNUSED(e); }
void home_btn_6_clicked(lv_event_t *e) { LV_UNUSED(e); }
