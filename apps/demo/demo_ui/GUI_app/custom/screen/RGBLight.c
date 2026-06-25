#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"
#include "RGBLight.h"
#include "scene_panel.h"

static uint32_t s_bri_tick;
static uint32_t s_color_tick;
static uint16_t s_color_pos;            /* 颜色滑条位置, 切屏后回填 */
static ScenePanel s_panel;              /* cont_2 情景面板 */
#define APPLY_MIN_MS  50
#define RGB_SEG_LEN   100
#define RGB_ANCHORS   7
#define RGB_POS_MAX   (RGB_SEG_LEN * (RGB_ANCHORS - 1))   /* 600: 红→黄→绿→浅蓝→深蓝→紫→红 */
#define RGB_BRI_FLOOR 20    /* 亮度下限: 拖到底也按 20% 出光, 防止灯光消失 */

/* 用户指定锚点色, 段间线性插值出过渡色 */
static const uint8_t s_rgb_key[RGB_ANCHORS][3] = {
    {0xFF, 0x00, 0x00},   /* 红   */
    {0x73, 0x8C, 0x00},   /* 黄   */
    {0x00, 0xFE, 0x01},   /* 绿   */
    {0x00, 0x5C, 0xA3},   /* 浅蓝 */
    {0x13, 0x00, 0xEC},   /* 深蓝 */
    {0x6C, 0x00, 0x93},   /* 紫   */
    {0xFF, 0x00, 0x00},   /* 红   */
};

/* 滑条位置 → 锚点间插值 RGB */
static void rgb_pos_to_color(uint32_t pos, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (pos > RGB_POS_MAX) pos = RGB_POS_MAX;
    uint32_t seg = pos / RGB_SEG_LEN;
    if (seg >= RGB_ANCHORS - 1) seg = RGB_ANCHORS - 2;
    int32_t frac = (int32_t)(pos - seg * RGB_SEG_LEN);
    const uint8_t *c0 = s_rgb_key[seg];
    const uint8_t *c1 = s_rgb_key[seg + 1];
    *r = (uint8_t)(c0[0] + ((int32_t)c1[0] - c0[0]) * frac / RGB_SEG_LEN);
    *g = (uint8_t)(c0[1] + ((int32_t)c1[1] - c0[1]) * frac / RGB_SEG_LEN);
    *b = (uint8_t)(c0[2] + ((int32_t)c1[2] - c0[2]) * frac / RGB_SEG_LEN);
}

