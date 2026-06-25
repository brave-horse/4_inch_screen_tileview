#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "RollBlind.h"

/* 竖向卷帘: 取自 generated 布局 */
#define CLOTH_Y0    181          /* 帘布 closed Y: 全关时帘布控件 Y 坐标 */
#define PULL_Y0     481          /* 拉手 closed Y: 全关时拉手控件 Y 坐标 */
#define PULL_CY     500          /* 拉手 closed 中心 Y: 全关时拉手中心点, 拖动以它反算 pct */
#define TRAVEL_MAX  280          /* 拉手行程 px: 从最下移到最上 */
#define APPLY_MIN_MS 50          /* 拖动时云端上报最小间隔 ms */

static int32_t  s_pct;           /* 0=放到最长(下), 100=收到最短(上) */
static uint32_t s_post_tick;

static void roll_apply(int32_t pct)
{
    int32_t displacement = pct * TRAVEL_MAX / 100;
    lv_obj_set_y(guider_ui.RollBlind_FabCurtianLeft,  CLOTH_Y0 - displacement);
    lv_obj_set_y(guider_ui.RollBlind_FabCurtianPull1, PULL_Y0  - displacement);
}

static void roll_post(int32_t pct)
{
    HWInterface.Curtain.SetPos(CURTAIN_IDX_ROLLBLIND, (uint16_t)pct);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_POS, .idx = CURTAIN_IDX_ROLLBLIND, .val = (uint16_t)pct });
}

static void roll_anim_cb(void *var, int32_t value)
{
    LV_UNUSED(var);
    s_pct = value;
    roll_apply(value);
}

/* 在指定时间内动画到 target(%); ms=0 直接到位 */
static void roll_anim_to_ms(int32_t target, uint32_t ms)
{
    lv_anim_del(&s_pct, roll_anim_cb);
    if (ms == 0) { s_pct = target; roll_apply(target); return; }
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, &s_pct);
    lv_anim_set_exec_cb(&anim, roll_anim_cb);
    lv_anim_set_values(&anim, s_pct, target);
    lv_anim_set_time(&anim, ms);
    lv_anim_start(&anim);
}

/* 点窗口 py(屏坐标) → 卷帘竖向瞬间到位(不播动画); cloth 自身拖动绑定已是绝对 p.y, 点 cloth 也即到位 */
static void roll_tap_to(lv_coord_t py)
{
    int32_t pct = (PULL_CY - py) * 100 / TRAVEL_MAX;
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;
    lv_anim_del(&s_pct, roll_anim_cb);
    s_pct = pct;
    roll_apply(pct);
    curtain_motion_set(CURTAIN_IDX_ROLLBLIND, (uint16_t)pct);
    roll_post(pct);
}

/* 点窗口空白处(cloth 收起后下方空白)→到位; 避开底部按钮行 */
static void roll_on_bg_tap(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_point_t p;
    lv_indev_get_point(indev, &p);
    if (p.y > 560) return;
    roll_tap_to(p.y);
}

/* 本屏不在 scr_guard, 自挂删除回调停动画防野指针 */
static void roll_del_cb(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_anim_del(&s_pct, roll_anim_cb);
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void roll_blind_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.RollBlind, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.RollBlind, roll_del_cb, LV_EVENT_DELETE, NULL);
    /* 点空白处到位: cont_2 是窗口场景层(cloth收起后露出, 盖在cont_1之上, 之前点被它吃掉),
     * cont_1/cont_2 都挂保证接住; 点 cloth 本身已由其拖动绑定即时到位 */
    lv_obj_t *roll_bg[] = { guider_ui.RollBlind_cont_1, guider_ui.RollBlind_cont_2 };
    for (uint8_t i = 0; i < 2; i++) {
        if (!lv_obj_is_valid(roll_bg[i])) continue;
        lv_obj_add_flag(roll_bg[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_remove_event_cb(roll_bg[i], roll_on_bg_tap);
        lv_obj_add_event_cb(roll_bg[i], roll_on_bg_tap, LV_EVENT_CLICKED, NULL);
    }

    /* 按时间算当前位置, 若仍在移动则续播到目标 */
    uint16_t cur_pct = curtain_motion_current(CURTAIN_IDX_ROLLBLIND);
    uint16_t tgt_pct = curtain_motion_target(CURTAIN_IDX_ROLLBLIND);
    s_pct = cur_pct;
    roll_apply(s_pct);
    if (cur_pct != tgt_pct)
        roll_anim_to_ms(tgt_pct, curtain_motion_remaining_ms(CURTAIN_IDX_ROLLBLIND));

    /* 按钮按下反馈: 50% 透明 */
    {
        lv_obj_t *b[] = { guider_ui.RollBlind_FabCurtianOpen,
                          guider_ui.RollBlind_FabCurtianPause,
                          guider_ui.RollBlind_FabCurtianClose };
        for (uint8_t i = 0; i < 3; i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

void roll_blind_on_open(void)
{
    curtain_motion_start(CURTAIN_IDX_ROLLBLIND, 100);
    roll_anim_to_ms(100, curtain_motion_remaining_ms(CURTAIN_IDX_ROLLBLIND));
    roll_post(100);
}

void roll_blind_on_close(void)
{
    curtain_motion_start(CURTAIN_IDX_ROLLBLIND, 0);
    roll_anim_to_ms(0, curtain_motion_remaining_ms(CURTAIN_IDX_ROLLBLIND));
    roll_post(0);
}

void roll_blind_on_pause(void)
{
    lv_anim_del(&s_pct, roll_anim_cb);
    curtain_motion_set(CURTAIN_IDX_ROLLBLIND, (uint16_t)s_pct);
    roll_post(s_pct);
}

void roll_blind_on_drag(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_point_t point;
    lv_indev_get_point(indev, &point);

    lv_anim_del(&s_pct, roll_anim_cb);

    int32_t pct = (PULL_CY - point.y) * 100 / TRAVEL_MAX;
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;

    s_pct = pct;
    roll_apply(pct);
    curtain_motion_set(CURTAIN_IDX_ROLLBLIND, (uint16_t)pct);   /* 手动定位, 停在此处 */
    if (lv_tick_elaps(s_post_tick) >= APPLY_MIN_MS) {
        s_post_tick = lv_tick_get();
        roll_post(pct);
    }
}
