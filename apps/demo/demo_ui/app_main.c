#ifdef LV_USE_GUIBUILDER_SIMULATOR
#include "lvgl.h"
#include "demos/lv_demos.h"
#else
#include "app_config.h"
#include "system/includes.h"
#include "os/os_api.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "TheOnlyTask.h"        /* 色温灯任务 */
#include "HWDataAccess.h"
#include "play_animation.h"     /* 开机动画 */
#include <stdio.h>   /* FILE / fopen / fclose */

lv_ui guider_ui;

/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,    6,  0 }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,    6,  1 }, //此中断强制注册到cpu1
    { -2,              -2, -2 }, //如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif
    { -1,              -1, -1 },
};

/*任务列表 */
//｛任务名，优先级，堆栈大小，消息队列大小，静态堆栈池，绑定核心｝
const struct task_info task_info_table[] = {
    {"app_core",            15,     2048,	  1024 },
    {"sys_event",           29,     512,	   0 },
    {"systimer",            14,     256, 	   0 },
    {"sys_timer",            9,     512,	  128 },
    {"The_onlytask",        20,     512,	   0 },   //仅有的唯一一个任务: 由 Task/Soc/TheOnlyTask.c 的 task_create 启动

    {0, 0, 0, 0, 0},
};
#endif /* LV_USE_GUIBUILDER_SIMULATOR */


#ifndef LV_USE_GUIBUILDER_SIMULATOR
/* 强符号覆盖 lvgl_main.c 里的 _WEAK_ jl_gui_init，
   由 lvgl_v8_main_task 在 lv_init() 之后回调 */
void jl_gui_init(void)
{
    puts("[demo_ui_boot] jl_gui_init enter\n");
    setup_ui(&guider_ui);
    puts("[demo_ui_boot] setup_ui done\n");
    events_init(&guider_ui);
    puts("[demo_ui_boot] events_init done\n");
    custom_init(&guider_ui);
    puts("[demo_ui_boot] custom_init done\n");

    /* 开机动画暂禁用: jpeg硬解与LVGL的GPU渲染共享硬件,LVGL运行时无法同时硬解,
       会卡死空转+canvas常驻拖慢滑动fps(25→15)。待改"LVGL启动前播+手动LCD推流"方案。 */
    /* play_animation_start(); */
}

extern int lvgl_main_task_init(void);

void app_main(void)
{
    printf("\n\n\n ------------demo ui run %s-------------\n\n\n", __TIME__);

    /* 1. 确保文件系统已挂载完毕 (因为此时刚开机，可能文件系统还在初始化，需要暂短轮询探测) */
    int retry = 0;
    FILE *fd = NULL;
    do {
        fd = fopen("mnt/sdfile/EXT_RESERVED/uipackres/ui/1111.avi", "r");
        if (fd) {
            fclose(fd);
            printf("[demo_ui_boot] resource probe ok, retry=%d\n", retry);
            break;
        }
        os_time_dly(10);
    } while (++retry < 30);
    if (!fd) {
        puts("[demo_ui_boot] resource probe fail: mnt/sdfile/EXT_RESERVED/uipackres/ui/1111.avi\n");
    }

    /* 2. 开机动画: 在LVGL之前同步播放(自解码+fb_draw直显) */
  /*   play_animation_start(); */

    /* 3. 初始化硬件中间层(必须在 task / lvgl 之前) */
    HW_Init();

    /* 3. 创建色温灯任务(中间层 HWInterface.LightCT 的下发任务) */
    TheOnlyTaskCreate();
    puts("[demo_ui_boot] TheOnlyTaskCreate done\n");

    /* 4. 启动 LVGL 界面框架 */
    int ret = lvgl_main_task_init();
    printf("[demo_ui_boot] lvgl_main_task_init ret=%d\n", ret);
}
#endif /* LV_USE_GUIBUILDER_SIMULATOR */
