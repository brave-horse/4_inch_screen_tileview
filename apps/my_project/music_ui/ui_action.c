/*
 * ============================================================================
 *  my_project UI 总入口 (GUI Guider 生成的 UI)
 *  本文件覆盖 lvgl_main.c 中的弱函数 jl_gui_init()，由 LVGL 主任务调用。
 *  调用链：app_main() -> lvgl_main_task_init() -> lvgl_v8_main_task()
 *          -> jl_gui_init()  (即本文件)
 * ============================================================================
 */
#include "app_config.h"
#ifdef CONFIG_UI_ENABLE

#include "lvgl.h"
#include "gui_guider.h"     /* GUI Guider 生成的总头文件，提供 setup_ui / lv_ui */
#include "events_init.h"    /* GUI Guider 生成的事件绑定 */
#include "custom.h"         /* 用户自定义初始化，含 pulldown_init */

/* GUI Guider 生成的 UI 全局对象，保存所有页面/控件句柄
 * gui_guider.h 中已 extern 声明，此处给出唯一定义 */
lv_ui guider_ui;

/*
 * UI 初始化入口（被 LVGL 主任务调用一次）
 * 作用：创建所有页面，注册事件回调，并执行自定义初始化
 */
void jl_gui_init(void)
{
#if LV_USE_MONKEY != 0
    /* ========== Monkey 测试（自动随机操作，仅在压力测试时启用） ========== */
    lv_monkey_config_t monkey_pointer_config;
    monkey_pointer_config.type = LV_INDEV_TYPE_POINTER;
    monkey_pointer_config.period_range.min = 20;
    monkey_pointer_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_pointer_config), true);

    lv_monkey_config_t monkey_keypad_config;
    monkey_keypad_config.type = LV_INDEV_TYPE_KEYPAD;
    monkey_keypad_config.period_range.min = 20;
    monkey_keypad_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_keypad_config), true);

    lv_monkey_config_t monkey_encode_config;
    monkey_encode_config.type = LV_INDEV_TYPE_ENCODER;
    monkey_encode_config.period_range.min = 20;
    monkey_encode_config.period_range.max = 20;
    monkey_encode_config.input_range.min = -5;
    monkey_encode_config.input_range.max = 5;
    lv_monkey_set_enable(lv_monkey_create(&monkey_encode_config), true);
#endif

    /* 1. 创建所有页面（GUI Guider 自动生成）
     * 实现见 music_ui/generated/gui_guider.c: setup_ui() */
    setup_ui(&guider_ui);

    /* 2. 绑定所有页面控件的事件回调
     * 实现见 music_ui/generated/events_init.c */
    events_init(&guider_ui);

    /* 3. 用户自定义初始化（含安卓下拉手势）
     * 实现见 music_ui/custom/custom.c */
    custom_init(&guider_ui);
}

#endif //CONFIG_UI_ENABLE
