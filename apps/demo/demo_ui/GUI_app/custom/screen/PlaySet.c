#include "lvgl.h"
#include "gui_guider.h"
#include "PlaySet.h"
#include "HWDataAccess.h"

/* 显示设置: 三栏手风琴折叠菜单(cont_1/2/3 代替旧 List)。
 * tileview 放在对应 cont 下方, 展开时后推后续 cont; 收起时恢复原位。
 * 不碰 flex——conts 完全保留 GUI-Guider 设的位置/尺寸。 */

#define PLAYSET_PRESS_BG  0x151414   /* 按下底色——改这一个宏即可 */

static void clear_children_clickable(lv_obj_t *obj)
{
	uint32_t cnt = lv_obj_get_child_cnt(obj);
	for (uint32_t ci = 0; ci < cnt; ci++) {
		lv_obj_t *child = lv_obj_get_child(obj, ci);
		lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
		clear_children_clickable(child);
	}
}

typedef struct {
    lv_obj_t  *cont;        /* 本栏容器(点按展开) */
    lv_obj_t  *tileview;    /* 选项面板 */
    lv_obj_t  *val_label;   /* 栏右当前值(label_1/2/3) */
    lv_obj_t  *opt_btn[7];  /* 选项单选圈(按 idx 顺序) */
    lv_obj_t  *opt_txt[7];  /* 选项文本(按 idx, 取文字更新值) */
    uint8_t    opt_n;       /* 选项数 */
    void     (*set_fn)(uint8_t);   /* 写中间层 */
    lv_coord_t cont_y0;     /* cont 初始 y(收起态, GUI-Guider 设的) */
    lv_coord_t cont_h;      /* cont 高度 */
    lv_coord_t tv_h;        /* tileview 高度 */
} SetGroup;

static SetGroup s_groups[3];

/* 收起全部 tileview + 恢复 cont 原位 */
static void collapse_all(void)
{
    for (uint8_t g = 0; g < 3; g++) {
        SetGroup *grp = &s_groups[g];
        if (lv_obj_is_valid(grp->tileview))
            lv_obj_add_flag(grp->tileview, LV_OBJ_FLAG_HIDDEN);
        if (lv_obj_is_valid(grp->cont))
            lv_obj_set_y(grp->cont, grp->cont_y0);
    }
    lv_obj_set_scroll_dir(guider_ui.PlaySet_tabview_1_tab_1, LV_DIR_VER);
}

