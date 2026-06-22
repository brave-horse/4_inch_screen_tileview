/**
 * @file lv_demo_keypad_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_keypad_encoder.h"

#if LV_USE_DEMO_KEYPAD_AND_ENCODER

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void selectors_create(lv_obj_t *parent);
static void text_input_create(lv_obj_t *parent);
/* ------------------- NEW ------------------- */
static void images_create(lv_obj_t *parent, bool start_timer);
static void tab_changed_cb(lv_event_t *e);
/* ----------------- END NEW ----------------- */
static void msgbox_create(void);

static void msgbox_event_cb(lv_event_t *e);
static void ta_event_cb(lv_event_t *e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t *g;
static lv_obj_t *tv;
static lv_obj_t *t1;
static lv_obj_t *t2;
/* ------------------- NEW ------------------- */
static lv_obj_t *t3;
static bool first_play_done = false;
/* ----------------- END NEW ----------------- */

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_keypad_encoder(void)
{
    g = lv_group_create();
    lv_group_set_default(g);

    lv_indev_t *indev = NULL;
    for (;;) {
        indev = lv_indev_get_next(indev);
        if (!indev) {
            break;
        }

        lv_indev_type_t indev_type = lv_indev_get_type(indev);
        if (indev_type == LV_INDEV_TYPE_KEYPAD) {
            lv_indev_set_group(indev, g);
        }

        if (indev_type == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(indev, g);
        }
    }

    tv = lv_tabview_create(lv_screen_active());

    t1 = lv_tabview_add_tab(tv, "Selectors");
    t2 = lv_tabview_add_tab(tv, "Text input");
    /* ------------------- NEW ------------------- */
    t3 = lv_tabview_add_tab(tv, "Images");
    /* ----------------- END NEW ----------------- */

    selectors_create(t1);
    text_input_create(t2);
    /* ------------------- NEW: 懒加载 -- 切到 t3 才加载图片 ------------------- */
    lv_obj_add_event_cb(tv, tab_changed_cb, LV_EVENT_VALUE_CHANGED, NULL);
    /* ----------------- END NEW ----------------- */

    msgbox_create();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t *parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *obj;

    obj = lv_table_create(parent);
    lv_table_set_cell_value(obj, 0, 0, "00");
    lv_table_set_cell_value(obj, 0, 1, "01");
    lv_table_set_cell_value(obj, 1, 0, "10");
    lv_table_set_cell_value(obj, 1, 1, "11");
    lv_table_set_cell_value(obj, 2, 0, "20");
    lv_table_set_cell_value(obj, 2, 1, "21");
    lv_table_set_cell_value(obj, 3, 0, "30");
    lv_table_set_cell_value(obj, 3, 1, "31");
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_calendar_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_buttonmatrix_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_checkbox_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_slider_create(parent);
    lv_slider_set_range(obj, 0, 10);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_switch_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_spinbox_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_dropdown_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_roller_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_t *list = lv_list_create(parent);
    lv_obj_update_layout(list);
    if (lv_obj_get_height(list) > lv_obj_get_content_height(parent)) {
        lv_obj_set_height(list, lv_obj_get_content_height(parent));
    }

    lv_list_add_button(list, LV_SYMBOL_OK, "Apply");
    lv_list_add_button(list, LV_SYMBOL_CLOSE, "Close");
    lv_list_add_button(list, LV_SYMBOL_EYE_OPEN, "Show");
    lv_list_add_button(list, LV_SYMBOL_EYE_CLOSE, "Hide");
    lv_list_add_button(list, LV_SYMBOL_TRASH, "Delete");
    lv_list_add_button(list, LV_SYMBOL_COPY, "Copy");
    lv_list_add_button(list, LV_SYMBOL_PASTE, "Paste");
}

static void text_input_create(lv_obj_t *parent)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    lv_obj_t *ta1 = lv_textarea_create(parent);
    lv_obj_set_width(ta1, LV_PCT(100));
    lv_textarea_set_one_line(ta1, true);
    lv_textarea_set_placeholder_text(ta1, "Click with an encoder to show a keyboard");

    lv_obj_t *ta2 = lv_textarea_create(parent);
    lv_obj_set_width(ta2, LV_PCT(100));
    lv_textarea_set_one_line(ta2, true);
    lv_textarea_set_placeholder_text(ta2, "Type something");

    lv_obj_t *kb = lv_keyboard_create(lv_screen_active());
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ta1, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(ta2, ta_event_cb, LV_EVENT_ALL, kb);
}

