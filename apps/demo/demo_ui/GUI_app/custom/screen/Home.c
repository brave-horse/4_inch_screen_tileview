#include "lvgl.h"
#include "gui_guider.h"
#include "Home.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "FanAndLight.h"
#include "device_management.h"
#include "nav.h"

/* 状态图显示/隐藏: 用 HIDDEN flag(不渲染)替代 opa(透明仍走渲染管线), 减小设备页渲染压力 */
static inline void img_show(lv_obj_t *obj, bool show)
{
    if (!obj) return;
    if (show) lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    else      lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
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
    img_show(slot->on,  on);    /* on 图: 开则显示, 关则 HIDDEN */
    img_show(slot->off, !on);   /* off 图: 关则显示 */
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
    img_show(row->on,  open);
    img_show(row->off, !open);
}

static lv_obj_t *s_dr_down_img;
static lv_obj_t *s_dr_up_img;
static void dryrack_img_refresh(void)
{
    if (!s_dr_down_img) return;
    bool down = curtain_motion_target(MOTION_IDX_DRYRACK) > 0;
    img_show(s_dr_down_img, down);
    img_show(s_dr_up_img,   !down);
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
    img_show(guider_ui.ui_home_screen_img_29, light);    /* 灯亮+扇 */
    img_show(guider_ui.ui_home_screen_img_28, !light);   /* 灯灭+扇 */
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
    lv_obj_move_foreground(guider_ui.ui_home_screen_img_21);   /* 设备底 sDev: 提到 z 基准 */
    int8_t mode = HWInterface.Heater.mode;
    /* 模式图互斥: 当前模式显示+置顶, 其余 HIDDEN(不渲染, 减压力) */
    for (uint8_t m = 1; m <= 5; m++) {
        if (m == mode) { img_show(modeimg[m], true); lv_obj_move_foreground(modeimg[m]); }
        else           img_show(modeimg[m], false);
    }
    /* 灯光 sHlight */
    if (HWInterface.Heater.light) {
        img_show(guider_ui.ui_home_screen_img_26, true);
        lv_obj_move_foreground(guider_ui.ui_home_screen_img_26);
        lv_obj_add_state(guider_ui.ui_home_screen_imgbtn_1, LV_STATE_CHECKED);
    } else {
        img_show(guider_ui.ui_home_screen_img_26, false);
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

/* 同步解码 obj 子树里所有 lv_img 进缓存(命中则秒过)。进 home 时把场景页大图
 * 一次性解进 DDR, 之后滑过去缓存命中不卡。代价: 进 home 这一刻多顿几百 ms。 */
static void decode_subtree_imgs(lv_obj_t *obj)
{
    if (lv_obj_check_type(obj, &lv_img_class)) {
        const void *src = lv_img_get_src(obj);
        if (src) _lv_img_cache_open(src, lv_color_white(), 0);
    }
    uint32_t cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t i = 0; i < cnt; i++) decode_subtree_imgs(lv_obj_get_child(obj, i));
}

/* ── 场景卡片标签点击上滑 ── */
static void scene_label_anim_exec_cb(void *var, int32_t v)
{
    lv_obj_set_y((lv_obj_t *)var, v);
}

static void scene_label_anim_ready_cb(lv_anim_t *anim)
{
    lv_obj_t *label = (lv_obj_t *)anim->var;
    if (!lv_obj_is_valid(label)) return;
    int32_t base_y = (int32_t)(intptr_t)lv_obj_get_user_data(label);
    lv_obj_set_y(label, base_y);
}

static void scene_cont_clicked_cb(lv_event_t *e)
{
    lv_obj_t *label = (lv_obj_t *)lv_event_get_user_data(e);
    if (!lv_obj_is_valid(label)) return;
    int32_t base_y = (int32_t)(intptr_t)lv_obj_get_user_data(label);
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, label);
    lv_anim_set_exec_cb(&anim, scene_label_anim_exec_cb);
    lv_anim_set_values(&anim, base_y, base_y - 45);
    lv_anim_set_time(&anim, 850);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&anim, scene_label_anim_ready_cb);
    lv_anim_start(&anim);
}

/* ── tile5 卡片松开颜色反馈 ── */
static void cont_color_anim_exec_cb(void *var, int32_t v)
{
    lv_obj_t *cont = (lv_obj_t *)var;
    lv_color_t c = lv_color_mix(lv_color_hex(0x1d3d60), lv_color_hex(0x333641), (uint8_t)v);
    lv_obj_set_style_bg_color(cont, c, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void cont_released_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    if (!lv_obj_is_valid(cont)) return;
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x1d3d60), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, cont);
    lv_anim_set_exec_cb(&anim, cont_color_anim_exec_cb);
    lv_anim_set_values(&anim, 255, 0);   // v:255蓝→0灰, 松开从蓝渐隐回原色
    lv_anim_set_time(&anim, 400);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_start(&anim);
}

