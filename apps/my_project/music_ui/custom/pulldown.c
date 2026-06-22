/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "pulldown.h"

#define PULLDOWN_SWITCH_DRAG_LIMIT  (LV_HOR_RES / 2)

/*********************
 *      DEFINES
 *********************/

/*******************************安卓下拉参数开始****************************/
#define PULLDOWN_START_EDGE         90              /* 只有从屏幕顶部 90 像素内开始滑动才触发 */
#define PULLDOWN_DRAG_START_DIST    8               /* 向下滑动超过 8 像素后开始露出下拉页 */
#define PULLDOWN_SETTLE_DIST        (LV_VER_RES / 3) /* 松手时露出超过 1/3 屏幕就全部展开 */
#define PULLDOWN_SWITCH_START_DIST  8               /* 左右滑动超过 8 像素后开始切换下拉页 */
#define PULLDOWN_SWITCH_SETTLE_DIST (LV_HOR_RES / 3) /* 松手时横向滑出超过 1/3 屏幕就切换 */
#define PULLDOWN_ANIM_TIME          220             /* 下拉/收起动画时间，单位 ms */
/*******************************安卓下拉参数结束****************************/

/**********************
 *      TYPEDEFS
 **********************/

/*******************************安卓下拉类型开始****************************/
typedef enum {
    PULLDOWN_PANEL_NONE = 0,    /* 当前没有下拉页显示 */
    PULLDOWN_PANEL_LEFT,        /* 左侧下拉页：screen_cont_1 */
    PULLDOWN_PANEL_RIGHT        /* 右侧下拉页：screen_cont_2 */
} pulldown_panel_t;

typedef enum {
    PULLDOWN_DRAG_MODE_NONE = 0, /* 尚未确认拖拽方向 */
    PULLDOWN_DRAG_MODE_VERTICAL, /* 上下拖动：下拉或收起面板 */
    PULLDOWN_DRAG_MODE_HORIZONTAL /* 左右拖动：在 cont_1 和 cont_2 间切换 */
} pulldown_drag_mode_t;
/*******************************安卓下拉类型结束****************************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/*******************************安卓下拉函数声明开始****************************/
/* 初始化下拉面板位置和属性：挂到顶层，默认隐藏在屏幕上方。 */
static void pulldown_prepare_panel(lv_obj_t *panel);

/* 定时轮询输入设备，识别顶部下拉手势并驱动拖拽流程。 */
static void pulldown_indev_timer_cb(lv_timer_t *timer);

/* LVGL 动画执行回调：设置对象的 Y 坐标。 */
static void pulldown_set_y(void *obj, int32_t y);

/* LVGL 动画执行回调：设置对象的 X 坐标。 */
static void pulldown_set_x(void *obj, int32_t x);

/* 根据面板枚举获取对应的下拉面板对象。 */
static lv_obj_t *pulldown_get_panel(pulldown_panel_t panel);

/* 获取与指定面板相对的另一个下拉面板对象。 */
static lv_obj_t *pulldown_get_other_panel(pulldown_panel_t panel);

/* 根据当前横向滑动方向获取要切换出来的面板。 */
static pulldown_panel_t pulldown_get_horizontal_target(pulldown_panel_t panel, lv_coord_t delta_x);

/* 开始拖拽指定面板，隐藏另一侧面板并取消旧动画。 */
static void pulldown_begin_drag(pulldown_panel_t panel);

/* 根据当前触点位置判断拖拽方向，并分发给竖向或横向拖拽逻辑。 */
static void pulldown_update_drag(const lv_point_t *point);

/* 根据当前触点位置更新竖向拖拽中的面板 Y 坐标。 */
static void pulldown_update_vertical_drag(const lv_point_t *point);

/* 结束拖拽，根据露出距离决定展开或收起面板。 */
static void pulldown_finish_drag(void);

/* 开始横向拖拽，准备当前面板和目标面板的位置。 */
static void pulldown_begin_horizontal_drag(pulldown_panel_t from_panel, pulldown_panel_t to_panel);

/* 根据当前触点位置更新横向拖拽中的两个面板 X 坐标。 */
static void pulldown_update_horizontal_drag(const lv_point_t *point);

/* 结束横向拖拽，根据滑出距离决定切换或回弹。 */
static void pulldown_finish_horizontal_drag(void);

/* 启动面板 X 坐标动画。 */
static void pulldown_anim_x(lv_obj_t *obj, lv_coord_t end_x);

