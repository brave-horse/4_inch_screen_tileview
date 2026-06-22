#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "FanAndLight.h"
#include "device_management.h"

/* ── 单槽位: 开关 imgbtn + 开指示灯 + 关遮罩 ── */
typedef struct {
    lv_obj_t *sw;     /* 开关 imgbtn (CHECKABLE) */
    lv_obj_t *on;     /* 开指示灯(开=COVER, 关=TRANSP) */
    lv_obj_t *off;    /* 关遮罩  (开=TRANSP, 关=COVER) */
    uint8_t (*is_on)(void);
    void    (*set_on)(bool on);
} DevSlot;

/* ═══════════ 各灯回调 ═══════════ */
static uint8_t ct_is_on(void)        { return HWInterface.LightCT.switch_status; }
static void    ct_set_on(bool on)    { HWInterface.LightCT.SetOnOff(on); }
static uint8_t led_is_on(void)       { return HWInterface.LEDStrip.switch_status; }
static void    led_set_on(bool on)   { HWInterface.LEDStrip.SetOnOff(on); }
static uint8_t mag_is_on(void)       { return HWInterface.MagLight.switch_status; }
static void    mag_set_on(bool on)   { HWInterface.MagLight.SetOnOff(on); }
static uint8_t rgb_is_on(void)       { return HWInterface.RGBLight.switch_status; }
static void    rgb_set_on(bool on)   { HWInterface.RGBLight.SetOnOff(on); }

/* ═══════════ 槽位表: 添加新设备只需加一行 ═══════════ */
static DevSlot g_slots[DEV_SLOT_COUNT] = {
    /* sw/on/off 在 load 时填(guider_ui 在 custom_init 之后才有) */
    [DEV_SLOT_CT_LIGHT] = { .is_on = ct_is_on,  .set_on = ct_set_on  },
    [DEV_SLOT_LEDSTRIP] = { .is_on = led_is_on, .set_on = led_set_on },
    [DEV_SLOT_MAGLIGHT] = { .is_on = mag_is_on, .set_on = mag_set_on },
    [DEV_SLOT_RGBLIGHT] = { .is_on = rgb_is_on, .set_on = rgb_set_on },
};

//绑定控件
static void slot_bind(DevSlot *slot,
                      lv_obj_t *sw, lv_obj_t *on, lv_obj_t *off)
{
    slot->sw  = sw;
    slot->on  = on;
    slot->off = off;
}

