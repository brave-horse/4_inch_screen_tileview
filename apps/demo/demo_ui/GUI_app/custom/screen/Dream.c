#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "Dream.h"

#define TRAVEL_PX    181        //PX pixels —— 全开行程, 改开多少调这里
#define APPLY_MIN_MS 50         //MIN minimum, MS milliseconds
#define ANGLE_MAX    180        /* 旋转角范围 0..180° */
#define SLIDER_MAX   100        /* slider_1 量程 */
#define SNAP_HALF    30         //点击中线±30 区域直接关紧
#define DREAM_FULL_MS 3500      /* 开合全程耗时 ms —— 改这里调梦幻帘开合速度(越大越慢) */

static int32_t    s_offset;                        /* 当前开合位移 0..TRAVEL_PX */
static int32_t    s_angle_slider = SLIDER_MAX / 2; /* 旋转角滑条值, 初始 50=90° */
static uint32_t   s_post_tick;
static uint32_t   s_angle_tick;
static lv_coord_t s_left_x0, s_right_x0, s_pull1_x0, s_pull2_x0;   //x0 initial x, 运行时捕获
static lv_coord_t s_center;     //两帘合拢中线 = 左帘右缘, on_screen_load 算

/* 两帘+两拉手从各自设计位置对称平移 offset, label 显示百分比 */
static void dream_apply(int32_t offset)
{
    if (!lv_obj_is_valid(guider_ui.Dream_FabCurtianLeft)) return;
    lv_obj_set_x(guider_ui.Dream_FabCurtianLeft,  s_left_x0  - offset);
    lv_obj_set_x(guider_ui.Dream_FabCurtianright, s_right_x0 + offset);
    lv_obj_set_x(guider_ui.Dream_FabCurtianPull1, s_pull1_x0 - offset);
    lv_obj_set_x(guider_ui.Dream_FabCurtianPull2, s_pull2_x0 + offset);
    lv_obj_set_x(guider_ui.Dream_FabCurtianPull3, s_pull1_x0 - offset);
    lv_obj_set_x(guider_ui.Dream_FabCurtianPull4, s_pull2_x0 + offset);
    lv_label_set_text_fmt(guider_ui.Dream_label_1, "%d%%", (int)(offset * 100 / TRAVEL_PX));
}

static void dream_post(int32_t offset)
{
    int percent = offset * 100 / TRAVEL_PX;
    HWInterface.Curtain.SetPos(CURTAIN_IDX_DREAM, (uint16_t)percent);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_POS, .idx = CURTAIN_IDX_DREAM, .val = (uint16_t)percent });
}

/* 旋转角只入队下发, UI 不转 */
static void dream_post_angle(int32_t degree)
{
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_CURTAIN_ANGLE, .idx = CURTAIN_IDX_DREAM, .val = (uint16_t)degree });
}

static void dream_anim_exec(void *unused, int32_t value)
{
    LV_UNUSED(unused);
    s_offset = value;
    dream_apply(value);
}

/* 在指定时间内动画到 target(px); ms=0 直接到位 */
static void dream_anim_to_ms(int32_t target, uint32_t ms)
{
    lv_anim_del(&s_offset, dream_anim_exec);
    if (ms == 0) { s_offset = target; dream_apply(target); return; }
    lv_anim_t animation;
    lv_anim_init(&animation);
    lv_anim_set_var(&animation, &s_offset);
    lv_anim_set_exec_cb(&animation, dream_anim_exec);   //cb callback
    lv_anim_set_values(&animation, s_offset, target);
    lv_anim_set_time(&animation, ms);
    lv_anim_start(&animation);
}

/* 点帘面 px(屏坐标) → 两帘对称瞬间到位; 中线±30 区域关紧(不播动画) */
static void dream_tap_to(lv_coord_t px)
{
    int32_t d = px - s_center;
    if (d < 0) d = -d;
    int32_t target = (d <= SNAP_HALF) ? 0 : d;
    if (target > TRAVEL_PX) target = TRAVEL_PX;
    lv_anim_del(&s_offset, dream_anim_exec);
    s_offset = target;
    dream_apply(target);
    curtain_motion_set(CURTAIN_IDX_DREAM, (uint16_t)(target * 100 / TRAVEL_PX));
    dream_post(target);
}

/* 点窗口任意处(帘面已清CLICKABLE穿透到此cont_1)→到位; 避开底部按钮行 */
static void dream_on_bg_tap(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_indev_t *indev = lv_indev_get_act();
    if (!indev) return;
    lv_point_t p;
    lv_indev_get_point(indev, &p);
    if (p.y > 560) return;
    dream_tap_to(p.x);
}