static void rgb_light_apply_light(void)
{
    lv_obj_t *slider1 = guider_ui.RGBLight_slider_1;
    lv_obj_t *slider2 = guider_ui.RGBLight_slider_2;
    if (!lv_obj_is_valid(slider1) || !lv_obj_is_valid(slider2))
        return;

    int32_t bri = lv_slider_get_value(slider1);
    int32_t eff = RGB_BRI_FLOOR + bri * (LIGHTCT_BRIGHTNESS_MAX - RGB_BRI_FLOOR) / LIGHTCT_BRIGHTNESS_MAX;  /* 套 20% 下限 */
    uint8_t r, g, b;
    rgb_pos_to_color((uint32_t)lv_slider_get_value(slider2), &r, &g, &b);

    uint8_t opa_r = (uint8_t)((uint32_t)r * eff / LIGHTCT_BRIGHTNESS_MAX);
    uint8_t opa_g = (uint8_t)((uint32_t)g * eff / LIGHTCT_BRIGHTNESS_MAX);
    uint8_t opa_b = (uint8_t)((uint32_t)b * eff / LIGHTCT_BRIGHTNESS_MAX);
    if (!HWInterface.RGBLight.switch_status)
        opa_r = opa_g = opa_b = 0;

    lv_obj_set_style_img_opa(guider_ui.RGBLight_Red,   opa_r, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.RGBLight_Green, opa_g, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(guider_ui.RGBLight_Blue,  opa_b, LV_PART_MAIN | LV_STATE_DEFAULT);

    char buf[32];
    lv_snprintf(buf, sizeof(buf), "亮 度 | %d%%", (int)bri);
    lv_label_set_text(guider_ui.RGBLight_label_1, buf);
    lv_snprintf(buf, sizeof(buf), "颜 色 | #%02X%02X%02X", r, g, b);
    lv_label_set_text(guider_ui.RGBLight_label_2, buf);
}

/* 共用: 刷灯光图+标签+开关UI */
static void rgb_light_refresh(bool btn_status)
{
    rgb_light_apply_light();

    if (btn_status) lv_obj_add_state(guider_ui.RGBLight_on_off_2_img, LV_STATE_CHECKED);
    else            lv_obj_clear_state(guider_ui.RGBLight_on_off_2_img, LV_STATE_CHECKED);

    if (btn_status) {
        lv_obj_set_style_bg_opa(guider_ui.RGBLight_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_background(guider_ui.RGBLight_cont_1);
    } else {
        lv_obj_set_style_bg_opa(guider_ui.RGBLight_cont_1, 162, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_move_foreground(guider_ui.RGBLight_cont_1);
        lv_obj_move_foreground(guider_ui.RGBLight_on_off_2_img);
    }
}

/* ══════ 4 个事件接口(供 GUI-Guider 事件一行调用) ══════ */

void rgb_light_on_screen_load(void)
{
    lv_slider_set_range(guider_ui.RGBLight_slider_1, 1, LIGHTCT_BRIGHTNESS_MAX);
    lv_slider_set_range(guider_ui.RGBLight_slider_2, 0, RGB_POS_MAX);
    lv_slider_set_value(guider_ui.RGBLight_slider_1, HWInterface.LightCT.brightness, LV_ANIM_OFF);
    lv_slider_set_value(guider_ui.RGBLight_slider_2, s_color_pos, LV_ANIM_OFF);
    rgb_light_refresh(HWInterface.RGBLight.switch_status);

    /* 按下反馈: 降透明度(松手自动还原) */
    lv_obj_t *btns[] = { guider_ui.RGBLight_on_off_2_img, guider_ui.RGBLight_imgbtn_1 };
    for (uint8_t i = 0; i < 2; i++) {
        lv_obj_set_style_img_opa(btns[i], 128, LV_PART_MAIN | LV_STATE_PRESSED);   /* 按下 50% 透明 */
        lv_obj_set_ext_click_area(btns[i], 30);   /* 热区各+30px,图片不变 */
    }

    /* cont_2 情景面板: 滑出/收回/模态/图片反馈 见 scene_panel 模块 */
    scene_panel_setup(&s_panel, guider_ui.RGBLight, guider_ui.RGBLight_cont_2,
                      guider_ui.RGBLight_imgbtn_1, guider_ui.RGBLight_on_off_2_img,
                      rgb_light_refresh);
}

void rgb_light_on_switch_toggle(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    bool btn_status = lv_obj_has_state(btn, LV_STATE_CHECKED);

    HWInterface.RGBLight.SetOnOff(btn_status);
    hw_cloud_post(&(HW_Msg){ .type = HW_MSG_LIGHT_RGB_SWITCH, .on = btn_status });
    scene_panel_on_power(&s_panel, btn_status);   /* 开/关灯; 关时面板若开先收回再上遮罩 */
}

void rgb_light_on_bri_slider_change(void)
{
    HWInterface.LightCT.SetBrightness((uint16_t)lv_slider_get_value(guider_ui.RGBLight_slider_1));
    rgb_light_apply_light();
    if (lv_tick_elaps(s_bri_tick) >= APPLY_MIN_MS) {
        s_bri_tick = lv_tick_get();
        hw_cloud_post(&(HW_Msg){ .type = HW_MSG_LIGHT_CT_BRI, .val = HWInterface.LightCT.brightness });
    }
}

void rgb_light_on_color_slider_change(void)
{
    s_color_pos = (uint16_t)lv_slider_get_value(guider_ui.RGBLight_slider_2);
    rgb_light_apply_light();
    if (lv_tick_elaps(s_color_tick) >= APPLY_MIN_MS) {
        s_color_tick = lv_tick_get();
        uint8_t r, g, b;
        rgb_pos_to_color(s_color_pos, &r, &g, &b);
        uint16_t rgb565 = (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
        hw_cloud_post(&(HW_Msg){ .type = HW_MSG_LIGHT_RGB_COLOR, .val = rgb565 });
    }
}
