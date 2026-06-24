#include "lvgl.h"
#include "gui_guider.h"
#include "NetSetting.h"

/* 网络设置三状态(互斥, 每态只显示自己那组, 其余 HIDDEN):
 *   0 未绑定: 二维码 img_3 + "设备未绑定" label_3 + "开始绑定" btn_3
 *   1 绑定中: img_4 + label_4
 *   2 已绑定: img_5 + "解除设备" btn_5
 * 标题 NetSet / 返回 img_1,btn_1 常显, 不参与切换。 */
typedef enum { NET_UNBOUND = 0, NET_BINDING, NET_BOUND } NetState;

static void obj_show(lv_obj_t *obj, bool show)
{
    if (!obj) return;
    if (show) lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    else      lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

static void netset_apply_state(NetState st)
{
    obj_show(guider_ui.NetSetting_label_3, st == NET_UNBOUND);
    obj_show(guider_ui.NetSetting_btn_3,   st == NET_UNBOUND);
    obj_show(guider_ui.NetSetting_img_3,   st == NET_UNBOUND);
    obj_show(guider_ui.NetSetting_label_4, st == NET_BINDING);
    obj_show(guider_ui.NetSetting_img_4,   st == NET_BINDING);
    obj_show(guider_ui.NetSetting_btn_5,   st == NET_BOUND);
    obj_show(guider_ui.NetSetting_img_5,   st == NET_BOUND);
}

/* 点"开始绑定" → 进绑定中 */
static void btn_start_bind_cb(lv_event_t *event)
{
    LV_UNUSED(event);
    netset_apply_state(NET_BINDING);
    /* TODO: 触发实际配网流程; 配网成功后由外部调 netsetting_set_bound() 切已绑定 */
}

/* 点"解除设备" → 回未绑定 */
static void btn_unbind_cb(lv_event_t *event)
{
    LV_UNUSED(event);
    netset_apply_state(NET_UNBOUND);
    /* TODO: 触发实际解绑 */
}

/* ── 屏幕加载(events_init 在 SCREEN_LOADED 调) ── */
void netsetting_on_screen_load(void)
{
    if (lv_obj_is_valid(guider_ui.NetSetting_btn_3))
        lv_obj_add_event_cb(guider_ui.NetSetting_btn_3, btn_start_bind_cb, LV_EVENT_CLICKED, NULL);
    if (lv_obj_is_valid(guider_ui.NetSetting_btn_5))
        lv_obj_add_event_cb(guider_ui.NetSetting_btn_5, btn_unbind_cb, LV_EVENT_CLICKED, NULL);
    netset_apply_state(NET_UNBOUND);   /* 进屏: 未绑定 */
}

/* 外部接口: 配网完成时调, 切到已绑定状态(显示解除按钮) */
void netsetting_set_bound(void)
{
    netset_apply_state(NET_BOUND);
}
