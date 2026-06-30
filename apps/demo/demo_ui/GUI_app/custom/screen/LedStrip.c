/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "light_CT_screen.h"
#include "LEDStrip.h"
#include "scene_panel.h"

/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t s_bri_tick;
static uint32_t s_ct_tick;
static ScenePanel s_panel;   /* cont_2 情景面板 */
/* 硬件下发限频(ms)。UI 每次都刷跟手, 硬件下发限频防 IIC/PWM 过密。
 * ⚠️ 隐患: 拖动松手时最后一帧若落在限频窗口内会被跳过, 硬件停在松手前 50ms 的中间值,
 *    与 UI 显示的最终值不一致 → 下次调节硬件会从那个中间值"咔嚓"跳到目标(亮度/色温突变)。
 *    接硬件时务必在松手(RELEASED)绕过限频强制补发一次最终值, UI 与硬件才同步。 */
#define APPLY_MIN_MS  50
#define LEDSTRIP_OPA_MIN  (LV_OPA_COVER * 20 / 100)   /* 亮度下限: 拖到1%也按20%出光, 防止灯条消失 */

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

static void led_strip_apply_light(void)
{
    lv_obj_t *slider1 = guider_ui.LedStrip_slider_1;
    lv_obj_t *slider2 = guider_ui.LedStrip_slider_2;
    if (!lv_obj_is_valid(slider1) || !lv_obj_is_valid(slider2))
        return;

    int32_t  bri = lv_slider_get_value(slider1);
    int32_t  ct  = lv_slider_get_value(slider2);
    uint32_t ct_span  = LIGHTCT_COLOR_TEMP_MAX - LIGHTCT_COLOR_TEMP_MIN;
    uint32_t tnum     = (uint32_t)(ct - LIGHTCT_COLOR_TEMP_MIN);
    uint32_t total    = LEDSTRIP_OPA_MIN + (uint32_t)bri * (LV_OPA_COVER - LEDSTRIP_OPA_MIN) / LIGHTCT_BRIGHTNESS_MAX;
    uint32_t o_white  = total * tnum             / ct_span;
    uint32_t o_orange = total * (ct_span - tnum) / ct_span;

    lv_obj_set_style_img_opa(guider_ui.LedStrip_LSOff, (lv_opa_t)o_white,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.LedStrip_LSOn,  (lv_opa_t)o_orange, LV_PART_MAIN | LV_STATE_DEFAULT);

    char buf[32];
    lv_snprintf(buf, sizeof(buf), "亮 度 | %d%%", (int)bri);
    lv_label_set_text(guider_ui.LedStrip_label_1, buf);
    lv_snprintf(buf, sizeof(buf), "色 温 | %dK", (int)ct);
    lv_label_set_text(guider_ui.LedStrip_label_2, buf);
}

static void led_strip_refresh(bool btn_status)
{
    led_strip_apply_light();

    if (btn_status) lv_obj_add_state(guider_ui.LedStrip_on_off_2_img, LV_STATE_CHECKED);
    else            lv_obj_clear_state(guider_ui.LedStrip_on_off_2_img, LV_STATE_CHECKED);

    if (btn_status) {
        lv_obj_set_style_bg_opa(guider_ui.LedStrip_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_background(guider_ui.LedStrip_cont_1);
    } else {
        lv_obj_set_style_bg_opa(guider_ui.LedStrip_cont_1, 162, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.LedStrip_cont_1);
        lv_obj_move_foreground(guider_ui.LedStrip_on_off_2_img);
    }
}

/* 松手补值: 快速甩到边缘时 VALUE_CHANGED 可能没到极值, RELEASED 再对齐一次 */
static void ct_released_cb(lv_event_t *e) { LV_UNUSED(e); led_strip_on_ct_slider_change(); }

/* ══════ 4 个事件接口(供 GUI-Guider 事件一行调用) ══════ */

void led_strip_on_screen_load(void)
{
    bool btn_status = HWInterface.LEDStrip.switch_status;
    lv_obj_set_style_pad_hor(guider_ui.LedStrip_slider_2, 30, LV_PART_MAIN);
    lv_obj_add_event_cb(guider_ui.LedStrip_slider_2, ct_released_cb, LV_EVENT_RELEASED, NULL);
    lv_slider_set_range(guider_ui.LedStrip_slider_1, 1, LIGHTCT_BRIGHTNESS_MAX);
    lv_slider_set_value(guider_ui.LedStrip_slider_1, HWInterface.LightCT.brightness, LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.LedStrip_slider_2, HWInterface.LightCT.color_temp, LV_ANIM_OFF);
    led_strip_refresh(btn_status);

    /* 按下反馈: 降透明度(松手自动还原) */
    lv_obj_t *btns[] = { guider_ui.LedStrip_on_off_2_img, guider_ui.LedStrip_imgbtn_1 };
    for (uint8_t i = 0; i < 2; i++) {
        lv_obj_set_style_img_opa(btns[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);   /* 按下 50% 透明 */
        lv_obj_set_ext_click_area(btns[i], 30);   /* 热区各+30px,图片不变 */
    }

    /* cont_2 情景面板: 滑出/收回/模态/图片反馈 见 scene_panel 模块 */
    scene_panel_setup(&s_panel, guider_ui.LedStrip, guider_ui.LedStrip_cont_2,
                      guider_ui.LedStrip_imgbtn_1, guider_ui.LedStrip_on_off_2_img,
                      led_strip_refresh);
}

void led_strip_on_switch_toggle(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    bool btn_status = lv_obj_has_state(btn, LV_STATE_CHECKED);

    HWInterface.LEDStrip.SetOnOff(btn_status);
    hw_cloud_post(&(HW_Msg){
        .type = HW_MSG_LIGHT_LED_SWITCH,
        .on   = btn_status
    });
    scene_panel_on_power(&s_panel, btn_status);   /* 开/关灯; 关时面板若开先收回再上遮罩 */
}

void led_strip_on_bri_slider_change(void)
{
    HWInterface.LightCT.SetBrightness((uint16_t)lv_slider_get_value(guider_ui.LedStrip_slider_1));
    led_strip_apply_light();   /* UI 每次都刷, 跟手; 仅硬件下发限频 */
    if (lv_tick_elaps(s_bri_tick) >= APPLY_MIN_MS) {
        s_bri_tick = lv_tick_get();
        hw_cloud_post(&(HW_Msg){
            .type = HW_MSG_LIGHT_CT_BRI,
            .val  = HWInterface.LightCT.brightness
        });
    }
}

void led_strip_on_ct_slider_change(void)
{
    lv_obj_t *s = guider_ui.LedStrip_slider_2;
    int32_t raw = lv_slider_get_value(s);
    int32_t v = ((raw + 25) / 50) * 50;
    if (v < LIGHTCT_COLOR_TEMP_MIN) v = LIGHTCT_COLOR_TEMP_MIN;
    if (v > LIGHTCT_COLOR_TEMP_MAX) v = LIGHTCT_COLOR_TEMP_MAX;
    if (v != raw) lv_slider_set_value(s, v, LV_ANIM_OFF);

    HWInterface.LightCT.SetColorTemp((uint16_t)v);
    led_strip_apply_light();   /* UI 每次都刷, 跟手; 仅硬件下发限频 */
    if (lv_tick_elaps(s_ct_tick) >= APPLY_MIN_MS) {
        s_ct_tick = lv_tick_get();
        hw_cloud_post(&(HW_Msg){
            .type = HW_MSG_LIGHT_CT_CT,
            .val  = HWInterface.LightCT.color_temp
        });
    }
}