//访问中间层同步ui控件
static void slot_refresh(DevSlot *slot)
{
    if (!slot || !slot->sw) return;
    bool on = slot->is_on();

    if (on) lv_obj_add_state(slot->sw, LV_STATE_CHECKED);
    else    lv_obj_clear_state(slot->sw, LV_STATE_CHECKED);

    if (slot->on)  lv_obj_set_style_img_opa(slot->on,
                    on ? LV_OPA_COVER : LV_OPA_TRANSP,
                    LV_PART_MAIN | LV_STATE_DEFAULT);
    if (slot->off) lv_obj_set_style_img_opa(slot->off,
                    on ? LV_OPA_TRANSP : LV_OPA_COVER,
                    LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* ═══════════ 窗帘行: 开/关按钮 + 开关状态图(position>0 显 on) ═══════════ */
typedef struct {
    lv_obj_t *on;     /* 开状态图 */
    lv_obj_t *off;    /* 关状态图 */
    uint8_t   idx;    /* CURTAIN_IDX_* */
} CurtainRow;

static CurtainRow g_curtain_rows[CURTAIN_IDX_COUNT];

static void curtain_refresh(CurtainRow *row)
{
    if (!row->on) return;
    bool open = curtain_motion_target(row->idx) > 0;   /* 定时模型: 按目标立刻显状态 */
    lv_obj_set_style_img_opa(row->on,  open ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(row->off, open ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* 晾衣机状态图: 放下(sDryRackDown)/收起(sDryRackUp) 叠放 */
static lv_obj_t *s_dr_down_img;
static lv_obj_t *s_dr_up_img;

static void dryrack_img_refresh(void)
{
    if (!s_dr_down_img) return;
    bool down = curtain_motion_target(MOTION_IDX_DRYRACK) > 0;   /* pct>0 = 放下 */
    lv_obj_set_style_img_opa(s_dr_down_img, down ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(s_dr_up_img,   down ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* ═══════════ 音乐: imgbtn_9 播放/暂停, sMusicPlayImg 转盘 ═══════════ */
#define MUSIC_TIMER_MS  30        //MS milliseconds
#define MUSIC_RPS       0.5f      //RPS rotations per second

static lv_timer_t *s_music_timer;
static int16_t     s_music_angle;   /* 当前角度 0.1° */

static void music_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *disc = guider_ui.device_management_screen_sMusicPauseImg;   /* 唱片碟 */
    if (!lv_obj_is_valid(disc)) return;
    s_music_angle += (int16_t)(MUSIC_RPS * 3600.0f * MUSIC_TIMER_MS / 1000.0f);
    if (s_music_angle >= 3600) s_music_angle -= 3600;
    lv_img_set_angle(disc, s_music_angle);
}

static void music_apply(void)
{
    bool playing = HWInterface.Music.playing;
    if (playing) lv_obj_add_state  (guider_ui.device_management_screen_imgbtn_9, LV_STATE_CHECKED);
    else         lv_obj_clear_state(guider_ui.device_management_screen_imgbtn_9, LV_STATE_CHECKED);
    if (playing) {
        if (!s_music_timer) s_music_timer = lv_timer_create(music_rotate_cb, MUSIC_TIMER_MS, NULL);
    } else {
        if (s_music_timer) { lv_timer_del(s_music_timer); s_music_timer = NULL; }
    }
}

/* ═══════════ 风扇灯: sFanLightBtn 灯, sSourceBtn 风扇, 两张扇叶图转动 ═══════════ */
#define FAN_TIMER_MS  30        //MS milliseconds

static lv_timer_t *s_fan_timer;
static int16_t     s_fan_angle;   /* 当前角度 0.1° */

static void fan_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *fan_on  = guider_ui.device_management_screen_sFanOpenImg;
    lv_obj_t *fan_off = guider_ui.device_management_screen_sFancloseImg;
    s_fan_angle += (int16_t)(fanlight_speed_rps() * 3600.0f * FAN_TIMER_MS / 1000.0f);
    if (s_fan_angle >= 3600) s_fan_angle -= 3600;
    if (lv_obj_is_valid(fan_on))  lv_img_set_angle(fan_on,  s_fan_angle);
    if (lv_obj_is_valid(fan_off)) lv_img_set_angle(fan_off, s_fan_angle);
}

static void fanlight_apply(void)
{
    /* 用 power 闸门后的有效状态: 子界面总开关关了→这里风扇/灯都显示关 */
    bool power = HWInterface.FanAndLight.power;
    bool light = power && HWInterface.FanAndLight.light_on;
    bool fan   = power && HWInterface.FanAndLight.fan_on;

    /* 灯: 亮显 sFanOpenImg, 灭显 sFancloseImg(两张叠放, 切透明度) */
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sFanOpenImg,
                             light ? LV_OPA_COVER : LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sFancloseImg,
                             light ? LV_OPA_TRANSP : LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (light) lv_obj_add_state  (guider_ui.device_management_screen_sFanLightBtn, LV_STATE_CHECKED);
    else       lv_obj_clear_state(guider_ui.device_management_screen_sFanLightBtn, LV_STATE_CHECKED);

    /* 风扇: 开则转(速度同子界面档位) */
    if (fan) lv_obj_add_state  (guider_ui.device_management_screen_sSourceBtn, LV_STATE_CHECKED);
    else     lv_obj_clear_state(guider_ui.device_management_screen_sSourceBtn, LV_STATE_CHECKED);
    if (fan) {
        if (!s_fan_timer) s_fan_timer = lv_timer_create(fan_rotate_cb, FAN_TIMER_MS, NULL);
    } else {
        if (s_fan_timer) { lv_timer_del(s_fan_timer); s_fan_timer = NULL; }
    }
}

/* ═══════════ 浴霸: 镜像子界面(照明独立 + 模式互斥) ═══════════ */
/* HeatDev 底 → idleMode 默认 → 当前模式图 → 照明图(独立, 开则盖最上, 关则隐藏) */
static void heater_apply(void)
{
    lv_obj_t *modeimg[6] = {
        NULL,
        guider_ui.device_management_screen_sHeatHighModeImg,  /* 1 暖风高 */
        guider_ui.device_management_screen_sHeatLowModeImg,   /* 2 暖风低 */
        guider_ui.device_management_screen_sVentilateModeImg, /* 3 换气 */
        guider_ui.device_management_screen_sWindModeImg,      /* 4 吹风 */
        guider_ui.device_management_screen_sidleModeImg,      /* 5 待机 */
    };
    lv_obj_move_foreground(guider_ui.device_management_screen_sHeatDevImg);
    lv_obj_move_foreground(guider_ui.device_management_screen_sidleModeImg);
    int8_t mode = HWInterface.Heater.mode;
    if (mode >= 1 && mode <= 5) lv_obj_move_foreground(modeimg[mode]);

    if (HWInterface.Heater.light) {
        lv_obj_clear_flag(guider_ui.device_management_screen_sHeatLightImg, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(guider_ui.device_management_screen_sHeatLightImg);
        lv_obj_add_state(guider_ui.device_management_screen_sHeaterLightBtn, LV_STATE_CHECKED);
    } else {
        lv_obj_add_flag(guider_ui.device_management_screen_sHeatLightImg, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(guider_ui.device_management_screen_sHeaterLightBtn, LV_STATE_CHECKED);
    }
}

/* ═══════════ 空调: 电源键(imgbtn_6) + 当前模式文字(关机显"关"), 同步子界面 ═══════════ */
static void aircon_apply(void)
{
    bool power = HWInterface.AirCondition.power;

    /* 电源键勾选态跟随 */
    if (power) lv_obj_add_state  (guider_ui.device_management_screen_imgbtn_6, LV_STATE_CHECKED);
    else       lv_obj_clear_state(guider_ui.device_management_screen_imgbtn_6, LV_STATE_CHECKED);

    /* 只显当前模式文字, 关机显"关" */
    lv_obj_t *txt[5] = {
        guider_ui.device_management_screen_sACCoolText,  /* 0 制冷 */
        guider_ui.device_management_screen_sACHotText,   /* 1 制热 */
        guider_ui.device_management_screen_sACFanText,   /* 2 送风 */
        guider_ui.device_management_screen_sACDryText,   /* 3 除湿 */
        guider_ui.device_management_screen_sOffText,     /* 4 关 */
    };
    uint8_t mode = HWInterface.AirCondition.mode;
    uint8_t show = power ? (mode < 4 ? mode : 0) : 4;
    for (uint8_t i = 0; i < 5; i++) {
        if (i == show) lv_obj_clear_flag(txt[i], LV_OBJ_FLAG_HIDDEN);
        else           lv_obj_add_flag (txt[i], LV_OBJ_FLAG_HIDDEN);
    }
}

/* 屏删除: 停所有 timer 防野指针 */
static void dev_mgmt_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    if (s_music_timer) { lv_timer_del(s_music_timer); s_music_timer = NULL; }
    if (s_fan_timer)   { lv_timer_del(s_fan_timer);   s_fan_timer   = NULL; }
}

/* 非对称热区: 左/下各 100(基础50+额外30), 上/右各 40。
 * ext_click_area 只能四边统一(本版LVGL), 故 pad 设100让候选框够大,
 * 再在此事件里把上/右多出的部分裁回 50。需配 ADV_HITTEST 标志。 */
static void hit_test_bl(lv_event_t *e)   //bl: bottom-left 额外扩
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_hit_test_info_t *info = lv_event_get_hit_test_info(e);
    lv_area_t a;
    lv_obj_get_coords(obj, &a);
    a.x1 -= 40;   //左 50+30
    a.x2 += 40;    //右 20
    a.y1 -= 40;    //上 20
    a.y2 += 80;   //下 50+30
    const lv_point_t *p = info->point;
    if (p->x < a.x1 || p->x > a.x2 || p->y < a.y1 || p->y > a.y2) {
        info->res = false;
    }
}


static void set_hit_area_bl(lv_obj_t *obj)
{
    if (!obj) return;
    lv_obj_set_ext_click_area(obj, 100);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(obj, hit_test_bl, LV_EVENT_HIT_TEST, NULL);
}

/* ═══════════ 对外接口(供 GUI-Guider 事件调用) ═══════════ */

void dev_mgmt_on_load(void)
{
    lv_obj_add_event_cb(guider_ui.device_management_screen, dev_mgmt_screen_delete, LV_EVENT_DELETE, NULL);

    /* 绑定控件到槽位 (开关 imgbtn, 开指示, 关遮罩) */
    slot_bind(&g_slots[DEV_SLOT_CT_LIGHT],
              guider_ui.device_management_screen_Light_CT_on_off_1_img,
              guider_ui.device_management_screen_sdev_on,
              guider_ui.device_management_screen_small_dev_off_img);
    slot_bind(&g_slots[DEV_SLOT_LEDSTRIP],
              guider_ui.device_management_screen_sLSimgbtn,
              guider_ui.device_management_screen_sLEDStripOn,
              guider_ui.device_management_screen_sLEDStripOff);
    slot_bind(&g_slots[DEV_SLOT_MAGLIGHT],
              guider_ui.device_management_screen_sMagimgbtn,
              guider_ui.device_management_screen_sMagLightOn,
              guider_ui.device_management_screen_sMagLightOff);
    slot_bind(&g_slots[DEV_SLOT_RGBLIGHT],
              guider_ui.device_management_screen_sRGBLightBtn,
              guider_ui.device_management_screen_sRGBLightOn,
              guider_ui.device_management_screen_sRGBLightOff);

    /* 灯开关imgbtn点击热区: 上/右各+50, 左/下各+100(图片显示尺寸不变) */
    set_hit_area_bl(guider_ui.device_management_screen_Light_CT_on_off_1_img);
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_Light_CT_on_off_1_img, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.device_management_screen_sLSimgbtn);
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sLSimgbtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.device_management_screen_sMagimgbtn);
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sMagimgbtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.device_management_screen_sRGBLightBtn);
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sRGBLightBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.device_management_screen_imgbtn_6);   //空调开关
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_imgbtn_6, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    set_hit_area_bl(guider_ui.device_management_screen_imgbtn_9);   //音乐播放
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_imgbtn_9, 128, LV_PART_MAIN | LV_STATE_PRESSED);

    /* 窗帘/晾衣机/风扇灯/浴霸 控制按钮热区各+15px(图片不变大) */
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sFabricCurOpen, 15);   //布帘开
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sFabricCurOpen, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sFabricCurClose, 15);  //布帘合
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sFabricCurClose, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sSheerOpen, 15);       //纱帘开
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sSheerOpen, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sSheerClose, 15);      //纱帘合
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sSheerClose, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sRollBlindUp, 15);     //卷帘上
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sRollBlindUp, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sRollBlindDown, 15);   //卷帘下
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sRollBlindDown, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sDreamOpen, 15);       //梦幻帘开
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sDreamOpen, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sDreamClose, 15);      //梦幻帘合
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sDreamClose, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sDryRackUpBtn, 15);    //晾衣机上
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sDryRackUpBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sDryRackDownBtn, 15);  //晾衣机下
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sDryRackDownBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sFanLightBtn, 15);     //风扇灯-灯
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sFanLightBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sSourceBtn, 15);       //风扇灯-风扇
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sSourceBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_sHeaterLightBtn, 15);  //浴霸灯
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sHeaterLightBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_ext_click_area(guider_ui.device_management_screen_IdleBtn, 15);          //浴霸待机
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_IdleBtn, 128, LV_PART_MAIN | LV_STATE_PRESSED);

    /* 刷新全部灯槽位 */
    for (uint8_t i = 0; i < DEV_SLOT_COUNT; i++) {
        slot_refresh(&g_slots[i]);
    }

    /* 绑定窗帘行(开状态图, 关状态图, idx) 并刷状态 */
    g_curtain_rows[CURTAIN_IDX_FABRIC] = (CurtainRow){
        guider_ui.device_management_screen_sFabricCurtianOn,
        guider_ui.device_management_screen_sFabricCurtianOff, CURTAIN_IDX_FABRIC };
    g_curtain_rows[CURTAIN_IDX_SHEERS] = (CurtainRow){
        guider_ui.device_management_screen_sSheersOn,
        guider_ui.device_management_screen_sSheersOff, CURTAIN_IDX_SHEERS };
    g_curtain_rows[CURTAIN_IDX_ROLLBLIND] = (CurtainRow){
        guider_ui.device_management_screen_sRollBlindOn,
        guider_ui.device_management_screen_sRollBlindOff, CURTAIN_IDX_ROLLBLIND };
    g_curtain_rows[CURTAIN_IDX_DREAM] = (CurtainRow){
        guider_ui.device_management_screen_sDreamOn,
        guider_ui.device_management_screen_sDreamOff, CURTAIN_IDX_DREAM };

    for (uint8_t i = 0; i < CURTAIN_IDX_COUNT; i++) {
        curtain_refresh(&g_curtain_rows[i]);
    }

    /* 绑定晾衣机状态图并刷新 */
    s_dr_down_img = guider_ui.device_management_screen_sDryRackDown;
    s_dr_up_img   = guider_ui.device_management_screen_sDryRackUp;
    dryrack_img_refresh();

    /* 晾衣机照明: 只显示(无开关), 跟随子界面 HWInterface.DryRack.light; 置顶防遮挡 */
    lv_obj_set_style_img_opa(guider_ui.device_management_screen_sDRLightImg,
                             HWInterface.DryRack.light ? LV_OPA_COVER : LV_OPA_TRANSP,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_move_foreground(guider_ui.device_management_screen_sDRLightImg);

    /* 音乐: 唱片碟 pivot 居中(51x51) + 按播放状态刷新 */
    lv_img_set_pivot(guider_ui.device_management_screen_sMusicPauseImg, 25, 25);
    music_apply();

    /* 风扇灯: 两张扇叶图 pivot 居中(60x60) + 按状态刷新 */
    lv_img_set_pivot(guider_ui.device_management_screen_sFanOpenImg,  30, 30);
    lv_img_set_pivot(guider_ui.device_management_screen_sFancloseImg, 30, 30);
    fanlight_apply();

    /* 浴霸: 镜像当前模式 */
    heater_apply();

    /* 空调: 电源键状态 + 当前模式文字 */
    aircon_apply();

    /* 清除装饰图层CLICKABLE(不挡按钮), 白名单外自动清; 新装饰图加进此数组 */
    {
        lv_obj_t *clear[] = {
            guider_ui.device_management_screen_sdev_on,
            guider_ui.device_management_screen_small_dev_off_img,
            guider_ui.device_management_screen_sLEDStripOn,
            guider_ui.device_management_screen_sLEDStripOff,
            guider_ui.device_management_screen_sMagLightOn,
            guider_ui.device_management_screen_sMagLightOff,
            guider_ui.device_management_screen_sRGBLightOn,
            guider_ui.device_management_screen_sRGBLightOff,
            guider_ui.device_management_screen_sFabricCurtianOn,
            guider_ui.device_management_screen_sFabricCurtianOff,
            guider_ui.device_management_screen_sSheersOn,
            guider_ui.device_management_screen_sSheersOff,
            guider_ui.device_management_screen_sRollBlindOn,
            guider_ui.device_management_screen_sRollBlindOff,
            guider_ui.device_management_screen_sDreamOn,
            guider_ui.device_management_screen_sDreamOff,
            guider_ui.device_management_screen_sVentilateACimg,
            guider_ui.device_management_screen_sAC,
            guider_ui.device_management_screen_sMusicPauseImg,
            guider_ui.device_management_screen_sMusicPlayImg,
            guider_ui.device_management_screen_sDryRackDown,
            guider_ui.device_management_screen_sDryRackUp,
            guider_ui.device_management_screen_sDRLightImg,
            guider_ui.device_management_screen_sFanOpenImg,
            guider_ui.device_management_screen_sFancloseImg,
            guider_ui.device_management_screen_sHeatLightImg,
            guider_ui.device_management_screen_sHeatLowModeImg,
            guider_ui.device_management_screen_sHeatHighModeImg,
            guider_ui.device_management_screen_sVentilateModeImg,
            guider_ui.device_management_screen_sWindModeImg,
            guider_ui.device_management_screen_sHeatDevImg,
            guider_ui.device_management_screen_sidleModeImg,
        };
        for (uint8_t i = 0; i < sizeof(clear) / sizeof(clear[0]); i++) {
            if (lv_obj_is_valid(clear[i])) lv_obj_clear_flag(clear[i], LV_OBJ_FLAG_CLICKABLE);
        }
    }
}