/* 动画展开指定下拉面板。 */
static void pulldown_show(pulldown_panel_t panel);

/* 动画收起当前激活的下拉面板。 */
static void pulldown_hide(void);

/* 横向切换动画结束后隐藏非当前面板。 */
static void pulldown_switch_ready_cb(lv_anim_t *anim);

/* 收起动画结束后隐藏面板对象。 */
static void pulldown_hide_ready_cb(lv_anim_t *anim);
/*******************************安卓下拉函数声明结束****************************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*******************************安卓下拉变量开始****************************/
static lv_obj_t *s_left_panel = NULL;
static lv_obj_t *s_right_panel = NULL;
static lv_timer_t *s_pulldown_timer = NULL;
static pulldown_panel_t s_active_panel = PULLDOWN_PANEL_NONE;
static bool s_touch_tracking = false;
static bool s_touch_dragging = false;
static pulldown_drag_mode_t s_drag_mode = PULLDOWN_DRAG_MODE_NONE;
static pulldown_panel_t s_drag_panel = PULLDOWN_PANEL_NONE;
static pulldown_panel_t s_switch_from_panel = PULLDOWN_PANEL_NONE;
static pulldown_panel_t s_switch_to_panel = PULLDOWN_PANEL_NONE;
static lv_coord_t s_drag_start_panel_y = 0;
static lv_point_t s_touch_start;
/*******************************安卓下拉变量结束****************************/

/*******************************安卓下拉逻辑开始****************************/
void pulldown_init(lv_ui *ui)
{
    if (s_pulldown_timer != NULL) {
        return;
    }

    s_left_panel = ui->screen_cont_1;
    s_right_panel = ui->screen_cont_2;

    /* 使用 GUI Guider 创建好的两个容器作为下拉页，不在代码里新建页面 */
    pulldown_prepare_panel(s_left_panel);
    pulldown_prepare_panel(s_right_panel);

    /* 定时扫描触摸点，实现任意控件上都能从顶部下拉 */
    s_pulldown_timer = lv_timer_create(pulldown_indev_timer_cb, 20, NULL);
}

static void pulldown_prepare_panel(lv_obj_t *panel)
{
    if (panel == NULL) {
        return;
    }

    lv_obj_set_parent(panel, lv_layer_top());
    lv_obj_set_size(panel, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_pos(panel, 0, -LV_VER_RES);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_GESTURE_BUBBLE);
}

static void pulldown_indev_timer_cb(lv_timer_t *timer)
{
    lv_indev_t *indev = lv_indev_get_next(NULL);
    lv_indev_t *pressed_indev = NULL;
    lv_point_t point;

    LV_UNUSED(timer);

    while (indev != NULL) {
        lv_indev_type_t type = lv_indev_get_type(indev);

        if ((type == LV_INDEV_TYPE_POINTER || type == LV_INDEV_TYPE_BUTTON) &&
            indev->proc.state == LV_INDEV_STATE_PRESSED) {
            pressed_indev = indev;
            break;
        }

        indev = lv_indev_get_next(indev);
    }

    if (pressed_indev == NULL) {
        if (s_drag_mode == PULLDOWN_DRAG_MODE_HORIZONTAL) {
            pulldown_finish_horizontal_drag();
        }
        else {
            pulldown_finish_drag();
        }

        s_touch_tracking = false;
        s_touch_dragging = false;
        s_drag_mode = PULLDOWN_DRAG_MODE_NONE;
        s_drag_panel = PULLDOWN_PANEL_NONE;
        s_switch_from_panel = PULLDOWN_PANEL_NONE;
        s_switch_to_panel = PULLDOWN_PANEL_NONE;
        return;
    }

    lv_indev_get_point(pressed_indev, &point);

    if (!s_touch_tracking) {
        /* 记录按下起点，用起点判断是左侧下拉还是右侧下拉 */
        s_touch_start = point;
        s_touch_tracking = true;
        s_touch_dragging = false;
        s_drag_mode = PULLDOWN_DRAG_MODE_NONE;
        s_switch_from_panel = PULLDOWN_PANEL_NONE;
        s_switch_to_panel = PULLDOWN_PANEL_NONE;

        if (s_active_panel != PULLDOWN_PANEL_NONE) {
            s_drag_panel = s_active_panel;
            s_drag_start_panel_y = lv_obj_get_y(pulldown_get_panel(s_drag_panel));
        }
        else if (s_touch_start.y <= PULLDOWN_START_EDGE) {
            /* 起点在屏幕左半边显示 cont_1，右半边显示 cont_2 */
            s_drag_panel = (s_touch_start.x < (LV_HOR_RES / 2)) ? PULLDOWN_PANEL_LEFT : PULLDOWN_PANEL_RIGHT;
            s_drag_start_panel_y = -LV_VER_RES;
        }
        else {
            s_drag_panel = PULLDOWN_PANEL_NONE;
        }
    }

    if (s_drag_panel == PULLDOWN_PANEL_NONE) {
        return;
    }

    pulldown_update_drag(&point);
}

