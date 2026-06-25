/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "MagLight.h"
#include "scene_panel.h"

/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t s_bri_tick;
static uint32_t s_ct_tick;
static ScenePanel s_panel;   /* cont_2 情景面板 */
#define APPLY_MIN_MS  50
#define MAGLIGHT_OPA_MIN  (LV_OPA_COVER * 20 / 100)  /* 亮度下限: 拖到1%也按20%出光, 防止灯图消失 */

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

static void mag_light_apply_light(void)
{
    lv_obj_t *slider1 = guider_ui.MagLight_slider_1;
    lv_obj_t *slider2 = guider_ui.MagLight_slider_2;
    if (!lv_obj_is_valid(slider1) || !lv_obj_is_valid(slider2))
        return;

    int32_t  bri = lv_slider_get_value(slider1);
    int32_t  ct  = lv_slider_get_value(slider2);
    uint32_t ct_span  = LIGHTCT_COLOR_TEMP_MAX - LIGHTCT_COLOR_TEMP_MIN;
    uint32_t tnum     = (uint32_t)(ct - LIGHTCT_COLOR_TEMP_MIN);
    uint32_t total    = MAGLIGHT_OPA_MIN + (uint32_t)bri * (LV_OPA_COVER - MAGLIGHT_OPA_MIN) / LIGHTCT_BRIGHTNESS_MAX;
    uint32_t o_white  = total * tnum             / ct_span;
    uint32_t o_orange = total * (ct_span - tnum) / ct_span;

    lv_obj_set_style_img_opa(guider_ui.MagLight_white,  (lv_opa_t)o_white,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.MagLight_Orange, (lv_opa_t)o_orange, LV_PART_MAIN | LV_STATE_DEFAULT);

    char buf[32];
    lv_snprintf(buf, sizeof(buf), "亮 度 | %d%%", (int)bri);
    lv_label_set_text(guider_ui.MagLight_label_1, buf);
    lv_snprintf(buf, sizeof(buf), "色 温 | %dK", (int)ct);
    lv_label_set_text(guider_ui.MagLight_label_2, buf);
}

/* 共用: 刷灯光图+标签+开关UI */
static void mag_light_refresh(bool btn_status)
{
    mag_light_apply_light();

    if (btn_status) lv_obj_add_state(guider_ui.MagLight_on_off_2_img, LV_STATE_CHECKED);
    else            lv_obj_clear_state(guider_ui.MagLight_on_off_2_img, LV_STATE_CHECKED);

    if (btn_status) {
        lv_obj_set_style_bg_opa(guider_ui.MagLight_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_background(guider_ui.MagLight_cont_1);
    } else {
        lv_obj_set_style_bg_opa(guider_ui.MagLight_cont_1, 162, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.MagLight_cont_1);
        lv_obj_move_foreground(guider_ui.MagLight_on_off_2_img);
    }
}

/* ══════ 4 个事件接口(供 GUI-Guider 事件一行调用) ══════ */

void mag_light_on_screen_load(void)
{
    bool btn_status = HWInterface.MagLight.switch_status;
    lv_slider_set_range(guider_ui.MagLight_slider_1, 1, LIGHTCT_BRIGHTNESS_MAX);
    lv_slider_set_value(guider_ui.MagLight_slider_1, HWInterface.LightCT.brightness, LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.MagLight_slider_2, HWInterface.LightCT.color_temp, LV_ANIM_OFF);
    mag_light_refresh(btn_status);

    /* 按下反馈: 降透明度(松手自动还原) */
    lv_obj_t *btns[] = { guider_ui.MagLight_on_off_2_img, guider_ui.MagLight_imgbtn_1 };
    for (uint8_t i = 0; i < 2; i++) {
        lv_obj_set_style_img_opa(btns[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);   /* 按下 50% 透明 */
        lv_obj_set_ext_click_area(btns[i], 30);   /* 热区各+30px,图片不变 */
    }

    /* cont_2 情景面板: 滑出/收回/模态/图片反馈 见 scene_panel 模块 */
    scene_panel_setup(&s_panel, guider_ui.MagLight, guider_ui.MagLight_cont_2,
                      guider_ui.MagLight_imgbtn_1, guider_ui.MagLight_on_off_2_img,
                      mag_light_refresh);
}

void mag_light_on_switch_toggle(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    bool btn_status = lv_obj_has_state(btn, LV_STATE_CHECKED);

    HWInterface.MagLight.SetOnOff(btn_status);      /* 更新缓存, UI 立刻可读 */
    hw_cloud_post(&(HW_Msg){                        /* 入队, 硬云任务下发硬件 */
        .type = HW_MSG_LIGHT_MAG_SWITCH,
        .on   = btn_status
    });
    scene_panel_on_power(&s_panel, btn_status);   /* 开/关灯; 关时面板若开先收回再上遮罩 */
}

void mag_light_on_bri_slider_change(void)
{
    HWInterface.LightCT.SetBrightness((uint16_t)lv_slider_get_value(guider_ui.MagLight_slider_1));
    mag_light_apply_light();
    if (lv_tick_elaps(s_bri_tick) >= APPLY_MIN_MS) {
        s_bri_tick = lv_tick_get();
        hw_cloud_post(&(HW_Msg){
            .type = HW_MSG_LIGHT_CT_BRI,
            .val  = HWInterface.LightCT.brightness
        });
    }
}

void mag_light_on_ct_slider_change(void)
{
    HWInterface.LightCT.SetColorTemp((uint16_t)lv_slider_get_value(guider_ui.MagLight_slider_2));
    mag_light_apply_light();
    if (lv_tick_elaps(s_ct_tick) >= APPLY_MIN_MS) {
        s_ct_tick = lv_tick_get();
        hw_cloud_post(&(HW_Msg){
            .type = HW_MSG_LIGHT_CT_CT,
            .val  = HWInterface.LightCT.color_temp
        });
    }
}