/* 通用: 读控件 CHECKED → 写中间层 → 刷指示器 */
static void slot_toggle(uint8_t idx)
{
    DevSlot *slot = &g_slots[idx];
    if (!slot->sw) return;
    bool on = lv_obj_has_state(slot->sw, LV_STATE_CHECKED);
    slot->set_on(on);
    slot_refresh(slot);
}

void dev_mgmt_ct_on_toggle(void)  { slot_toggle(DEV_SLOT_CT_LIGHT); }
void dev_mgmt_led_on_toggle(void) { slot_toggle(DEV_SLOT_LEDSTRIP); }
void dev_mgmt_mag_on_toggle(void) { slot_toggle(DEV_SLOT_MAGLIGHT); }
void dev_mgmt_rgb_on_toggle(void) { slot_toggle(DEV_SLOT_RGBLIGHT); }

/* 定时移动(子界面会按时间续播), 图标立刻反映目标 */
static void curtain_move(uint8_t idx, uint16_t target)
{
    curtain_motion_start(idx, target);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_POS, .idx = idx, .val = target });
    curtain_refresh(&g_curtain_rows[idx]);
}

void dev_mgmt_fabric_open(void)    { curtain_move(CURTAIN_IDX_FABRIC,    CURTAIN_POS_MAX); }
void dev_mgmt_fabric_close(void)   { curtain_move(CURTAIN_IDX_FABRIC,    CURTAIN_POS_MIN); }
void dev_mgmt_sheers_open(void)    { curtain_move(CURTAIN_IDX_SHEERS,    CURTAIN_POS_MAX); }
void dev_mgmt_sheers_close(void)   { curtain_move(CURTAIN_IDX_SHEERS,    CURTAIN_POS_MIN); }
void dev_mgmt_rollblind_open(void) { curtain_move(CURTAIN_IDX_ROLLBLIND, CURTAIN_POS_MAX); }
void dev_mgmt_rollblind_close(void){ curtain_move(CURTAIN_IDX_ROLLBLIND, CURTAIN_POS_MIN); }
void dev_mgmt_dream_open(void)     { curtain_move(CURTAIN_IDX_DREAM,     CURTAIN_POS_MAX); }
void dev_mgmt_dream_close(void)    { curtain_move(CURTAIN_IDX_DREAM,     CURTAIN_POS_MIN); }

