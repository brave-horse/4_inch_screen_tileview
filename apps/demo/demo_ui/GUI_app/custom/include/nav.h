#ifndef NAV_H
#define NAV_H

#ifdef __cplusplus
extern "C" {
#endif

/* 屏幕 id: 顺序随意, 屏表用 designated initializer 对齐 */
typedef enum {
    SCR_HOME,
    SCR_LIGHT_CT, SCR_LEDSTRIP, SCR_RGBLIGHT, SCR_MAGLIGHT,
    SCR_FABRICCURTAIN, SCR_SHEERS, SCR_ROLLBLIND, SCR_DREAM,
    SCR_AIRCONDITION, SCR_MUSIC, SCR_DRYRACK, SCR_FANANDLIGHT, SCR_HEATER,
    SCR_SETTING, SCR_NETSETTING, SCR_PLAYSET, SCR_SWITCHSET, SCR_SENSORSET,
    SCR_RESET, SCR_HUIFU, SCR_RELATIVEPRODUCT, SCR_HELPER,
    SCR_COUNT
} ScreenId;

/* 进 target 屏: 把当前屏(若是 home 顺带记当前 tile)压栈。子屏入口按钮用。 */
void nav_go(ScreenId target);

/* 返回上一屏(弹栈)。所有返回按钮用。空栈兜底回主页。 */
void nav_back(void);

/* 清空栈直接回主页 tile_3。下拉面板"房子"按钮用。 */
void nav_go_home(void);

/* Home 加载时取回待恢复 tile(并清除); -1 表示无(用默认主页 tile_3)。 */
int  nav_consume_home_tile(void);

/* Home 加载时取回待恢复的 tile 内部滚动 y(并清除); 0 表示不滚。 */
int  nav_consume_home_scroll(void);

#ifdef __cplusplus
}
#endif

#endif
