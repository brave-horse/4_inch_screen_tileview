#include "lvgl.h"
#include "gui_guider.h"
#include "WIFI_detail.h"

void wifi_detail_on_screen_load(void)
{
    lv_obj_set_scroll_dir(guider_ui.WIFI_detail_tabview_1, LV_DIR_VER);
    lv_obj_set_scroll_dir(guider_ui.WIFI_detail_tabview_1_tab_1, LV_DIR_VER);
}
