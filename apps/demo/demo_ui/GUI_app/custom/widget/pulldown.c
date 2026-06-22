/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include "lvgl.h"
#include "pulldown.h"

/*********************
 *      DEFINES
 *********************/

/* 安卓式顶部下拉面板(单面板版, 参考 dem3333 的 pulldown 简化而来)。
 *
 * 用 GUI-Guider 在主屏画好的 ui_home_screen_cont_1 当下拉页(它已被摆在屏外 (0,-600)):
 *   1. 开机 pulldown_init 把它从 ui_home_screen 挪到 lv_layer_top, 藏在屏幕正上方并隐藏;
 *   2. 定时(20ms)扫触摸点, 从屏幕顶部 40px 内"竖直向下"滑 -> 面板跟手滑下露出;
 *   3. 松手时按"露出是否超过一半"决定展开(贴顶)或收起(缩回屏外);
 *   4. 展开后任意位置上滑可收起。
 *
 * 注: 面板挪到 lv_layer_top 后不再随主屏 auto_del 销毁, s_panel 一直有效;
 *     主屏每次重建虽会再造一个屏内 cont_1 "幽灵", 但它在屏外(0,-600)不可见、且随旧屏删除,
 *     不累积也不挡事, 这里不用管它。 */

#define PULLDOWN_START_EDGE   40    /* 只有从屏幕顶部 40px 内开始下滑才触发(收窄, 避开标签栏/按钮防误触) */
#define PULLDOWN_DRAG_START   8     /* 移动超过 8px 才认定为拖拽(防误触) */
#define PULLDOWN_ANIM_TIME    220   /* 拖动松手 展开/收起动画时间, ms */
#define PULLDOWN_BTN_COLLAPSE_TIME 500  /* 点按钮后收起动画时间(慢一点), ms */

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t   *s_panel    = NULL;  /* 下拉面板(ui_home_screen_cont_1, 已挪到 layer_top) */
static lv_timer_t *s_timer    = NULL;
static lv_coord_t  s_panel_h  = 0;     /* 面板高度 = 下拉完全露出的高度 */
static bool        s_open      = false; /* 当前是否已展开 */
static bool        s_tracking  = false; /* 本次按下是否在跟踪 */
static bool        s_dragging  = false; /* 是否已进入拖拽 */
static lv_point_t  s_start;             /* 按下起点 */
static lv_coord_t  s_start_y   = 0;     /* 拖拽开始时面板的 y */
static lv_indev_t *s_indev     = NULL;
static bool        s_locked     = false; /* 是否已锁住本次输入(防下层控件抢) */

/* 面板内 4 个图标按钮 + 睡眠图标(init 时捕获真身, 不依赖会变成幽灵的 guider_ui.*) */
static lv_obj_t *s_btn_set       = NULL; /* MainSetBtn → 设置 */
static lv_obj_t *s_btn_sleep     = NULL; /* btn_4 → 睡眠切换 */
static lv_obj_t *s_btn_manual    = NULL; /* btn_5 → 手册(Helper) */
static lv_obj_t *s_btn_home      = NULL; /* btn_6 → 收起面板 */
static lv_obj_t *s_img_sleep_off = NULL; /* img_2 月亮关 */
static lv_obj_t *s_img_sleep_on  = NULL; /* img_6 月亮开 */
static bool      s_sleep_on      = false;
static lv_obj_t *s_backdrop      = NULL; /* 全屏透明遮罩: 面板下方拦截外部点击→收回 */

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void pulldown_set_y(void *obj, int32_t y);
static void pulldown_hide_ready_cb(lv_anim_t *a);
static void pulldown_anim_to(lv_coord_t end_y, lv_anim_ready_cb_t ready_cb);
static void pulldown_show(void);
static void pulldown_hide(void);
static void pulldown_prepare(lv_obj_t *p);
static void pulldown_timer_cb(lv_timer_t *t);
static void pulldown_collapse_slow(void);
static void pulldown_bind_btn(lv_obj_t *btn, lv_event_cb_t cb);
static void on_set_clicked(lv_event_t *e);
static void on_sleep_clicked(lv_event_t *e);
static void on_manual_clicked(lv_event_t *e);
static void on_home_clicked(lv_event_t *e);
static void on_backdrop_clicked(lv_event_t *e);
static void pulldown_backdrop_set(bool show);

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

