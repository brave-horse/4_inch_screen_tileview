#include "scene_panel.h"

/* 4 个灯屏 cont_2 是同模板: 524x392, 开在 (92,227), 收起藏到屏外上方 */
#define SP_OPEN_X     92
#define SP_OPEN_Y     200
#define SP_HIDDEN_Y   (-392)    /* = -面板高度, 完全藏到屏幕上方 */
#define SP_OPEN_MS    700       /* 展开时长 */
#define SP_CLOSE_MS   300       /* 收回更快 */

static void sp_anim_y_cb(void *var, int32_t value)
{
    lv_obj_set_y((lv_obj_t *)var, value);
}

/* 收回动画结束: 若是总开关关触发的收回, 此刻才上遮罩(先收回后遮罩) */
static void sp_anim_ready_cb(lv_anim_t *anim)
{
    ScenePanel *panel = lv_obj_get_user_data((lv_obj_t *)anim->var);   //setup 时存进 cont
    if (!panel) return;
    if (!panel->open && panel->refresh_off_after_close) {
        panel->refresh_off_after_close = false;
        if (panel->refresh) panel->refresh(false);
    }
}

/* 展开/收回: 同步 imgbtn 图标, 开时显捕获层并把开关/imgbtn/面板提到其上, 竖向滑(收回更快) */
static void sp_set_open(ScenePanel *panel, bool open)
{
    if (!lv_obj_is_valid(panel->cont)) return;
    panel->open = open;
    if (open) panel->refresh_off_after_close = false;   //重开则取消待上遮罩

    if (lv_obj_is_valid(panel->trigger)) {
        if (open) lv_obj_add_state(panel->trigger, LV_STATE_CHECKED);   //图标切"关闭"
        else      lv_obj_clear_state(panel->trigger, LV_STATE_CHECKED);
    }
    if (open) {
        if (lv_obj_is_valid(panel->overlay)) {
            lv_obj_clear_flag(panel->overlay, LV_OBJ_FLAG_HIDDEN);   //显示捕获层
            lv_obj_move_foreground(panel->overlay);
        }
        if (lv_obj_is_valid(panel->power))   lv_obj_move_foreground(panel->power);   //开关留捕获层之上
        if (lv_obj_is_valid(panel->trigger)) lv_obj_move_foreground(panel->trigger);
        lv_obj_move_foreground(panel->cont);   //面板最上
    } else if (lv_obj_is_valid(panel->overlay)) {
        lv_obj_add_flag(panel->overlay, LV_OBJ_FLAG_HIDDEN);   //收回: 隐藏捕获层, 滑块恢复
    }
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, panel->cont);
    lv_anim_set_exec_cb(&anim, sp_anim_y_cb);
    lv_anim_set_values(&anim, lv_obj_get_y(panel->cont), open ? SP_OPEN_Y : SP_HIDDEN_Y);
    lv_anim_set_time(&anim, open ? SP_OPEN_MS : SP_CLOSE_MS);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_out);
    lv_anim_set_ready_cb(&anim, sp_anim_ready_cb);
    lv_anim_start(&anim);
}

static void sp_trigger_cb(lv_event_t *e)     //imgbtn_1 toggle: 开/收
{
    ScenePanel *panel = lv_event_get_user_data(e);
    sp_set_open(panel, lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED));
}

static void sp_overlay_cb(lv_event_t *e)     //捕获层被点(滑块/空白)→收回
{
    ScenePanel *panel = lv_event_get_user_data(e);
    if (panel->open) sp_set_open(panel, false);
}

static void sp_img_cb(lv_event_t *e)         //面板内图片点击→收回(按下减半由PRESSED样式做)
{
    sp_set_open((ScenePanel *)lv_event_get_user_data(e), false);
}

void scene_panel_setup(ScenePanel *panel, lv_obj_t *screen, lv_obj_t *cont,
                       lv_obj_t *trigger, lv_obj_t *power, void (*refresh)(bool))
{
    panel->cont    = cont;
    panel->trigger = trigger;
    panel->power   = power;
    panel->refresh = refresh;
    panel->open    = false;
    panel->refresh_off_after_close = false;

    if (lv_obj_is_valid(cont)) {
        lv_obj_set_user_data(cont, panel);            //anim ready_cb 取 panel 用
        lv_obj_set_x(cont, SP_OPEN_X);                //x 固定, 只竖向滑
        lv_obj_set_y(cont, SP_HIDDEN_Y);             //起始藏屏外
        lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE); //吸收面板背景点击, 不外漏
        uint32_t cnt = lv_obj_get_child_cnt(cont);   //cnt 子控件数
        for (uint32_t i = 0; i < cnt; i++) {
            lv_obj_t *child = lv_obj_get_child(cont, i);
            if (!lv_obj_check_type(child, &lv_img_class)) continue;
            lv_obj_add_flag(child, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_img_opa(child, LV_OPA_50, LV_PART_MAIN | LV_STATE_PRESSED);   //按下减半, 松手还原
            lv_obj_remove_event_cb(child, sp_img_cb);   //清旧绑定防重复
            lv_obj_add_event_cb(child, sp_img_cb, LV_EVENT_CLICKED, panel);
        }
    }
    if (lv_obj_is_valid(trigger)) {
        lv_obj_clear_state(trigger, LV_STATE_CHECKED);   //默认收起
        lv_obj_remove_event_cb(trigger, sp_trigger_cb);
        lv_obj_add_event_cb(trigger, sp_trigger_cb, LV_EVENT_VALUE_CHANGED, panel);
    }
    /* 模态捕获层: 全屏透明可点, 创建一次(屏常驻则复用), 默认隐藏 */
    if (lv_obj_is_valid(screen)) {
        if (!lv_obj_is_valid(panel->overlay) || lv_obj_get_parent(panel->overlay) != screen) {
            panel->overlay = lv_obj_create(screen);
            lv_obj_remove_style_all(panel->overlay);
            lv_obj_set_pos(panel->overlay, 0, 0);
            lv_obj_set_size(panel->overlay, 720, 720);
            lv_obj_set_style_bg_opa(panel->overlay, LV_OPA_TRANSP, 0);   //全透明
            lv_obj_clear_flag(panel->overlay, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_flag(panel->overlay, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_event_cb(panel->overlay, sp_overlay_cb, LV_EVENT_CLICKED, panel);
        }
        lv_obj_add_flag(panel->overlay, LV_OBJ_FLAG_HIDDEN);   //默认收起→隐藏
    }
}

void scene_panel_on_power(ScenePanel *panel, bool on)
{
    if (!on && panel->open) {
        panel->refresh_off_after_close = true;   //先收回, ready_cb 再上遮罩
        sp_set_open(panel, false);
    } else if (panel->refresh) {
        panel->refresh(on);
    }
}
