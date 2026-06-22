#include "app_config.h"
#ifdef CONFIG_UI_ENABLE

#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl_v8_ui_app/style_LY/generated/gui_guider.h"
#else
#include "lvgl_v8_ui_app/style_JL/generated/gui_guider.h"
#endif

lv_ui guider_ui;
void jl_gui_init(void)
{
#if LV_USE_MONKEY != 0
    /*Create pointer monkey test*/
    lv_monkey_config_t monkey_pointer_config;
    monkey_pointer_config.type = LV_INDEV_TYPE_POINTER;
    monkey_pointer_config.period_range.min = 20;
    monkey_pointer_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_pointer_config), true);

    /*Create keypad monkey test*/
    lv_monkey_config_t monkey_keypad_config;
    monkey_keypad_config.type = LV_INDEV_TYPE_KEYPAD;
    monkey_keypad_config.period_range.min = 20;
    monkey_keypad_config.period_range.max = 20;
    lv_monkey_set_enable(lv_monkey_create(&monkey_keypad_config), true);

    /*Create encoder monkey test*/
    lv_monkey_config_t monkey_encode_config;
    monkey_encode_config.type = LV_INDEV_TYPE_ENCODER;
    monkey_encode_config.period_range.min = 20;
    monkey_encode_config.period_range.max = 20;
    monkey_encode_config.input_range.min = -5;
    monkey_encode_config.input_range.max = 5;
    lv_monkey_set_enable(lv_monkey_create(&monkey_encode_config), true);
#endif
    setup_ui(&guider_ui);//UI初始化，创建界面元素，绑定事件回调等
    events_init(&guider_ui);//UI事件初始化，设置界面元素的事件回调函数等，这两句必须写。写后，将杰理自己的gui生成的代码放在对应的风格里面就行。

    extern void lv_page_map_view_3_create(void);
    lv_page_map_view_3_create();
}
#endif //CONFIG_UI_ENABLE
