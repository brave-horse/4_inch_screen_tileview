#include "lvgl.h"
#include "gui_guider.h"
#include "hw_cloud_task.h"
#include "HWDataAccess.h"
#include "DryRack.h"

#define DOWN_Y       160      /* img_1 最大下降 y(初始 -110) */
#define APPLY_MIN_MS 50
#define DRYRACK_FULL_MS 5500  /* 升降全程耗时 ms —— 改这里调晾衣机升降速度(越大越慢) */
#define TAP_BTN_Y    560      /* 点击到位时, 超过此 y 算点底部按钮行, 忽略 */
#define ARM_TAP_ADJUST 0      /* 点击到位参考微调: 杆没对准点击点就调这里(px, 负=参考点上移) */

#define s_light  HWInterface.DryRack.light   /* 照明开关存中间层(与管理屏共享) */

static int32_t    s_d;         /* 当前下降位移 0..s_travel */
static int32_t    s_travel;    /* = DOWN_Y - 初始 y */
static lv_coord_t s_img_y0;    /* img_1 初始 y(运行时捕获) */
static lv_coord_t s_label_y0;  /* label_1 初始 y */
static lv_coord_t s_pull_y0;   /* 大按钮 dry_rack_pull 初始 y */
static uint32_t   s_post_tick;

/* img_1 + label_1 同步移动(间距不变), label 显示百分比 */
static void dryrack_apply(int32_t d)
{
    if (!lv_obj_is_valid(guider_ui.DryRack_img_1)) return;
    lv_obj_set_y(guider_ui.DryRack_img_1,   s_img_y0   + d);
    lv_obj_set_y(guider_ui.DryRack_label_1, s_label_y0 + d);
    lv_obj_set_y(guider_ui.DryRack_dry_rack_pull, s_pull_y0 + d);   /* 大按钮跟晾衣架升降 */
    int pct = s_travel ? (int)(d * 100 / s_travel) : 0;
    lv_label_set_text_fmt(guider_ui.DryRack_label_1, "%d%%", pct);
}

static void dryrack_post(int32_t d)
{
    int pct = s_travel ? (int)(d * 100 / s_travel) : 0;
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_POS, .val = (uint16_t)pct });
}