/* =========================================================================
 * ============================== NEW: images ==============================
 * ========================================================================= */
static void gif_pause_cb(lv_timer_t *timer)
{
    lv_obj_t *gif = lv_timer_get_user_data(timer);
    lv_gif_pause(gif);
}

static void tab_changed_cb(lv_event_t *e)
{
    lv_obj_t *tv_obj = lv_event_get_target(e);
    if (lv_tabview_get_tab_active(tv_obj) == 2) {
        /* 进入 Images: 首次播 5s 后暂停, 之后切回直接显示暂停状态 */
        images_create(t3, !first_play_done);
        first_play_done = true;
    } else {
        /* 离开 Images: 清空 t3 释放 GIF/PNG 资源 */
        lv_obj_clean(t3);
    }
}

static void images_create(lv_obj_t *parent, bool start_timer)
{
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *img = lv_image_create(parent);
    lv_image_set_src(img, "mnt/sdfile/EXT_RESERVED/uipackres/ui/1111.png");

    lv_obj_t *gif1 = lv_gif_create(parent);
    lv_gif_set_src(gif1, "mnt/sdfile/EXT_RESERVED/uipackres/ui/dance.gif");
    if (start_timer) {
        lv_timer_set_repeat_count(lv_timer_create(gif_pause_cb, 5000, gif1), 1);
    } else {
        lv_gif_pause(gif1);
    }

    lv_obj_t *gif2 = lv_gif_create(parent);
    lv_gif_set_src(gif2, "mnt/sdfile/EXT_RESERVED/uipackres/ui/lol.gif");
    if (start_timer) {
        lv_timer_set_repeat_count(lv_timer_create(gif_pause_cb, 5000, gif2), 1);
    } else {
        lv_gif_pause(gif2);
    }
}
/* =========================================================================
 * ============================ END NEW: images ============================
 * ========================================================================= */

static void msgbox_create(void)
{
    lv_obj_t *mbox = lv_msgbox_create(NULL);
    lv_msgbox_add_title(mbox, "Hi");
    lv_msgbox_add_text(mbox, "Welcome to the keyboard and encoder demo");

    lv_obj_t *btn = lv_msgbox_add_footer_button(mbox, "Ok");
    lv_obj_add_event_cb(btn, msgbox_event_cb, LV_EVENT_CLICKED, mbox);
    lv_group_focus_obj(btn);
    lv_obj_add_state(btn, LV_STATE_FOCUS_KEY);
    lv_group_focus_freeze(g, true);

    lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *bg = lv_obj_get_parent(mbox);
    lv_obj_set_style_bg_opa(bg, LV_OPA_70, 0);
    lv_obj_set_style_bg_color(bg, lv_palette_main(LV_PALETTE_GREY), 0);
}

static void msgbox_event_cb(lv_event_t *e)
{
    lv_obj_t *msgbox = lv_event_get_user_data(e);

    lv_msgbox_close(msgbox);
    lv_group_focus_freeze(g, false);
    lv_group_focus_obj(lv_obj_get_child(t1, 0));
    lv_obj_scroll_to(t1, 0, 0, LV_ANIM_OFF);
}

static void ta_event_cb(lv_event_t *e)
{
    lv_indev_t *indev = lv_indev_active();
    if (indev == NULL) {
        return;
    }
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED && indev_type == LV_INDEV_TYPE_ENCODER) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_group_focus_obj(kb);
        lv_group_set_editing(lv_obj_get_group(kb), kb != NULL);
        lv_obj_set_height(tv, LV_VER_RES / 2);
        lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
    }

    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_height(tv, LV_VER_RES);
    }
}

#endif
