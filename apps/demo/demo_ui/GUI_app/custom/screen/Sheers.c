#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "Sheers.h"

#define TRAVEL_PX    190        //PX pixels
#define APPLY_MIN_MS 50         //MIN minimum, MS milliseconds

static int32_t    s_offset;     /* 当前开合位移 0..TRAVEL_PX */
static uint32_t   s_post_tick;
/* 闭合时各控件 x, on_screen_load 运行时捕获(尊重 GUI-Guider 摆放) */
static lv_coord_t s_left_x0, s_right_x0, s_pull1_x0, s_pull2_x0;   //x0 initial x

/* 两帘+两拉手从各自设计位置对称平移 offset(拉手随帘一起动) */
static void sheers_apply(int32_t offset)
{
    if (!lv_obj_is_valid(guider_ui.Sheers_FabCurtianLeft)) return;
    lv_obj_set_x(guider_ui.Sheers_FabCurtianLeft,  s_left_x0  - offset);
    lv_obj_set_x(guider_ui.Sheers_FabCurtianright, s_right_x0 + offset);
    lv_obj_set_x(guider_ui.Sheers_FabCurtianPull1, s_pull1_x0 - offset);
    lv_obj_set_x(guider_ui.Sheers_FabCurtianPull2, s_pull2_x0 + offset);
}

static void sheers_post(int32_t offset)
{
    int percent = offset * 100 / TRAVEL_PX;
    HWInterface.Curtain.SetPos(CURTAIN_IDX_SHEERS, (uint16_t)percent);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_POS, .idx = CURTAIN_IDX_SHEERS, .val = (uint16_t)percent });
}

static void sheers_anim_exec(void *unused, int32_t value)
{
    LV_UNUSED(unused);
    s_offset = value;
    sheers_apply(value);
}

/* 在指定时间内动画到 target(px); ms=0 直接到位 */
static void sheers_anim_to_ms(int32_t target, uint32_t ms)
{
    lv_anim_del(&s_offset, sheers_anim_exec);
    if (ms == 0) { s_offset = target; sheers_apply(target); return; }
    lv_anim_t animation;
    lv_anim_init(&animation);
    lv_anim_set_var(&animation, &s_offset);
    lv_anim_set_exec_cb(&animation, sheers_anim_exec);   //cb callback
    lv_anim_set_values(&animation, s_offset, target);
    lv_anim_set_time(&animation, ms);
    lv_anim_start(&animation);
}

/* 本屏不在 scr_guard, 自挂删除回调停动画防野指针 */
static void sheers_on_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_anim_del(&s_offset, sheers_anim_exec);
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void sheers_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.Sheers, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.Sheers, sheers_on_screen_delete, LV_EVENT_DELETE, NULL);
    s_left_x0  = lv_obj_get_x(guider_ui.Sheers_FabCurtianLeft);
    s_right_x0 = lv_obj_get_x(guider_ui.Sheers_FabCurtianright);
    s_pull1_x0 = lv_obj_get_x(guider_ui.Sheers_FabCurtianPull1);
    s_pull2_x0 = lv_obj_get_x(guider_ui.Sheers_FabCurtianPull2);

    /* 按时间算当前位置, 若仍在移动则续播到目标 */
    uint16_t cur_pct = curtain_motion_current(CURTAIN_IDX_SHEERS);
    uint16_t tgt_pct = curtain_motion_target(CURTAIN_IDX_SHEERS);
    s_offset = cur_pct * TRAVEL_PX / 100;
    sheers_apply(s_offset);
    if (cur_pct != tgt_pct)
        sheers_anim_to_ms(tgt_pct * TRAVEL_PX / 100, curtain_motion_remaining_ms(CURTAIN_IDX_SHEERS));

    /* 按钮按下反馈: 50% 透明 */
    {
        lv_obj_t *b[] = { guider_ui.Sheers_FabCurtianOpen,
                          guider_ui.Sheers_FabCurtianPause,
                          guider_ui.Sheers_FabCurtianClose };
        for (uint8_t i = 0; i < 3; i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

void sheers_on_open(void)
{
    curtain_motion_start(CURTAIN_IDX_SHEERS, 100);
    sheers_anim_to_ms(TRAVEL_PX, curtain_motion_remaining_ms(CURTAIN_IDX_SHEERS));
    sheers_post(TRAVEL_PX);
}

void sheers_on_close(void)
{
    curtain_motion_start(CURTAIN_IDX_SHEERS, 0);
    sheers_anim_to_ms(0, curtain_motion_remaining_ms(CURTAIN_IDX_SHEERS));
    sheers_post(0);
}

void sheers_on_pause(void)
{
    lv_anim_del(&s_offset, sheers_anim_exec);
    curtain_motion_set(CURTAIN_IDX_SHEERS, (uint16_t)(s_offset * 100 / TRAVEL_PX));
    sheers_post(s_offset);
}

/* 拖拉手: 跟手累加位移(像素), 按抓住的拉手锁定方向(越过中线不切边) */
void sheers_on_drag(lv_event_t *event)
{
    lv_indev_t *indev = lv_indev_get_act();   //indev input device
    if (!indev) return;
    lv_anim_del(&s_offset, sheers_anim_exec);

    lv_obj_t *target = lv_event_get_target(event);
    bool right = (target == guider_ui.Sheers_FabCurtianPull2 ||
                  target == guider_ui.Sheers_FabCurtianright);
    lv_point_t delta;
    lv_indev_get_vect(indev, &delta);         //vect vector
    s_offset += right ? delta.x : -delta.x;    /* 右拉手右移=开, 左拉手左移=开 */
    if (s_offset < 0)         s_offset = 0;
    if (s_offset > TRAVEL_PX) s_offset = TRAVEL_PX;

    sheers_apply(s_offset);
    curtain_motion_set(CURTAIN_IDX_SHEERS, (uint16_t)(s_offset * 100 / TRAVEL_PX));  /* 手动定位, 停在此处 */
    if (lv_tick_elaps(s_post_tick) >= APPLY_MIN_MS) {
        s_post_tick = lv_tick_get();
        sheers_post(s_offset);
    }
}
