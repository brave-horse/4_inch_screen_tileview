#ifndef SCENE_PANEL_H
#define SCENE_PANEL_H

#include "lvgl.h"

/* 灯屏通用"情景面板"(cont_2): imgbtn_1 toggle 从屏外滑出到 (92,227) / 收回(更快);
 * 模态捕获层(开时盖在滑块/空白之上、总开关&imgbtn&面板之下, 点它们只收回);
 * 面板内图片按下减半(PRESSED)+点击收回; 总开关 开→关 时先收回再上遮罩。
 * 色温/灯带/彩色/磁吸 4 个灯屏共用, 改效果只改本模块。 */
typedef struct {
    lv_obj_t *cont;          /* 滑出面板 cont_2 */
    lv_obj_t *trigger;       /* imgbtn_1 触发键 */
    lv_obj_t *power;         /* on_off_2_img 总电源 */
    lv_obj_t *overlay;       /* 内部创建的模态捕获层 */
    void (*refresh)(bool);   /* 各屏自己的 *_refresh(bool), 收回后上遮罩用 */
    bool open;
    bool refresh_off_after_close;
} ScenePanel;

/* 进屏时调用(放 *_on_screen_load 末尾): 复位到收起 + 绑定 imgbtn/图片/捕获层 */
void scene_panel_setup(ScenePanel *panel, lv_obj_t *screen, lv_obj_t *cont,
                       lv_obj_t *trigger, lv_obj_t *power, void (*refresh)(bool));

/* 总开关 toggle 后调用(代替直接 refresh): on→关且面板开→先收回再上遮罩, 否则直接 refresh */
void scene_panel_on_power(ScenePanel *panel, bool on);

#endif /* SCENE_PANEL_H */