/* 本屏不在 scr_guard, 自挂删除回调停动画防野指针 */
static void dream_on_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    lv_anim_del(&s_offset, dream_anim_exec);
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void dream_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.Dream, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.Dream, dream_on_screen_delete, LV_EVENT_DELETE, NULL);
    curtain_motion_set_speed(CURTAIN_IDX_DREAM, DREAM_FULL_MS);   /* 本屏开合速度 */
    s_left_x0  = lv_obj_get_x(guider_ui.Dream_FabCurtianLeft);
    s_right_x0 = lv_obj_get_x(guider_ui.Dream_FabCurtianright);
    s_pull1_x0 = lv_obj_get_x(guider_ui.Dream_FabCurtianPull1);
    s_pull2_x0 = lv_obj_get_x(guider_ui.Dream_FabCurtianPull2);
    s_center   = s_left_x0 + lv_obj_get_width(guider_ui.Dream_FabCurtianLeft);   //中线=左帘右缘
    lv_slider_set_value(guider_ui.Dream_slider_1, s_angle_slider, LV_ANIM_OFF);

    /* 点击到位: 清两帘 CLICKABLE 让点穿透到 cont_1 统一接管(拉手仍 PRESSING 拖动) */
    lv_obj_clear_flag(guider_ui.Dream_FabCurtianLeft,  LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(guider_ui.Dream_FabCurtianright, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(guider_ui.Dream_cont_1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_event_cb(guider_ui.Dream_cont_1, dream_on_bg_tap);
    lv_obj_add_event_cb(guider_ui.Dream_cont_1, dream_on_bg_tap, LV_EVENT_CLICKED, NULL);

    /* 按时间算当前位置, 若仍在移动则续播到目标 */
    uint16_t cur_pct = curtain_motion_current(CURTAIN_IDX_DREAM);
    uint16_t tgt_pct = curtain_motion_target(CURTAIN_IDX_DREAM);
    s_offset = cur_pct * TRAVEL_PX / 100;
    dream_apply(s_offset);
    if (cur_pct != tgt_pct)
        dream_anim_to_ms(tgt_pct * TRAVEL_PX / 100, curtain_motion_remaining_ms(CURTAIN_IDX_DREAM));
    dream_post_angle(s_angle_slider * ANGLE_MAX / SLIDER_MAX);

    /* 按钮按下反馈: 50% 透明 */
    {
        lv_obj_t *b[] = { guider_ui.Dream_FabCurtianOpen,
                          guider_ui.Dream_FabCurtianPause,
                          guider_ui.Dream_FabCurtianClose };
        for (uint8_t i = 0; i < 3; i++)
            lv_obj_set_style_img_opa(b[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

void dream_on_open(void)
{
    curtain_motion_start(CURTAIN_IDX_DREAM, 100);
    dream_anim_to_ms(TRAVEL_PX, curtain_motion_remaining_ms(CURTAIN_IDX_DREAM));
    dream_post(TRAVEL_PX);
}

void dream_on_close(void)
{
    curtain_motion_start(CURTAIN_IDX_DREAM, 0);
    dream_anim_to_ms(0, curtain_motion_remaining_ms(CURTAIN_IDX_DREAM));
    dream_post(0);
}

void dream_on_pause(void)
{
    lv_anim_del(&s_offset, dream_anim_exec);
    curtain_motion_set(CURTAIN_IDX_DREAM, (uint16_t)(s_offset * 100 / TRAVEL_PX));
    dream_post(s_offset);
}

/* 拖拉手: 跟手累加位移(像素), 按抓住的拉手锁定方向(越过中线不切边) */
void dream_on_drag(lv_event_t *event)
{
    lv_indev_t *indev = lv_indev_get_act();   //indev input device
    if (!indev) return;
    lv_anim_del(&s_offset, dream_anim_exec);

    lv_obj_t *target = lv_event_get_target(event);
    bool right = (target == guider_ui.Dream_FabCurtianPull2 ||
                  target == guider_ui.Dream_FabCurtianPull4 ||   /* 右帘大按钮 */
                  target == guider_ui.Dream_FabCurtianright);
    lv_point_t delta;
    lv_indev_get_vect(indev, &delta);         //vect vector
    s_offset += right ? delta.x : -delta.x;    /* 右拉手右移=开, 左拉手左移=开 */
    if (s_offset < 0)         s_offset = 0;
    if (s_offset > TRAVEL_PX) s_offset = TRAVEL_PX;

    dream_apply(s_offset);
    curtain_motion_set(CURTAIN_IDX_DREAM, (uint16_t)(s_offset * 100 / TRAVEL_PX));  /* 手动定位, 停在此处 */
    if (lv_tick_elaps(s_post_tick) >= APPLY_MIN_MS) {
        s_post_tick = lv_tick_get();
        dream_post(s_offset);
    }
}

/* 旋转角滑条 0..100 → 0..180° 下发 */
void dream_on_angle_slider_change(void)
{
    s_angle_slider = lv_slider_get_value(guider_ui.Dream_slider_1);
    if (lv_tick_elaps(s_angle_tick) >= APPLY_MIN_MS) {
        s_angle_tick = lv_tick_get();
        dream_post_angle(s_angle_slider * ANGLE_MAX / SLIDER_MAX);
    }
}