void pulldown_init(lv_ui *ui)
{
    if (s_timer != NULL) {
        return;                         /* 已初始化, 防重复 */
    }
    if (ui == NULL || ui->ui_home_screen_cont_1 == NULL) {
        return;                         /* GUI-Guider 里没画 cont_1 就不启用 */
    }
    s_panel = ui->ui_home_screen_cont_1;
    pulldown_prepare(s_panel);

    /* 捕获面板内 4 个图标按钮真身(此刻 guider_ui 仍指向真实控件;
     * 之后主屏重建只改 guider_ui 指向幽灵, 这些 static 仍指 layer_top 上真身, 不受影响) */
    s_btn_set       = ui->ui_home_screen_MainSetBtn;
    s_btn_sleep     = ui->ui_home_screen_btn_4;
    s_btn_manual    = ui->ui_home_screen_btn_5;
    s_btn_home      = ui->ui_home_screen_btn_6;
    s_img_sleep_off = ui->ui_home_screen_img_2;
    s_img_sleep_on  = ui->ui_home_screen_img_6;

    pulldown_bind_btn(s_btn_set,    on_set_clicked);
    pulldown_bind_btn(s_btn_sleep,  on_sleep_clicked);
    pulldown_bind_btn(s_btn_manual, on_manual_clicked);
    pulldown_bind_btn(s_btn_home,   on_home_clicked);

    /* 图标(图层在按钮上)默认 CLICKABLE 会吃掉点击 → 清掉, 让点击落到下面的按钮 */
    lv_obj_t *glyphs[] = { ui->ui_home_screen_img_2, ui->ui_home_screen_img_6,
                           ui->ui_home_screen_img_4, ui->ui_home_screen_img_3,
                           ui->ui_home_screen_MainSetImg };
    for (uint8_t i = 0; i < 5; i++) {
        if (glyphs[i]) lv_obj_clear_flag(glyphs[i], LV_OBJ_FLAG_CLICKABLE);
    }

    /* 全屏透明遮罩: 平时隐藏; 面板展开时显示在面板下方, 点它(=点面板外)即收回 */
    s_backdrop = lv_obj_create(lv_layer_top());
    lv_obj_remove_style_all(s_backdrop);
    lv_obj_set_size(s_backdrop, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_pos(s_backdrop, 0, 0);
    lv_obj_set_style_bg_opa(s_backdrop, LV_OPA_TRANSP, 0);
    lv_obj_clear_flag(s_backdrop, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(s_backdrop, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(s_backdrop, on_backdrop_clicked, LV_EVENT_CLICKED, NULL);
    lv_obj_move_foreground(s_panel);   /* 面板压在遮罩之上 */

    /* 睡眠图标初始: 关(img_2)显示, 开(img_6)透明 */
    if (s_img_sleep_off) lv_obj_set_style_img_opa(s_img_sleep_off, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (s_img_sleep_on)  lv_obj_set_style_img_opa(s_img_sleep_on,  0,   LV_PART_MAIN | LV_STATE_DEFAULT);

    s_timer = lv_timer_create(pulldown_timer_cb, 20, NULL);
}

/**********************
 *  STATIC FUNCTIONS
 **********************/

/* 收起后任意键: 清掉按钮上 GUI-Guider 的旧绑定(防双触发), 换成 pulldown 自己的 CLICKED 回调 */
static void pulldown_bind_btn(lv_obj_t *btn, lv_event_cb_t cb)
{
    if (btn == NULL) return;
    while (lv_obj_remove_event_cb(btn, NULL)) ;   /* NULL=删第一个, 循环清空 */
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);
}

/* 显示/隐藏遮罩(显示时压在面板下、其余之上) */
static void pulldown_backdrop_set(bool show)
{
    if (s_backdrop == NULL) return;
    if (show) {
        lv_obj_clear_flag(s_backdrop, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(s_backdrop);
        lv_obj_move_foreground(s_panel);   /* 面板再压在遮罩之上 */
    } else {
        lv_obj_add_flag(s_backdrop, LV_OBJ_FLAG_HIDDEN);
    }
}

/* 点面板外部(遮罩) → 收回面板 */
static void on_backdrop_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    pulldown_hide();
}

/* 点按钮后慢速收起面板(动画, 比拖动松手更慢, 看着顺) */
static void pulldown_collapse_slow(void)
{
    if (s_panel == NULL) return;
    pulldown_backdrop_set(false);        /* 点按钮收起也撤遮罩 */
    lv_anim_del(s_panel, pulldown_set_y);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, s_panel);
    lv_anim_set_exec_cb(&a, pulldown_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(s_panel), -s_panel_h);
    lv_anim_set_time(&a, PULLDOWN_BTN_COLLAPSE_TIME);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&a, pulldown_hide_ready_cb);
    lv_anim_start(&a);
    s_open = false;
}

/* btn_4 → 切换睡眠: 蓝/img_6(月亮开)  ↔  白/img_2(月亮关) */
static void on_sleep_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    s_sleep_on = !s_sleep_on;
    if (s_btn_sleep)     lv_obj_set_style_bg_color(s_btn_sleep, lv_color_hex(s_sleep_on ? 0x2195f6 : 0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    if (s_img_sleep_off) lv_obj_set_style_img_opa(s_img_sleep_off, s_sleep_on ? 0   : 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (s_img_sleep_on)  lv_obj_set_style_img_opa(s_img_sleep_on,  s_sleep_on ? 255 : 0,   LV_PART_MAIN | LV_STATE_DEFAULT);
}

/* btn_6 房子 → 回主页: 不在主页就加载主页, 然后慢速收起面板 */
static void on_home_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    if (lv_scr_act() != guider_ui.ui_home_screen) {
        ui_load_scr_animation(&guider_ui, &guider_ui.ui_home_screen, guider_ui.ui_home_screen_del,
            &guider_ui.ui_home_screen_del, setup_scr_ui_home_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
    }
    pulldown_collapse_slow();
}

/* MainSetBtn → 进设置屏并慢速收起面板 */
static void on_set_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del,
        &guider_ui.ui_home_screen_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
    pulldown_collapse_slow();
}

/* btn_5 → 进手册(Helper)屏并慢速收起面板 */
static void on_manual_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_load_scr_animation(&guider_ui, &guider_ui.Helper, guider_ui.Helper_del,
        &guider_ui.ui_home_screen_del, setup_scr_Helper, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
    pulldown_collapse_slow();
}

static void pulldown_set_y(void *obj, int32_t y)
{
    lv_obj_set_y((lv_obj_t *)obj, (lv_coord_t)y);
    /* 面板透明+在 layer_top, 收起向上滑腾出的区域底下首页不会自动重画→残影(白条);
     * 强制重绘当前活动屏清掉残影。只在滑动/动画期间发生, 开销可接受。 */
    lv_obj_t *scr = lv_scr_act();
    if (scr) lv_obj_invalidate(scr);
}

static void pulldown_hide_ready_cb(lv_anim_t *a)
{
    LV_UNUSED(a);
    lv_obj_add_flag(s_panel, LV_OBJ_FLAG_HIDDEN);   /* 收起动画结束后彻底隐藏 */
}

static void pulldown_anim_to(lv_coord_t end_y, lv_anim_ready_cb_t ready_cb)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, s_panel);
    lv_anim_set_exec_cb(&a, pulldown_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(s_panel), end_y);
    lv_anim_set_time(&a, PULLDOWN_ANIM_TIME);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    if (ready_cb) {
        lv_anim_set_ready_cb(&a, ready_cb);
    }
    lv_anim_start(&a);
}

