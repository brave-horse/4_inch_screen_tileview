#include "lvgl.h"
#include "gui_guider.h"
#include "PlaySet.h"
#include "HWDataAccess.h"

/* 显示设置: 三栏手风琴折叠菜单。
 * List 三栏(延时/待机/接近) + 三个 tileview(选项列表) 并入 List 的 flex;
 * 点栏展开对应 tileview(手风琴, 同时只开一栏), List flex 自动把后面栏下推;
 * 选中选项即收起 + 更新栏右值 label + 写中间层。 */

typedef struct {
    lv_obj_t  *item;        /* List 栏(点击展开) */
    lv_obj_t  *tileview;    /* 选项面板 */
    lv_obj_t  *val_label;   /* 栏右当前值(label_1/2/3) */
    lv_obj_t  *opt_btn[7];  /* 选项单选圈(按 idx 顺序) */
    lv_obj_t  *opt_txt[7];  /* 选项文本(按 idx, 取文字更新值) */
    uint8_t    opt_n;       /* 选项数 */
    void     (*set_fn)(uint8_t);   /* 写中间层 */
} SetGroup;

static SetGroup s_groups[3];

/* 收起全部 tileview */
static void collapse_all(void)
{
    for (uint8_t g = 0; g < 3; g++)
        if (lv_obj_is_valid(s_groups[g].tileview))
            lv_obj_add_flag(s_groups[g].tileview, LV_OBJ_FLAG_HIDDEN);
}

/* 点栏: 手风琴。本栏已展开则收起; 否则收起其余、展开本栏 */
static void accordion_toggle(uint8_t g)
{
    lv_obj_t *tv = s_groups[g].tileview;
    bool was_open = !lv_obj_has_flag(tv, LV_OBJ_FLAG_HIDDEN);
    collapse_all();
    if (!was_open) lv_obj_clear_flag(tv, LV_OBJ_FLAG_HIDDEN);
}

/* 选中 g 组第 opt 项: 单选打勾 + 栏右值更新 + 收起 + 写中间层 */
static void option_pick(uint8_t g, uint8_t opt)
{
    SetGroup *grp = &s_groups[g];
    for (uint8_t i = 0; i < grp->opt_n; i++) {
        if (i == opt) lv_obj_add_state(grp->opt_btn[i], LV_STATE_CHECKED);
        else          lv_obj_clear_state(grp->opt_btn[i], LV_STATE_CHECKED);
    }
    lv_label_set_text(grp->val_label, lv_label_get_text(grp->opt_txt[opt]));
    lv_obj_add_flag(grp->tileview, LV_OBJ_FLAG_HIDDEN);   /* 选中即收起 */
    if (grp->set_fn) grp->set_fn(opt);                    /* 写中间层 */
}

/* ── 事件回调: user_data 传索引 ── */
static void item_click_cb(lv_event_t *event)
{
    accordion_toggle((uint8_t)(uintptr_t)lv_event_get_user_data(event));
}
static void option_click_cb(lv_event_t *event)
{
    uintptr_t packed = (uintptr_t)lv_event_get_user_data(event);   /* (group<<8)|opt */
    option_pick((uint8_t)(packed >> 8), (uint8_t)(packed & 0xff));
}

