#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_ft_info_t lv_font_FangZhengKaiTiJianTi_1_12_font_info;
lv_font_t lv_font_FangZhengKaiTiJianTi_1_12;
void lv_font_FangZhengKaiTiJianTi_1_12_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_12_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_12_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_12_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_12, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.name =
        "D:\\wl83_soundbox\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\font\\FangZhengKaiTiJianTi_1.ttf";
#else
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.name = "storage/sd0/C/30100000.ttf";
#endif
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.weight = 12;
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.style = FT_FONT_STYLE_NORMAL;
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.mem = NULL;
    lv_font_FangZhengKaiTiJianTi_1_12_font_info.font = NULL;
    if (!lv_ft_font_init(&lv_font_FangZhengKaiTiJianTi_1_12_font_info)) {
        LV_LOG_ERROR("Create Font Failed %s\n", lv_font_FangZhengKaiTiJianTi_1_12_font_info.name);
        memset(&lv_font_FangZhengKaiTiJianTi_1_12_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_12, 0, sizeof(lv_font_t));
        lv_font_FangZhengKaiTiJianTi_1_12 = *LV_FONT_DEFAULT;
    } else {
        lv_font_FangZhengKaiTiJianTi_1_12 = *(lv_font_FangZhengKaiTiJianTi_1_12_font_info.font);
    }
}
lv_ft_info_t lv_font_FangZhengKaiTiJianTi_1_24_font_info;
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_24_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_24_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_24_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.name =
        "D:\\wl83_soundbox\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\font\\FangZhengKaiTiJianTi_1.ttf";
#else
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.name = "storage/sd0/C/30100000.ttf";
#endif
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.weight = 24;
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.style = FT_FONT_STYLE_NORMAL;
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.mem = NULL;
    lv_font_FangZhengKaiTiJianTi_1_24_font_info.font = NULL;
    if (!lv_ft_font_init(&lv_font_FangZhengKaiTiJianTi_1_24_font_info)) {
        LV_LOG_ERROR("Create Font Failed %s\n", lv_font_FangZhengKaiTiJianTi_1_24_font_info.name);
        memset(&lv_font_FangZhengKaiTiJianTi_1_24_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
        lv_font_FangZhengKaiTiJianTi_1_24 = *LV_FONT_DEFAULT;
    } else {
        lv_font_FangZhengKaiTiJianTi_1_24 = *(lv_font_FangZhengKaiTiJianTi_1_24_font_info.font);
    }
}
lv_ft_info_t lv_font_FangZhengKaiTiJianTi_1_32_font_info;
lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
void lv_font_FangZhengKaiTiJianTi_1_32_file()
{
    if (lv_font_FangZhengKaiTiJianTi_1_32_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_32_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_32_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_32, 0, sizeof(lv_font_t));
    }
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.name =
        "D:\\wl83_soundbox\\ac792\\ui_prj\\wifi_soundbox_800x480\\import\\font\\FangZhengKaiTiJianTi_1.ttf";
#else
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.name = "storage/sd0/C/30100000.ttf";
#endif
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.weight = 32;
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.style = FT_FONT_STYLE_NORMAL;
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.mem = NULL;
    lv_font_FangZhengKaiTiJianTi_1_32_font_info.font = NULL;
    if (!lv_ft_font_init(&lv_font_FangZhengKaiTiJianTi_1_32_font_info)) {
        LV_LOG_ERROR("Create Font Failed %s\n", lv_font_FangZhengKaiTiJianTi_1_32_font_info.name);
        memset(&lv_font_FangZhengKaiTiJianTi_1_32_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_32, 0, sizeof(lv_font_t));
        lv_font_FangZhengKaiTiJianTi_1_32 = *LV_FONT_DEFAULT;
    } else {
        lv_font_FangZhengKaiTiJianTi_1_32 = *(lv_font_FangZhengKaiTiJianTi_1_32_font_info.font);
    }
}

void init_gui_fonts()
{
    lv_font_FangZhengKaiTiJianTi_1_12_file();
    lv_font_FangZhengKaiTiJianTi_1_24_file();
    lv_font_FangZhengKaiTiJianTi_1_32_file();


}

void free_gui_fonts()
{
    if (lv_font_FangZhengKaiTiJianTi_1_12_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_12_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_12_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_12, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_24_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_24_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_24_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_24, 0, sizeof(lv_font_t));
    }
    if (lv_font_FangZhengKaiTiJianTi_1_32_font_info.font != NULL) {
        lv_ft_font_destroy(lv_font_FangZhengKaiTiJianTi_1_32_font_info.font);
        memset(&lv_font_FangZhengKaiTiJianTi_1_32_font_info, 0, sizeof(lv_ft_info_t));
        memset(&lv_font_FangZhengKaiTiJianTi_1_32, 0, sizeof(lv_font_t));
    }
}