static void pulldown_show(void)
{
    lv_anim_del(s_panel, pulldown_set_y);
    lv_obj_clear_flag(s_panel, LV_OBJ_FLAG_HIDDEN);
    pulldown_backdrop_set(true);         /* 展开时挂遮罩, 点外部可收回 */
    pulldown_anim_to(0, NULL);           /* 贴顶展开 */
    s_open = true;
}

static void pulldown_hide(void)
{
    lv_anim_del(s_panel, pulldown_set_y);
    pulldown_backdrop_set(false);        /* 收起即撤遮罩, 不挡下层 */
    pulldown_anim_to(-s_panel_h, pulldown_hide_ready_cb);   /* 缩回屏外 */
    s_open = false;
}

/* 面板初始化: 挪到顶层、藏在屏幕正上方、隐藏。保留 GUI-Guider 给的尺寸/样式不动。 */
static void pulldown_prepare(lv_obj_t *p)
{
    lv_obj_update_layout(p);
    s_panel_h = lv_obj_get_height(p);
    if (s_panel_h <= 0) {
        s_panel_h = 320;                 /* 兜底 */
    }
    lv_obj_set_parent(p, lv_layer_top());
    lv_obj_set_pos(p, 0, -s_panel_h);    /* 藏在屏幕正上方(底边贴屏顶) */
    lv_obj_set_scrollbar_mode(p, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(p, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(p, LV_OBJ_FLAG_SCROLLABLE);
}

static void pulldown_timer_cb(lv_timer_t *t)
{
    lv_indev_t *indev;
    lv_indev_t *pressed = NULL;
    lv_point_t  pt;
    lv_coord_t  dy;
    lv_coord_t  y;

    LV_UNUSED(t);

    if (s_panel == NULL || !lv_obj_is_valid(s_panel)) {
        return;
    }

    /* 找一个"正按下"的指针(触摸)设备 */
    for (indev = lv_indev_get_next(NULL); indev; indev = lv_indev_get_next(indev)) {
        if (lv_indev_get_type(indev) == LV_INDEV_TYPE_POINTER &&
            indev->proc.state == LV_INDEV_STATE_PRESSED) {
            pressed = indev;
            break;
        }
    }

    /* 松手: 结束本次拖拽, 按露出比例决定展开/收起 */
    if (pressed == NULL) {
        if (s_dragging) {
            lv_coord_t reveal = s_panel_h + lv_obj_get_y(s_panel);   /* 已露出高度(0~panel_h) */
            if (reveal >= s_panel_h / 2) {
                pulldown_show();
            } else {
                pulldown_hide();
            }
        }
        s_tracking = false;
        s_dragging = false;
        s_indev    = NULL;
        s_locked   = false;
        return;
    }

    s_indev = pressed;
    lv_indev_get_point(pressed, &pt);

    if (!s_tracking) {
        s_start    = pt;
        s_tracking = true;
        s_dragging = false;
        if (s_open) {
            s_start_y = 0;                  /* 已展开: 任意位置都能上拉收起 */
        } else if (pt.y <= PULLDOWN_START_EDGE) {
            s_start_y = -s_panel_h;         /* 收起态: 只有顶部边缘下滑才拉得出 */
        } else {
            s_tracking = false;             /* 起点不在顶部, 本次不管 */
            return;
        }
    }

    dy = pt.y - s_start.y;

    if (!s_dragging) {
        lv_coord_t dx = pt.x - s_start.x;

        /* 收紧判定防误触, 任一不满足就直接 return 把这次按压交还给下层控件(按钮/滚动),
         * 且此刻尚未锁输入(延后锁) :
         *   1) 移动要超过阈值;
         *   2) 必须"竖直主导"(|dy|>|dx|): 横滑、点按钮的小斜抖都不当下拉;
         *   3) 方向要对: 收起态只认向下滑(dy>0)拉出, 展开态只认向上滑(dy<0)收起。 */
        if (LV_ABS(dy) < PULLDOWN_DRAG_START) {
            return;                         /* 移动太小, 还不算拖拽 */
        }
        if (LV_ABS(dy) <= LV_ABS(dx)) {
            return;                         /* 不是竖直主导(横向/斜向), 不抢 */
        }
        if (!s_open && dy <= 0) {
            return;                         /* 收起态只响应向下滑 */
        }
        if (s_open && dy >= 0) {
            return;                         /* 展开态只响应向上滑 */
        }
        s_dragging = true;
        lv_anim_del(s_panel, pulldown_set_y);
        lv_obj_clear_flag(s_panel, LV_OBJ_FLAG_HIDDEN);
        pulldown_backdrop_set(true);   /* 拖动露出即挂遮罩 */
    }

    /* 跟手移动面板 y, 限制在 [-panel_h, 0] */
    y = s_start_y + dy;
    if (y > 0) {
        y = 0;
    }
    if (y < -s_panel_h) {
        y = -s_panel_h;
    }
    lv_obj_set_y(s_panel, y);
    {   /* 手动拖动收起同样会腾出区域, 强制重绘首页清残影 */
        lv_obj_t *scr = lv_scr_act();
        if (scr) lv_obj_invalidate(scr);
    }

    /* 一旦进入拖拽, 锁住本次按压, 防止下面的按钮/控件误响应 */
    if (s_dragging && !s_locked && s_indev != NULL) {
        lv_indev_wait_release(s_indev);
        s_locked = true;
    }
}
