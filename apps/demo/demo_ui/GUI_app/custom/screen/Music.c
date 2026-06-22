#include "lvgl.h"
#include "gui_guider.h"
#include "HWDataAccess.h"
#include "Music.h"

#define MUSIC_TIMER_MS  30        //MS milliseconds
#define MUSIC_RPS       0.5f      //RPS rotations per second

static bool          s_playing;       /* play/pause state */
static lv_timer_t    *s_disc_timer;   /* disc rotation timer */
static int16_t       s_disc_angle;    /* current angle in 0.1° */
static int16_t       s_disc_step;     /* angle step per tick in 0.1° */

static void disc_rotate_cb(lv_timer_t *timer);

static void apply_play_state(void)
{
    if (s_playing) {
        s_disc_step = (int16_t)(MUSIC_RPS * 3600.0f * MUSIC_TIMER_MS / 1000.0f);
        if (!s_disc_timer) s_disc_timer = lv_timer_create(disc_rotate_cb, MUSIC_TIMER_MS, NULL);
    } else {
        if (s_disc_timer) { lv_timer_del(s_disc_timer); s_disc_timer = NULL; }
    }
}

static void disc_rotate_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_obj_t *disc = guider_ui.Music_disc;
    if (!lv_obj_is_valid(disc)) return;
    s_disc_angle += s_disc_step;
    if (s_disc_angle >= 3600) s_disc_angle -= 3600;
    lv_img_set_angle(disc, s_disc_angle);
}

static void music_on_screen_delete(lv_event_t *event)
{
    LV_UNUSED(event);
    if (s_disc_timer) { lv_timer_del(s_disc_timer); s_disc_timer = NULL; }
}

/* ══════ 事件接口(GUI-Guider 一行调用) ══════ */

void music_on_screen_load(void)
{
    lv_obj_clear_flag(guider_ui.Music, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(guider_ui.Music, music_on_screen_delete, LV_EVENT_DELETE, NULL);

    /* 从共享状态恢复到控件 */
    s_playing = HWInterface.Music.playing;
    if (s_playing) lv_obj_add_state(guider_ui.Music_play, LV_STATE_CHECKED);
    else           lv_obj_clear_state(guider_ui.Music_play, LV_STATE_CHECKED);
    apply_play_state();

    /* 按下反馈 */
    lv_obj_set_style_img_opa(guider_ui.Music_play, 100, LV_PART_MAIN | LV_STATE_PRESSED);
}

void music_on_play_toggle(lv_event_t *event)
{
    s_playing = lv_obj_has_state(lv_event_get_target(event), LV_STATE_CHECKED);
    HWInterface.Music.playing = s_playing;   /* 同步给管理屏 */
    apply_play_state();
}