/* ═══════════ 晾衣机: 升/降按钮 复用运动模型 ═══════════ */
void dev_mgmt_dryrack_down(void)   /* 放下: pct 100 */
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 100);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_POS, .val = 100 });
    dryrack_img_refresh();
}
void dev_mgmt_dryrack_up(void)     /* 收起: pct 0 */
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 0);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_POS, .val = 0 });
    dryrack_img_refresh();
}

/* 音乐 播放/暂停(imgbtn_9 VALUE_CHANGED): 转盘随播放转 */
void dev_mgmt_music_toggle(void)
{
    HWInterface.Music.playing = lv_obj_has_state(guider_ui.device_management_screen_imgbtn_9, LV_STATE_CHECKED);
    music_apply();
}

/* 风扇灯 灯光开关(sFanLightBtn VALUE_CHANGED) */
void dev_mgmt_fanlight_light_toggle(void)
{
    HWInterface.FanAndLight.light_on = lv_obj_has_state(guider_ui.device_management_screen_sFanLightBtn, LV_STATE_CHECKED);
    /* 开灯/扇即开子界面总开关; 两者都关才关总开关 */
    HWInterface.FanAndLight.power = HWInterface.FanAndLight.fan_on || HWInterface.FanAndLight.light_on;
    fanlight_apply();
}