/* ── 屏幕加载(events_init 在 SCREEN_LOADED 挂) ── */
void playset_on_screen_load(void)
{
    lv_obj_t *list = guider_ui.PlaySet_List;

    /* 1) 三组映射(idx 按显示顺序; 待机/接近的 btn 编号是倒序) */
    s_groups[0] = (SetGroup){
        .item = guider_ui.PlaySet_List_item0, .tileview = guider_ui.PlaySet_tileview_1,
        .val_label = guider_ui.PlaySet_label_1, .opt_n = 7,
        .opt_btn = { guider_ui.PlaySet_btn_5, guider_ui.PlaySet_btn_6, guider_ui.PlaySet_btn_7,
                     guider_ui.PlaySet_btn_8, guider_ui.PlaySet_btn_9, guider_ui.PlaySet_btn_10, guider_ui.PlaySet_btn_11 },
        .opt_txt = { guider_ui.PlaySet_label_5, guider_ui.PlaySet_label_6, guider_ui.PlaySet_label_7,
                     guider_ui.PlaySet_label_8, guider_ui.PlaySet_label_9, guider_ui.PlaySet_label_10, guider_ui.PlaySet_label_11 },
        .set_fn = HWInterface.Display.SetStandbyDelay,
    };
    s_groups[1] = (SetGroup){
        .item = guider_ui.PlaySet_List_item1, .tileview = guider_ui.PlaySet_tileview_2,
        .val_label = guider_ui.PlaySet_label_2, .opt_n = 7,
        .opt_btn = { guider_ui.PlaySet_btn_18, guider_ui.PlaySet_btn_17, guider_ui.PlaySet_btn_16,
                     guider_ui.PlaySet_btn_15, guider_ui.PlaySet_btn_14, guider_ui.PlaySet_btn_13, guider_ui.PlaySet_btn_12 },
        .opt_txt = { guider_ui.PlaySet_label_18, guider_ui.PlaySet_label_17, guider_ui.PlaySet_label_16,
                     guider_ui.PlaySet_label_15, guider_ui.PlaySet_label_14, guider_ui.PlaySet_label_13, guider_ui.PlaySet_label_12 },
        .set_fn = HWInterface.Display.SetStandbyDisplay,
    };
    s_groups[2] = (SetGroup){
        .item = guider_ui.PlaySet_List_item2, .tileview = guider_ui.PlaySet_tileview_3,
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

    /* 2) tileview 并入 List flex: set_parent 到末尾, 再 move 到对应 item 后
     *    末尾[item0,item1,item2,tv1,tv2,tv3] → tv1→1,tv2→3,tv3→5 = [i0,tv1,i1,tv2,i2,tv3] */
    for (uint8_t g = 0; g < 3; g++)
        lv_obj_set_parent(s_groups[g].tileview, list);
    lv_obj_move_to_index(s_groups[0].tileview, 1);
    lv_obj_move_to_index(s_groups[1].tileview, 3);
    lv_obj_move_to_index(s_groups[2].tileview, 5);

    /* 2b) 值 label + 箭头 img 并入对应 item, 跟 flex 一起下推(否则展开时它们绝对定位不动、错位)。
     *     img_2/4/3 分别是延时/待机/接近栏的右箭头(按 y 对应)。 */
    lv_obj_t *arrow[3] = { guider_ui.PlaySet_img_2, guider_ui.PlaySet_img_4, guider_ui.PlaySet_img_3 };
    for (uint8_t g = 0; g < 3; g++) {
        /* 并入 item 跟下推, 但 set_pos 用原设计相对位置(原绝对 - item content左上≈(36,111)),
         * 位置保持你 GUI-Guider 的设计、不被 align 改动。三栏 offset 相同(各 item 高一致)。 */
        lv_obj_set_parent(s_groups[g].val_label, s_groups[g].item);
        lv_obj_set_pos(s_groups[g].val_label, 497, 3);    /* 值 label 原(533,114) */
        if (lv_obj_is_valid(arrow[g])) {
            lv_obj_set_parent(arrow[g], s_groups[g].item);
            lv_obj_set_pos(arrow[g], 631, 31);            /* 箭头 原(667,142) */
        }
    }

    /* 3) 每组: tileview 宽对齐+隐藏; 选项圈 CHECKABLE+选中样式; 整行(圈+文本)挂点击; 初始化当前值 */
    for (uint8_t g = 0; g < 3; g++) {
        SetGroup *grp = &s_groups[g];

        lv_obj_set_width(grp->tileview, lv_pct(100));            /* 宽度跟 List */
        lv_obj_add_flag(grp->tileview, LV_OBJ_FLAG_HIDDEN);     /* 默认收起 */

        lv_obj_add_flag(grp->item, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(grp->item, item_click_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)g);

        for (uint8_t i = 0; i < grp->opt_n; i++) {
            /* 单选圈: CHECKED 填充蓝(实心), 默认空心(setup 已给蓝 border) */
            lv_obj_add_flag(grp->opt_btn[i], LV_OBJ_FLAG_CHECKABLE);
            lv_obj_set_style_bg_color(grp->opt_btn[i], lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(grp->opt_btn[i], LV_OPA_COVER, LV_PART_MAIN | LV_STATE_CHECKED);

            /* 整行可点: 透明 overlay 盖住整行捕获点击, 完全不碰文字 label */
            void *packed = (void *)(((uintptr_t)g << 8) | i);
            lv_obj_t *tile = lv_obj_get_parent(grp->opt_btn[i]);
            lv_obj_t *ov   = lv_obj_create(tile);
            lv_obj_remove_style_all(ov);                   /* 透明无边框, 不遮下面的文字/圈 */
            lv_obj_set_pos(ov, 0, i * 75);                 /* 行高 75 = 选项 btn 间隔 */
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