static void pulldown_set_y(void *obj, int32_t y)
{
    lv_obj_set_y((lv_obj_t *)obj, (lv_coord_t)y);
}

static void pulldown_set_x(void *obj, int32_t x)
{
    lv_obj_set_x((lv_obj_t *)obj, (lv_coord_t)x);
}

static lv_obj_t *pulldown_get_panel(pulldown_panel_t panel)
{
    if (panel == PULLDOWN_PANEL_LEFT) {
        return s_left_panel;
    }

    if (panel == PULLDOWN_PANEL_RIGHT) {
        return s_right_panel;
    }

    return NULL;
}

static lv_obj_t *pulldown_get_other_panel(pulldown_panel_t panel)
{
    if (panel == PULLDOWN_PANEL_LEFT) {
        return s_right_panel;
    }

    if (panel == PULLDOWN_PANEL_RIGHT) {
        return s_left_panel;
    }

    return NULL;
}

static pulldown_panel_t pulldown_get_horizontal_target(pulldown_panel_t panel, lv_coord_t delta_x)
{
    if (panel == PULLDOWN_PANEL_RIGHT && delta_x > 0) {
        return PULLDOWN_PANEL_LEFT;
    }

    if (panel == PULLDOWN_PANEL_LEFT && delta_x < 0) {
        return PULLDOWN_PANEL_RIGHT;
    }

    return PULLDOWN_PANEL_NONE;
}