/* 照明: imgbtn 勾选态 + DRLightImg 发光图透明度 */
static void dryrack_apply_light(void)
{
    if (s_light) lv_obj_add_state  (guider_ui.DryRack_imgbtn_1, LV_STATE_CHECKED);
    else         lv_obj_clear_state(guider_ui.DryRack_imgbtn_1, LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(guider_ui.DryRack_DRLightImg,
                             s_light ? LV_OPA_COVER : LV_OPA_TRANSP,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void d_anim_cb(void *var, int32_t v)
{
    LV_UNUSED(var);
    s_d = v;
    dryrack_apply(v);
}

/* 在指定时间内动画到 target(px); ms=0 直接到位 */
static void anim_to_ms(int32_t target, uint32_t ms)
{
    lv_anim_del(&s_d, d_anim_cb);
    if (ms == 0) { s_d = target; dryrack_apply(target); return; }
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, &s_d);
    lv_anim_set_exec_cb(&a, d_anim_cb);
    lv_anim_set_values(&a, s_d, target);
    lv_anim_set_time(&a, ms);
    lv_anim_start(&a);
}

/* px ↔ pct 换算(s_travel 运行时才有) */
static uint16_t d_to_pct(int32_t d) { return s_travel ? (uint16_t)(d * 100 / s_travel) : 0; }
static int32_t  pct_to_d(uint16_t pct) { return (int32_t)pct * s_travel / 100; }

/* 点场景空白处 → 晾衣架升降到该 y(学卷帘点击到位, 瞬间到不播动画) */
static void dryrack_tap_to(lv_coord_t py)
{
    /* 晾衣架杆在 img_1 底部附近: 参考点 = 图底(收起时杆的视觉 y), 点击 py 让杆移到那 */
    lv_coord_t arm_ref = s_img_y0 + lv_obj_get_height(guider_ui.DryRack_img_1) + ARM_TAP_ADJUST;
    int32_t d = py - arm_ref;
    if (d < 0)        d = 0;
    if (d > s_travel) d = s_travel;
    lv_anim_del(&s_d, d_anim_cb);
    s_d = d;
    dryrack_apply(d);
    curtain_motion_set(MOTION_IDX_DRYRACK, d_to_pct(d));   /* 定位停住 */
    dryrack_post(d);
}

static void dryrack_on_bg_tap(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_point_t p;
    lv_indev_get_point(indev, &p);
    if (p.y > TAP_BTN_Y) return;   /* 避开底部按钮行 */
    dryrack_tap_to(p.y);
}

/* 本屏不在 scr_guard 列表, 自挂删除回调: 屏一删停动画, 防野指针 */
static void scr_del_cb(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_anim_del(&s_d, d_anim_cb);
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void dryrack_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.DryRack, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.DryRack, scr_del_cb, LV_EVENT_DELETE, NULL);
    curtain_motion_set_speed(MOTION_IDX_DRYRACK, DRYRACK_FULL_MS);   /* 本屏升降速度 */
    /* Open/Close: 按下瞬间到位 */
    while (lv_obj_remove_event_cb(guider_ui.DryRack_FabCurtianOpen, NULL));
    lv_obj_add_event_cb(guider_ui.DryRack_FabCurtianOpen, (lv_event_cb_t)dryrack_on_open, LV_EVENT_PRESSED, NULL);
    while (lv_obj_remove_event_cb(guider_ui.DryRack_FabCurtianClose, NULL));
    lv_obj_add_event_cb(guider_ui.DryRack_FabCurtianClose, (lv_event_cb_t)dryrack_on_close, LV_EVENT_PRESSED, NULL);
    /* 点场景空白处升降到位(学卷帘): 挂在 cont_1 背景层 */
    if (lv_obj_is_valid(guider_ui.DryRack_cont_1)) {
        lv_obj_add_flag(guider_ui.DryRack_cont_1, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_remove_event_cb(guider_ui.DryRack_cont_1, dryrack_on_bg_tap);
        lv_obj_add_event_cb(guider_ui.DryRack_cont_1, dryrack_on_bg_tap, LV_EVENT_CLICKED, NULL);
    }
    /* 大按钮 dry_rack_pull: 追加 CLICKED 到位(PRESSING 拖动走生成的 dryrack_on_drag, 不碰) */
    lv_obj_add_event_cb(guider_ui.DryRack_dry_rack_pull, dryrack_pull_click, LV_EVENT_CLICKED, NULL);

    s_img_y0   = lv_obj_get_y(guider_ui.DryRack_img_1);
    s_label_y0 = lv_obj_get_y(guider_ui.DryRack_label_1);
    s_pull_y0  = lv_obj_get_y(guider_ui.DryRack_dry_rack_pull);
    s_travel   = DOWN_Y - s_img_y0;
    if (s_travel <= 0) s_travel = 270;

    /* 按时间算当前位置, 若仍在移动则续播到目标 */
    uint16_t cur_pct = curtain_motion_current(MOTION_IDX_DRYRACK);
    uint16_t tgt_pct = curtain_motion_target(MOTION_IDX_DRYRACK);
    s_d = pct_to_d(cur_pct);
    dryrack_apply(s_d);
    dryrack_apply_light();
    if (cur_pct != tgt_pct)
        anim_to_ms(pct_to_d(tgt_pct), curtain_motion_remaining_ms(MOTION_IDX_DRYRACK));

    /* 按钮按下反馈: 50% 透明 */
    {
        lv_obj_t *b[] = { guider_ui.DryRack_FabCurtianOpen,
                          guider_ui.DryRack_FabCurtianPause,
                          guider_ui.DryRack_FabCurtianClose,
                          guider_ui.DryRack_imgbtn_1 };
        for (uint8_t i = 0; i < 4; i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

/* 灯按钮: 开→img_2 显示, 关→img_2 透明度 0 */
void dryrack_on_light_toggle(lv_event_t *e)
{
    s_light = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    dryrack_apply_light();
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_DRYRACK_LIGHT, .on = s_light });
}

/* 大按钮点击到位: CLICKED 独立回调(不碰 PRESSING 拖动, 免得干扰 vect 累加) */
static void dryrack_pull_click(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_point_t p;
    lv_indev_get_point(indev, &p);
    if (p.y <= TAP_BTN_Y) dryrack_tap_to(p.y);
}

/* 触摸 label_1/img_1/dry_rack_pull 拖动: 跟手累加位移, 两者同步移动 */
void dryrack_on_drag(lv_event_t *e)
{
    LV_UNUSED(e);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_anim_del(&s_d, d_anim_cb);

    lv_point_t v;
    lv_indev_get_vect(indev, &v);
    s_d += v.y;
    if (s_d < 0)        s_d = 0;
    if (s_d > s_travel) s_d = s_travel;

    dryrack_apply(s_d);
    curtain_motion_set(MOTION_IDX_DRYRACK, d_to_pct(s_d));   /* 手动定位, 停在此处 */
    if (lv_tick_elaps(s_post_tick) >= APPLY_MIN_MS) {
        s_post_tick = lv_tick_get();
        dryrack_post(s_d);
    }
}

void dryrack_on_open(void)   /* 上升(收起): pct 0 */
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 0);
    anim_to_ms(0, curtain_motion_remaining_ms(MOTION_IDX_DRYRACK));
    dryrack_post(0);
}

void dryrack_on_close(void)  /* 下降(放下): pct 100 */
{
    curtain_motion_start(MOTION_IDX_DRYRACK, 100);
    anim_to_ms(s_travel, curtain_motion_remaining_ms(MOTION_IDX_DRYRACK));
    dryrack_post(s_travel);
}

void dryrack_on_pause(void)
{
    lv_anim_del(&s_d, d_anim_cb);
    curtain_motion_set(MOTION_IDX_DRYRACK, d_to_pct(s_d));
    dryrack_post(s_d);
}
