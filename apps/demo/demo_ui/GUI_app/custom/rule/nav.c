#include "lvgl.h"
#include "gui_guider.h"
#include "nav.h"

/* 多层导航栈: 记录"从哪来", 返回时回到真实来源屏(而非写死主页)。
 * home 是 tileview, 顺带记录进入时停在哪一格(tile), 返回后恢复(如设备页 tile4)。
 * 前提: 所有屏切换都走本模块(nav_go/nav_back/nav_go_home), s_current 才准确。 */

/*===== 屏表: ScreenId → 屏指针/del标志/setup函数 =====*/
typedef struct {
    lv_obj_t **scr;
    bool      *del;
    void     (*setup)(lv_ui *);
} ScreenDef;

#define SD(name) { &guider_ui.name, &guider_ui.name##_del, setup_scr_##name }

static const ScreenDef s_screens[SCR_COUNT] = {
    [SCR_HOME]            = SD(ui_home_screen),
    [SCR_LIGHT_CT]        = SD(light_CT_screen),
    [SCR_LEDSTRIP]        = SD(LedStrip),
    [SCR_RGBLIGHT]        = SD(RGBLight),
    [SCR_MAGLIGHT]        = SD(MagLight),
    [SCR_FABRICCURTAIN]   = SD(FabricCurtian),
    [SCR_SHEERS]          = SD(Sheers),
    [SCR_ROLLBLIND]       = SD(RollBlind),
    [SCR_DREAM]           = SD(Dream),
    [SCR_AIRCONDITION]    = SD(AirCondition),
    [SCR_MUSIC]           = SD(Music),
    [SCR_DRYRACK]         = SD(DryRack),
    [SCR_FANANDLIGHT]     = SD(FanAndLight),
    [SCR_HEATER]          = SD(Heater),
    [SCR_SETTING]         = SD(setting_screen),
    [SCR_NETSETTING]      = SD(NetSetting),
    [SCR_PLAYSET]         = SD(PlaySet),
    [SCR_SWITCHSET]       = SD(SwitchSet),
    [SCR_SENSORSET]       = SD(SensorSet),
    [SCR_RESET]           = SD(Reset),
    [SCR_HUIFU]           = SD(huifuchuchangshezhi),
    [SCR_RELATIVEPRODUCT] = SD(RelativeProduct),
    [SCR_HELPER]          = SD(Helper),
};

/*===== 栈 =====*/
#define NAV_STACK_MAX  8
typedef struct { ScreenId scr; uint8_t home_tile; } NavEntry;
static NavEntry  s_stack[NAV_STACK_MAX];
static uint8_t   s_top = 0;
static ScreenId  s_current = SCR_HOME;       /* 当前屏(开机停 home) */
static int       s_pending_home_tile = -1;   /* 返回 home 时待恢复的 tile, -1=无 */

/* 读 home tileview 当前停在第几格(col); 读不到给主页 3 */
static uint8_t home_cur_tile(void)
{
    lv_obj_t *tv = guider_ui.ui_home_screen_tileview_1;
    if (!lv_obj_is_valid(tv)) return 3;
    lv_obj_t *act = lv_tileview_get_tile_act(tv);
    lv_obj_t *tiles[7] = {
        guider_ui.ui_home_screen_tileview_1_tile_0, guider_ui.ui_home_screen_tileview_1_tile_1,
        guider_ui.ui_home_screen_tileview_1_tile_2, guider_ui.ui_home_screen_tileview_1_tile_3,
        guider_ui.ui_home_screen_tileview_1_tile_4, guider_ui.ui_home_screen_tileview_1_tile_5,
        guider_ui.ui_home_screen_tileview_1_tile_6,
    };
    for (uint8_t idx = 0; idx < 7; idx++)        /* idx index */
        if (tiles[idx] == act) return idx;
    return 3;
}

/* 按屏表加载 target; 旧屏 del 标志自动取当前屏 */
static void nav_load(ScreenId target)
{
    if (target >= SCR_COUNT) return;
    const ScreenDef *to   = &s_screens[target];
    const ScreenDef *from = &s_screens[s_current];
    ui_load_scr_animation(&guider_ui, to->scr, *to->del, from->del,
                          to->setup, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
    s_current = target;
}

void nav_go(ScreenId target)
{
    if (s_top < NAV_STACK_MAX) {
        s_stack[s_top].scr       = s_current;
        s_stack[s_top].home_tile = (s_current == SCR_HOME) ? home_cur_tile() : 3;
        s_top++;
    }
    nav_load(target);
}

void nav_back(void)
{
    if (s_top == 0) {                 /* 空栈兜底回主页 */
        s_pending_home_tile = -1;
        nav_load(SCR_HOME);
        return;
    }
    NavEntry entry = s_stack[--s_top];
    s_pending_home_tile = (entry.scr == SCR_HOME) ? (int)entry.home_tile : -1;
    nav_load(entry.scr);
}

void nav_go_home(void)
{
    s_top = 0;
    s_pending_home_tile = 3;          /* 回主页 tile_3 */
    nav_load(SCR_HOME);
}

int nav_consume_home_tile(void)
{
    int tile = s_pending_home_tile;
    s_pending_home_tile = -1;
    return tile;
}