/* 展开 grp 组 tileview: 收起所有后, 展开本栏, 后推后栏 */
static void accordion_expand(uint8_t g)
{
    collapse_all();
    SetGroup *grp = &s_groups[g];
    lv_obj_clear_flag(grp->tileview, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_scroll_dir(guider_ui.PlaySet_tabview_1_tab_1, LV_DIR_NONE);
    lv_coord_t push = grp->tv_h;
    for (uint8_t j = g + 1; j < 3; j++)
        if (lv_obj_is_valid(s_groups[j].cont))
            lv_obj_set_y(s_groups[j].cont, s_groups[j].cont_y0 + push);
}

static void accordion_toggle(uint8_t g)
{
    SetGroup *grp = &s_groups[g];
    bool was_open = !lv_obj_has_flag(grp->tileview, LV_OBJ_FLAG_HIDDEN);
    if (was_open) collapse_all();
    else          accordion_expand(g);
}

static void option_pick(uint8_t g, uint8_t opt)
{
    SetGroup *grp = &s_groups[g];
    for (uint8_t i = 0; i < grp->opt_n; i++) {
        if (i == opt) lv_obj_add_state(grp->opt_btn[i], LV_STATE_CHECKED);
        else          lv_obj_clear_state(grp->opt_btn[i], LV_STATE_CHECKED);
    }
    lv_label_set_text(grp->val_label, lv_label_get_text(grp->opt_txt[opt]));
    collapse_all();
    if (grp->set_fn) grp->set_fn(opt);
}

static void item_click_cb(lv_event_t *event)
{
    accordion_toggle((uint8_t)(uintptr_t)lv_event_get_user_data(event));
}

static void option_click_cb(lv_event_t *event)
{
    uintptr_t packed = (uintptr_t)lv_event_get_user_data(event);
    option_pick((uint8_t)(packed >> 8), (uint8_t)(packed & 0xff));
}

void playset_on_screen_load(void)
{
    lv_obj_set_scroll_dir(guider_ui.PlaySet_tabview_1_tab_1, LV_DIR_VER);

    s_groups[0] = (SetGroup){
        .cont = guider_ui.PlaySet_cont_1, .tileview = guider_ui.PlaySet_tileview_1,
        .val_label = guider_ui.PlaySet_label_1, .opt_n = 7,
        .opt_btn = { guider_ui.PlaySet_btn_5, guider_ui.PlaySet_btn_6, guider_ui.PlaySet_btn_7,
                     guider_ui.PlaySet_btn_8, guider_ui.PlaySet_btn_9, guider_ui.PlaySet_btn_10, guider_ui.PlaySet_btn_11 },
        .opt_txt = { guider_ui.PlaySet_label_5, guider_ui.PlaySet_label_6, guider_ui.PlaySet_label_7,
                     guider_ui.PlaySet_label_8, guider_ui.PlaySet_label_9, guider_ui.PlaySet_label_10, guider_ui.PlaySet_label_11 },
        .set_fn = HWInterface.Display.SetStandbyDelay,
    };
    s_groups[1] = (SetGroup){
        .cont = guider_ui.PlaySet_cont_2, .tileview = guider_ui.PlaySet_tileview_2,
        .val_label = guider_ui.PlaySet_label_2, .opt_n = 7,
        .opt_btn = { guider_ui.PlaySet_btn_18, guider_ui.PlaySet_btn_17, guider_ui.PlaySet_btn_16,
                     guider_ui.PlaySet_btn_15, guider_ui.PlaySet_btn_14, guider_ui.PlaySet_btn_13, guider_ui.PlaySet_btn_12 },
        .opt_txt = { guider_ui.PlaySet_label_18, guider_ui.PlaySet_label_17, guider_ui.PlaySet_label_16,
                     guider_ui.PlaySet_label_15, guider_ui.PlaySet_label_14, guider_ui.PlaySet_label_13, guider_ui.PlaySet_label_12 },
        .set_fn = HWInterface.Display.SetStandbyDisplay,
    };
    s_groups[2] = (SetGroup){
        .cont = guider_ui.PlaySet_cont_3, .tileview = guider_ui.PlaySet_tileview_3,
        .val_label = guider_ui.PlaySet_label_3, .opt_n = 4,
        .opt_btn = { guider_ui.PlaySet_btn_25, guider_ui.PlaySet_btn_24, guider_ui.PlaySet_btn_23, guider_ui.PlaySet_btn_22 },
        .opt_txt = { guider_ui.PlaySet_label_25, guider_ui.PlaySet_label_24, guider_ui.PlaySet_label_23, guider_ui.PlaySet_label_22 },
        .set_fn = HWInterface.Display.SetProximity,
    };

    uint8_t cur_idx[3] = {
        HWInterface.Display.standby_delay,
        HWInterface.Display.standby_display,
        HWInterface.Display.proximity,
    };

    lv_obj_t *tab = guider_ui.PlaySet_tabview_1_tab_1;
    for (uint8_t g = 0; g < 3; g++) {
        SetGroup *grp = &s_groups[g];
        lv_obj_t *tv = grp->tileview;
        if (lv_obj_get_parent(tv) != tab) lv_obj_set_parent(tv, tab);
        lv_obj_set_width(tv, lv_obj_get_width(grp->cont));
        lv_obj_set_x(tv, lv_obj_get_x(grp->cont));

        lv_obj_update_layout(grp->cont);
        lv_obj_update_layout(tv);
        grp->cont_y0 = lv_obj_get_y(grp->cont);
        grp->cont_h  = lv_obj_get_height(grp->cont);
        grp->tv_h    = lv_obj_get_height(tv);
        lv_obj_set_y(tv, grp->cont_y0 + grp->cont_h);
        lv_obj_add_flag(tv, LV_OBJ_FLAG_HIDDEN);
    }

    /* 三栏 cont: 清子 CLICKABLE + 按下变色 */
    {
        lv_obj_t *conts[] = {
            guider_ui.PlaySet_cont_1,
            guider_ui.PlaySet_cont_2,
            guider_ui.PlaySet_cont_3,
        };
        const uint8_t n = sizeof(conts) / sizeof(conts[0]);
        for (uint8_t i = 0; i < n; i++) {
            lv_obj_t *cont = conts[i];
            if (!lv_obj_is_valid(cont)) continue;
            clear_children_clickable(cont);
            lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(cont, lv_color_hex(PLAYSET_PRESS_BG), LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_PRESSED);
        }
    }

    /* 每组: 挂点击事件 + 选项圈 + 初始化值 */
    for (uint8_t g = 0; g < 3; g++) {
        SetGroup *grp = &s_groups[g];
        lv_obj_add_event_cb(grp->cont, item_click_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)g);

        for (uint8_t i = 0; i < grp->opt_n; i++) {
            lv_obj_add_flag(grp->opt_btn[i], LV_OBJ_FLAG_CHECKABLE);
            lv_obj_set_style_bg_color(grp->opt_btn[i], lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(grp->opt_btn[i], LV_OPA_COVER, LV_PART_MAIN | LV_STATE_CHECKED);

            void *packed = (void *)(((uintptr_t)g << 8) | i);
            lv_obj_t *tile = lv_obj_get_parent(grp->opt_btn[i]);
            lv_obj_t *ov   = lv_obj_create(tile);
            lv_obj_remove_style_all(ov);
            lv_obj_set_pos(ov, 0, i * 75);
            lv_obj_set_size(ov, lv_pct(100), 75);
            lv_obj_add_flag(ov, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_clear_flag(ov, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_event_cb(ov, option_click_cb, LV_EVENT_CLICKED, packed);
        }

        uint8_t cur = cur_idx[g] < grp->opt_n ? cur_idx[g] : 0;
        lv_obj_add_state(grp->opt_btn[cur], LV_STATE_CHECKED);
        lv_label_set_text(grp->val_label, lv_label_get_text(grp->opt_txt[cur]));
    }
}