/* ── tile3 三个灯按键: off=_1(HlightOff) on=_2(HlightOn), btn 已是 CHECKABLE ── */
typedef struct { lv_obj_t *btn; lv_obj_t *off_img; lv_obj_t *on_img; } LightBtn;  //off_img关图 on_img开图
static LightBtn g_light_btns[3];

static void light_btn_apply(LightBtn *light)
{
    if (!light->btn) return;
    bool on = lv_obj_has_state(light->btn, LV_STATE_CHECKED);
    img_show(light->on_img,  on);     //不显示的图用HIDDEN, 不进渲染
    img_show(light->off_img, !on);
}
static void light_btn_event_cb(lv_event_t *e)
{
    light_btn_apply((LightBtn *)lv_event_get_user_data(e));
}

/* tile5 灯光总控前向声明(定义在文件尾部) */
static void lights_all_on(lv_event_t *e);
static void lights_all_off(lv_event_t *e);

/* ═══════════ 首页 + 设备页合并加载 ═══════════ */
void home_on_screen_load(void)
{
    /* tileview 布局(共7个tile col0~6): tile_3 当主页面(进 home 默认停这),
     * tile_0/1 预留空白禁止滑入(为后续主页左边屏幕留位), tile_2~6 全部可滑。
     * 逐 tile 设 dir 控制可滑方向(set_tile 会用 tile->dir 重设 scroll_dir):
     *   tile_0/1 = NONE  不可达(留白)
     *   tile_2   = RIGHT 左边界, 只能往右, 滑不到 tile_1/0
     *   tile_3   = HOR   主页面
     *   tile_4/5 = HOR   中间页, 双向可滑
     *   tile_6   = LEFT  右边界
     * 关 ELASTIC 让边界硬停。LVGL v8 内部 tile 结构 {lv_obj_t obj; lv_dir_t dir}。 */
    {
        struct tv_tile { lv_obj_t obj; lv_dir_t dir; };   //tv tileview
        lv_obj_t *tv = guider_ui.ui_home_screen_tileview_1;
        lv_obj_t *tiles[] = { guider_ui.ui_home_screen_tileview_1_tile_0,
                              guider_ui.ui_home_screen_tileview_1_tile_1,
                              guider_ui.ui_home_screen_tileview_1_tile_2,
                              guider_ui.ui_home_screen_tileview_1_tile_3,
                              guider_ui.ui_home_screen_tileview_1_tile_4,
                              guider_ui.ui_home_screen_tileview_1_tile_5,
                              guider_ui.ui_home_screen_tileview_1_tile_6 };
        lv_dir_t dirs[] = { LV_DIR_NONE, LV_DIR_NONE, LV_DIR_RIGHT, LV_DIR_HOR,
                            LV_DIR_HOR, LV_DIR_HOR, LV_DIR_LEFT };
        for (uint8_t i = 0; i < 7; i++)
            if (lv_obj_is_valid(tiles[i])) ((struct tv_tile *)tiles[i])->dir = dirs[i];
        if (lv_obj_is_valid(tv)) {
            lv_obj_clear_flag(tv, LV_OBJ_FLAG_SCROLL_ELASTIC);
            int restore_tile   = nav_consume_home_tile();    /* 返回时记的来源 tile, -1=无 */
            int restore_scroll = nav_consume_home_scroll();  /* 设备页 tabview 内部滚动位置 */
            uint8_t col = restore_tile >= 0 ? (uint8_t)restore_tile : 3;
            lv_obj_set_tile_id(tv, col, 0, LV_ANIM_OFF);
            /* 设备页(tile4)卡片的滚动在内部 tabview_3 的 tab_1, 不是 tile 本身 */
            if (col == 4 && restore_scroll > 0 &&
                lv_obj_is_valid(guider_ui.ui_home_screen_tabview_3_tab_1)) {
                lv_obj_t *dev_tab = guider_ui.ui_home_screen_tabview_3_tab_1;
                lv_obj_update_layout(dev_tab);               /* 先布局, 滚动范围才有效 */
                lv_obj_scroll_to_y(dev_tab, restore_scroll, LV_ANIM_OFF);
            }
        }
    }

    /* ── 首页: 清大图 CLICKABLE ── */
    #define SAFE_CLEAR(obj, flag) if (lv_obj_is_valid(guider_ui.obj)) lv_obj_clear_flag(guider_ui.obj, flag)
    SAFE_CLEAR(ui_home_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_2, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_3, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_4, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_img_6, LV_OBJ_FLAG_CLICKABLE);
    SAFE_CLEAR(ui_home_screen_MainSetImg, LV_OBJ_FLAG_CLICKABLE);

    /* ── tile_3 三个灯按键 btn_63/64/65: 点击 toggle 显示 on/off 图 ──
     * 旧 btn_1/2/7 已在 GUI-Guider 删除。off=_1(HlightOff) on=_2(HlightOn)。 */
    {
        g_light_btns[0] = (LightBtn){ guider_ui.ui_home_screen_btn_63, guider_ui.ui_home_screen_img_off_63_1, guider_ui.ui_home_screen_img_off_63_2 };
        g_light_btns[1] = (LightBtn){ guider_ui.ui_home_screen_btn_64, guider_ui.ui_home_screen_img_off_64_1, guider_ui.ui_home_screen_img_on_64_2  };
        g_light_btns[2] = (LightBtn){ guider_ui.ui_home_screen_btn_65, guider_ui.ui_home_screen_img_off_65_1, guider_ui.ui_home_screen_img_off_65_2 };
        /* 清 9 个图/标签的 CLICKABLE, 让点击穿透到下层 btn */
        lv_obj_t *passthru[] = {
            guider_ui.ui_home_screen_img_off_63_1, guider_ui.ui_home_screen_img_off_63_2, guider_ui.ui_home_screen_label_63,
            guider_ui.ui_home_screen_img_off_64_1, guider_ui.ui_home_screen_img_on_64_2,  guider_ui.ui_home_screen_label_64,
            guider_ui.ui_home_screen_img_off_65_1, guider_ui.ui_home_screen_img_off_65_2, guider_ui.ui_home_screen_label_65,
        };
        for (uint8_t i = 0; i < 9; i++)
            if (lv_obj_is_valid(passthru[i])) lv_obj_clear_flag(passthru[i], LV_OBJ_FLAG_CLICKABLE);
        for (uint8_t i = 0; i < 3; i++) {
            LightBtn *light = &g_light_btns[i];
            if (!lv_obj_is_valid(light->btn)) continue;
            lv_obj_clear_state(light->btn, LV_STATE_CHECKED);   //默认off
            light_btn_apply(light);                              //初始: 显off图, 隐on图
            lv_obj_add_event_cb(light->btn, light_btn_event_cb, LV_EVENT_VALUE_CHANGED, light);
        }
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
    img_show(guider_ui.ui_home_screen_img_19, HWInterface.DryRack.light);   /* sDryRackL */
    if (HWInterface.DryRack.light) lv_obj_move_foreground(guider_ui.ui_home_screen_img_19);

    /* 音乐 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_35, 25, 25);   /* 唱片碟 51x51 */
    music_apply();

    /* 风扇灯 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_29, 30, 30);   /* 灯亮+扇叶 60x60 */
    lv_img_set_pivot(guider_ui.ui_home_screen_img_28, 30, 30);   /* 灯灭+扇叶 */
    fanlight_apply();

    /* 浴霸 */
    heater_apply();

    /* tile5 灯光总控: cont_3=全开, cont_4=全关; 清内部子 CLICKABLE 让按压落容器 */
    if (lv_obj_is_valid(guider_ui.ui_home_screen_cont_3)) {
        uint32_t cc = lv_obj_get_child_cnt(guider_ui.ui_home_screen_cont_3);
        for (uint32_t ci = 0; ci < cc; ci++)
            lv_obj_clear_flag(lv_obj_get_child(guider_ui.ui_home_screen_cont_3, ci), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_flag(guider_ui.ui_home_screen_cont_3, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(guider_ui.ui_home_screen_cont_3, lights_all_on, LV_EVENT_PRESSED, NULL);
    }
    if (lv_obj_is_valid(guider_ui.ui_home_screen_cont_4)) {
        uint32_t cc = lv_obj_get_child_cnt(guider_ui.ui_home_screen_cont_4);
        for (uint32_t ci = 0; ci < cc; ci++)
            lv_obj_clear_flag(lv_obj_get_child(guider_ui.ui_home_screen_cont_4, ci), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_flag(guider_ui.ui_home_screen_cont_4, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(guider_ui.ui_home_screen_cont_4, lights_all_off, LV_EVENT_PRESSED, NULL);
    }

    /* ── 场景卡片标签点击动画 ── */
    {
        lv_obj_t *conts[8] = {
            guider_ui.ui_home_screen_cont_28, guider_ui.ui_home_screen_cont_29,
            guider_ui.ui_home_screen_cont_30, guider_ui.ui_home_screen_cont_31,
            guider_ui.ui_home_screen_cont_32, guider_ui.ui_home_screen_cont_33,
            guider_ui.ui_home_screen_cont_34, guider_ui.ui_home_screen_cont_35,
        };
        lv_obj_t *labels[8] = {
            guider_ui.ui_home_screen_label_45, guider_ui.ui_home_screen_label_46,
            guider_ui.ui_home_screen_label_47, guider_ui.ui_home_screen_label_48,
            guider_ui.ui_home_screen_label_49, guider_ui.ui_home_screen_label_50,
            guider_ui.ui_home_screen_label_51, guider_ui.ui_home_screen_label_52,
        };
        for (uint8_t i = 0; i < 8; i++) {
            if (!lv_obj_is_valid(conts[i]) || !lv_obj_is_valid(labels[i])) continue;
            /* 清 cont 内子图的 CLICKABLE, 让点击穿透到 cont */
            uint32_t child_cnt = lv_obj_get_child_cnt(conts[i]);
            for (uint32_t c = 0; c < child_cnt; c++) {
                lv_obj_t *child = lv_obj_get_child(conts[i], c);
                if (lv_obj_check_type(child, &lv_img_class))
                    lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
            }
            lv_obj_add_flag(conts[i], LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_user_data(labels[i], (void *)(intptr_t)lv_obj_get_y(labels[i]));
            lv_obj_add_event_cb(conts[i], scene_cont_clicked_cb, LV_EVENT_CLICKED, labels[i]);
        }
    }

    /* ── tile5 卡片松开颜色反馈 ── */
    {
        lv_obj_t *conts[6] = {
            guider_ui.ui_home_screen_cont_3, guider_ui.ui_home_screen_cont_4,
            guider_ui.ui_home_screen_cont_5, guider_ui.ui_home_screen_cont_6,
            guider_ui.ui_home_screen_cont_7, guider_ui.ui_home_screen_cont_8,
        };
        for (uint8_t i = 0; i < 6; i++) {
            if (!lv_obj_is_valid(conts[i])) continue;
            uint32_t child_cnt = lv_obj_get_child_cnt(conts[i]);
            for (uint32_t c = 0; c < child_cnt; c++) {
                lv_obj_t *child = lv_obj_get_child(conts[i], c);
                if (lv_obj_check_type(child, &lv_img_class))
                    lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
            }
            lv_obj_add_flag(conts[i], LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(conts[i], cont_released_cb, LV_EVENT_RELEASED, NULL);
        }
    }
}

/* 预解码场景页(tile_4)全部图进缓存。由 scr_guard 在 purge_cache 之后调用。
 * 注: 内存不足时此预解码仍会 nodata(实测), 治本是把场景图编进固件(C数组,不走cache)。
 *     编固件做完后, 本函数 + decode_subtree_imgs + scr_guard 的调用都应一并撤掉。 */
void home_preload_scene(void)
{
    if (lv_obj_is_valid(guider_ui.ui_home_screen_tileview_1_tile_4))
        decode_subtree_imgs(guider_ui.ui_home_screen_tileview_1_tile_4);
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
void dev_mgmt_led_on_toggle(void *e) { (void)e; slot_toggle(DEV_SLOT_LEDSTRIP); }  /* e 忽略, 兼容 GUI-Guider 带参回调 */
void dev_mgmt_mag_on_toggle(void)    { slot_toggle(DEV_SLOT_MAGLIGHT); }
void dev_mgmt_rgb_on_toggle(void)    { slot_toggle(DEV_SLOT_RGBLIGHT); }

/* tile5 灯光总控: cont_3=全开, cont_4=全关 */
static void lights_all_on(lv_event_t *e)
{
    LV_UNUSED(e);
    ct_set_on(true);  led_set_on(true);
    mag_set_on(true); rgb_set_on(true);
    for (uint8_t i = 0; i < DEV_SLOT_COUNT; i++) slot_refresh(&g_slots[i]);
}
static void lights_all_off(lv_event_t *e)
{
    LV_UNUSED(e);
    ct_set_on(false);  led_set_on(false);
    mag_set_on(false); rgb_set_on(false);
    for (uint8_t i = 0; i < DEV_SLOT_COUNT; i++) slot_refresh(&g_slots[i]);
}

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
    bool on = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_2, LV_STATE_CHECKED);
    if (on) HWInterface.FanAndLight.power = true;   /* 开灯先开总电源(否则总开关关时点不亮), 关灯不动 power */
    HWInterface.FanAndLight.light_on = on;
    fanlight_apply();
}

void dev_mgmt_fanlight_fan_toggle(void)
{
    bool on = lv_obj_has_state(guider_ui.ui_home_screen_imgbtn_3, LV_STATE_CHECKED);
    if (on) HWInterface.FanAndLight.power = true;   /* 开风扇先开总电源, 关风扇不动 power */
    HWInterface.FanAndLight.fan_on = on;
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