static void pulldown_begin_drag(pulldown_panel_t panel)
{
    lv_obj_t *target = pulldown_get_panel(panel);
    lv_obj_t *other = pulldown_get_other_panel(panel);

    if (target == NULL) {
        return;
    }

    if (other != NULL) {
        /* 同一时间只显示一个下拉页 */
        lv_anim_del(other, pulldown_set_x);
        lv_anim_del(other, pulldown_set_y);
        lv_obj_set_x(other, 0);
        lv_obj_add_flag(other, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_y(other, -LV_VER_RES);
    }

    s_active_panel = panel;
    s_drag_mode = PULLDOWN_DRAG_MODE_VERTICAL;
    lv_anim_del(target, pulldown_set_x);
    lv_anim_del(target, pulldown_set_y);
    lv_obj_set_x(target, 0);
    lv_obj_set_y(target, s_drag_start_panel_y);
    lv_obj_clear_flag(target, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_to_index(target, -1);
}

static void pulldown_update_drag(const lv_point_t *point)
{
    lv_coord_t delta_x = point->x - s_touch_start.x;
    lv_coord_t delta_y = point->y - s_touch_start.y;
    lv_coord_t abs_x = LV_ABS(delta_x);
    lv_coord_t abs_y = LV_ABS(delta_y);
    pulldown_panel_t switch_target;

    if (!s_touch_dragging) {
        if (s_active_panel != PULLDOWN_PANEL_NONE &&
            abs_x >= PULLDOWN_SWITCH_START_DIST &&
            abs_x > abs_y) {
            switch_target = pulldown_get_horizontal_target(s_active_panel, delta_x);

            if (switch_target != PULLDOWN_PANEL_NONE) {
                pulldown_begin_horizontal_drag(s_active_panel, switch_target);
                pulldown_update_horizontal_drag(point);
            }

            return;
        }

        if (abs_y < PULLDOWN_DRAG_START_DIST || abs_y < abs_x) {
            return;
        }
    }

    if (s_drag_mode == PULLDOWN_DRAG_MODE_HORIZONTAL) {
        pulldown_update_horizontal_drag(point);
        return;
    }

    pulldown_update_vertical_drag(point);
}

static void pulldown_update_vertical_drag(const lv_point_t *point)
{
    lv_obj_t *target = pulldown_get_panel(s_drag_panel);
    lv_coord_t delta_y = point->y - s_touch_start.y;
    lv_coord_t y;

    if (target == NULL) {
        return;
    }

    if (!s_touch_dragging) {
        if (s_drag_start_panel_y <= -LV_VER_RES) {
            if (delta_y < PULLDOWN_DRAG_START_DIST) {
                return;
            }
        }
        else {
            if (delta_y > -PULLDOWN_DRAG_START_DIST && delta_y < PULLDOWN_DRAG_START_DIST) {
                return;
            }
        }

        pulldown_begin_drag(s_drag_panel);
        s_touch_dragging = true;
    }

    y = s_drag_start_panel_y + delta_y;

    if (y > 0) {
        y = 0;
    }

    if (y < -LV_VER_RES) {
        y = -LV_VER_RES;
    }

    /* 手指没有松开时，下拉页一直跟随手指上下移动 */
    lv_obj_set_y(target, y);
}

static void pulldown_finish_drag(void)
{
    lv_obj_t *target;
    lv_coord_t reveal_dist;

    if (!s_touch_tracking || !s_touch_dragging || s_drag_panel == PULLDOWN_PANEL_NONE) {
        return;
    }

    target = pulldown_get_panel(s_drag_panel);
    if (target == NULL) {
        return;
    }

    reveal_dist = LV_VER_RES + lv_obj_get_y(target);

    if (s_drag_start_panel_y == 0) {
        /* 已经展开的页面，向上拖超过 1/3 屏幕后收起 */
        if (lv_obj_get_y(target) <= -PULLDOWN_SETTLE_DIST) {
            pulldown_hide();
        }
        else {
            pulldown_show(s_drag_panel);
        }
    }
    else {
        /* 从顶部拉出的页面，松手时露出超过 1/3 屏幕就展开，否则收起 */
        if (reveal_dist >= PULLDOWN_SETTLE_DIST) {
            pulldown_show(s_drag_panel);
        }
        else {
            pulldown_hide();
        }
    }
}

static void pulldown_begin_horizontal_drag(pulldown_panel_t from_panel, pulldown_panel_t to_panel)
{
    lv_obj_t *from = pulldown_get_panel(from_panel);
    lv_obj_t *to = pulldown_get_panel(to_panel);
    lv_coord_t to_start_x;

    if (from == NULL || to == NULL) {
        return;
    }

    to_start_x = (to_panel == PULLDOWN_PANEL_LEFT) ? -LV_HOR_RES : LV_HOR_RES;

    lv_anim_del(from, pulldown_set_x);
    lv_anim_del(from, pulldown_set_y);
    lv_anim_del(to, pulldown_set_x);
    lv_anim_del(to, pulldown_set_y);

    lv_obj_clear_flag(from, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(to, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_pos(from, 0, 0);
    lv_obj_set_pos(to, to_start_x, 0);

    lv_obj_move_to_index(from, -1);
    lv_obj_move_to_index(to, -1);

    s_drag_mode = PULLDOWN_DRAG_MODE_HORIZONTAL;
    s_touch_dragging = true;
    s_switch_from_panel = from_panel;
    s_switch_to_panel = to_panel;
}

static void pulldown_update_horizontal_drag(const lv_point_t *point)
{
    lv_obj_t *from = pulldown_get_panel(s_switch_from_panel);
    lv_obj_t *to = pulldown_get_panel(s_switch_to_panel);
    lv_coord_t delta_x = point->x - s_touch_start.x;
    lv_coord_t from_x;
    lv_coord_t to_x;

    if (from == NULL || to == NULL) {
        return;
    }

    if (s_switch_to_panel == PULLDOWN_PANEL_LEFT) {
        if (delta_x < 0) {
            delta_x = 0;
        }
        if (delta_x > PULLDOWN_SWITCH_DRAG_LIMIT) {
            delta_x = PULLDOWN_SWITCH_DRAG_LIMIT;
        }

        from_x = 0;
        to_x = delta_x - LV_HOR_RES;
    }
    else {
        if (delta_x > 0) {
            delta_x = 0;
        }
        if (delta_x < -PULLDOWN_SWITCH_DRAG_LIMIT) {
            delta_x = -PULLDOWN_SWITCH_DRAG_LIMIT;
        }

        from_x = 0;
        to_x = delta_x + LV_HOR_RES;
    }

    lv_obj_set_x(from, from_x);
    lv_obj_set_x(to, to_x);
}

static void pulldown_finish_horizontal_drag(void)
{
    lv_obj_t *from = pulldown_get_panel(s_switch_from_panel);
    lv_obj_t *to = pulldown_get_panel(s_switch_to_panel);
    lv_coord_t reveal_dist;

    if (!s_touch_tracking || !s_touch_dragging ||
        s_switch_from_panel == PULLDOWN_PANEL_NONE ||
        s_switch_to_panel == PULLDOWN_PANEL_NONE ||
        from == NULL || to == NULL) {
        return;
    }

    reveal_dist = LV_HOR_RES - LV_ABS(lv_obj_get_x(to));

    if (reveal_dist >= PULLDOWN_SWITCH_SETTLE_DIST) {
        s_active_panel = s_switch_to_panel;
        lv_obj_set_x(from, 0);
        pulldown_anim_x(to, 0);
    }
    else {
        s_active_panel = s_switch_from_panel;
        lv_obj_set_x(from, 0);
        pulldown_anim_x(to, (s_switch_to_panel == PULLDOWN_PANEL_LEFT) ? -LV_HOR_RES : LV_HOR_RES);
    }
}

static void pulldown_anim_x(lv_obj_t *obj, lv_coord_t end_x)
{
    lv_anim_t anim;

    if (obj == NULL) {
        return;
    }

    lv_anim_del(obj, pulldown_set_x);

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_exec_cb(&anim, pulldown_set_x);
    lv_anim_set_values(&anim, lv_obj_get_x(obj), end_x);
    lv_anim_set_time(&anim, PULLDOWN_ANIM_TIME);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&anim, pulldown_switch_ready_cb);
    lv_anim_start(&anim);
}

static void pulldown_show(pulldown_panel_t panel)
{
    lv_obj_t *target = pulldown_get_panel(panel);
    lv_obj_t *other = pulldown_get_other_panel(panel);
    lv_anim_t anim;
    lv_coord_t start_y;

    if (target == NULL) {
        return;
    }

    if (other != NULL) {
        /* 同一时间只显示一个下拉页 */
        lv_anim_del(other, pulldown_set_x);
        lv_obj_set_x(other, 0);
        lv_obj_add_flag(other, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_y(other, -LV_VER_RES);
    }

    s_active_panel = panel;
    lv_anim_del(target, pulldown_set_x);
    lv_anim_del(target, pulldown_set_y);
    lv_obj_set_x(target, 0);
    lv_obj_clear_flag(target, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_to_index(target, -1);
    start_y = lv_obj_get_y(target);

    if (start_y < -LV_VER_RES || start_y > 0) {
        start_y = -LV_VER_RES;
        lv_obj_set_y(target, start_y);
    }

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, target);
    lv_anim_set_exec_cb(&anim, pulldown_set_y);
    lv_anim_set_values(&anim, start_y, 0);
    lv_anim_set_time(&anim, PULLDOWN_ANIM_TIME);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_start(&anim);
}

static void pulldown_hide(void)
{
    lv_obj_t *target = pulldown_get_panel(s_active_panel);
    lv_anim_t anim;

    if (target == NULL) {
        return;
    }

    lv_anim_del(target, pulldown_set_y);
    lv_anim_del(target, pulldown_set_x);
    lv_obj_set_x(target, 0);

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, target);
    lv_anim_set_exec_cb(&anim, pulldown_set_y);
    lv_anim_set_values(&anim, lv_obj_get_y(target), -LV_VER_RES);
    lv_anim_set_time(&anim, PULLDOWN_ANIM_TIME);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&anim, pulldown_hide_ready_cb);
    lv_anim_start(&anim);

    s_active_panel = PULLDOWN_PANEL_NONE;
}

static void pulldown_switch_ready_cb(lv_anim_t *anim)
{
    lv_obj_t *panel = (lv_obj_t *)anim->var;

    if (panel == pulldown_get_panel(s_active_panel)) {
        lv_obj_t *other = pulldown_get_other_panel(s_active_panel);

        lv_obj_clear_flag(panel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(panel, 0, 0);

        if (other != NULL) {
            lv_anim_del(other, pulldown_set_x);
            lv_obj_set_x(other, 0);
            lv_obj_add_flag(other, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else {
        lv_obj_add_flag(panel, LV_OBJ_FLAG_HIDDEN);
    }
}

static void pulldown_hide_ready_cb(lv_anim_t *anim)
{
    lv_obj_t *panel = (lv_obj_t *)anim->var;

    lv_obj_add_flag(panel, LV_OBJ_FLAG_HIDDEN);
}
/*******************************安卓下拉逻辑结束****************************/
