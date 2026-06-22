/*
 * ============================================================================
 *  wifi_camera UI 总入口
 *  本文件覆盖 lvgl_main.c 中的弱函数 jl_gui_init()，由 LVGL 主任务调用。
 *  调用链：app_main() -> logo_poweron_play_end() -> lvgl_main_task_init()
 *          -> lvgl_v8_main_task() -> jl_gui_init()  (即本文件)
 * ============================================================================
 */
#include "app_config.h"
#ifdef CONFIG_UI_ENABLE

/* 根据配置选择 UI 风格：LY 风格 或 JL 风格（默认 JL） */
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl_v8_ui_app/style_LY/generated/gui_guider.h"
#else
#include "lvgl_v8_ui_app/style_JL/generated/gui_guider.h"
#endif

/* GUI Builder 生成的 UI 全局对象，保存所有页面/控件句柄 */
lv_ui guider_ui;

/*
 * UI 初始化入口（被 LVGL 主任务调用一次）
 * 作用：创建所有页面，注册事件回调，并显示首页
 */
void jl_gui_init(void)
{
#if LV_USE_MONKEY != 0
    /* ========== Monkey 测试（自动随机操作，仅在压力测试时启用） ========== */

    /* 模拟触摸输入：每 20ms 随机点击屏幕 */
    lv_monkey_config_t monkey_pointer_config;
    monkey_pointer_config.type = LV_INDEV_TYPE_POINTER;
    monkey_pointer_config.period_range.min = 20;
    monkey_pointer_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_pointer_config), true);
    
    /* 模拟键盘输入：每 20ms 随机按键 */
    lv_monkey_config_t monkey_keypad_config;
    monkey_keypad_config.type = LV_INDEV_TYPE_KEYPAD;
    monkey_keypad_config.period_range.min = 20;
    monkey_keypad_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_keypad_config), true);

    /* 模拟编码器输入：每 20ms 随机滚动 -5 ~ 5 */
    lv_monkey_config_t monkey_encode_config;
    monkey_encode_config.type = LV_INDEV_TYPE_ENCODER;
    monkey_encode_config.period_range.min = 20;
    monkey_encode_config.period_range.max = 20;
    monkey_encode_config.input_range.min = -5;
    monkey_encode_config.input_range.max = 5;
    lv_monkey_set_enable(lv_monkey_create(&monkey_encode_config), true);
#endif

    /* 创建所有页面并显示首页（GUI Builder 自动生成的代码）
     * 实现见 lvgl_v8_ui_app/style_JL/generated/gui_guider.c: setup_ui()
     * 首页由 setup_ui 内部的 GUI_SCREEN_VIDEO_REC 决定（录像页） */
    setup_ui(&guider_ui);

    /* 绑定所有页面控件的事件回调（按钮点击、滑动等）
     * 实现见 lvgl_v8_ui_app/style_JL/generated/gui_events/events_init.c */
    events_init(&guider_ui);
}

#endif //CONFIG_UI_ENABLE