/* 风扇灯 风扇开关(sSourceBtn VALUE_CHANGED): 开则扇叶转动 */
void dev_mgmt_fanlight_fan_toggle(void)
{
    HWInterface.FanAndLight.fan_on = lv_obj_has_state(guider_ui.device_management_screen_sSourceBtn, LV_STATE_CHECKED);
    HWInterface.FanAndLight.power = HWInterface.FanAndLight.fan_on || HWInterface.FanAndLight.light_on;
    fanlight_apply();
}

/* 浴霸 照明开关(sHeaterLightBtn VALUE_CHANGED): 独立, 不影响模式 */
void dev_mgmt_heater_light_toggle(void)
{
    HWInterface.Heater.light = lv_obj_has_state(guider_ui.device_management_screen_sHeaterLightBtn, LV_STATE_CHECKED);
    heater_apply();
}

/* 浴霸 待机键(IdleBtn CLICKED): 切到待机(5), 再点取消 */
void dev_mgmt_heater_idle(void)
{
    HWInterface.Heater.mode = (HWInterface.Heater.mode == 5) ? -1 : 5;
    heater_apply();
}

/* 空调 电源(imgbtn_6 VALUE_CHANGED): 同步子界面电源 */
void dev_mgmt_aircon_toggle(void)
{
    HWInterface.AirCondition.power = lv_obj_has_state(guider_ui.device_management_screen_imgbtn_6, LV_STATE_CHECKED);
    aircon_apply();
}
