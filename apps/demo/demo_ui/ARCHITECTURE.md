# demo_ui 工程架构

> 路径约定：所有 SDK 侧相对路径以 `apps/demo/demo_ui/` 为基准。  
> GUI-Guider 侧（custom/generated）通过符号链接挂载：  
> `GUI_app/custom` → `D:/7.NXP-GUI-PROJECT/4_inch_screen_tileview/custom`  
> `GUI_app/generated` → `D:/7.NXP-GUI-PROJECT/4_inch_screen_tileview/generated`

---

## 一、总览：三大物理分区

```
┌──────────────────────────────────────────────────────────────────┐
│  SDK 固件侧 (E: 盘)                                              │
│  apps/demo/demo_ui/                                              │
│  ├── 应用入口 + 板级配置 + HAL + 任务                            │
│  └── GUI_app/ ───[符号链接]───>>  D: 盘 GUI-Guider 工程          │
├──────────────────────────────────────────────────────────────────┤
│  GUI-Guider 工程侧 (D: 盘)                                       │
│  ├── custom/    手写 UI 逻辑（屏逻辑/组件/守护）                  │
│  └── generated/ GUI-Guider 自动生成（setup_scr_/events/fonts/img）│
├──────────────────────────────────────────────────────────────────┤
│  资源打包 (E: 盘)                                                │
│  cpu/wl83/tools/demo_ui_res/  →  packres  →  UIPACKRES (4MB)    │
│  运行时挂载路径: s:/sdfile/EXT_RESERVED/uipackres/ui/            │
└──────────────────────────────────────────────────────────────────┘
```

---

## 二、完整目录树

```
apps/demo/demo_ui/
│
├── app_main.c                          ◄── 应用入口：初始化→创建任务→启动LVGL
├── lv_dclock.c / lv_dclock.h           ◄── LVGL 数字时钟控件
├── play_animation.c                    ◄── 开机动画（MJPEG自解码 + YUV→RGB）
├── avi_parse.c / local_avi.c           ◄── AVI 容器解析 + 本地文件读取
├── pipeline_jpeg_dec.c                 ◄── JPEG 硬解流水线
├── media_stubs.c                       ◄── 媒体子系统空桩
├── LVGL_PORTING_NOTES.md               ◄── LVGL 移植笔记
│
├── include/
│   ├── app_config.h                    ◄── 总开关：UI资源分区/LVGL版本/性能日志/路径
│   ├── avi_parse.h
│   ├── local_avi.h
│   ├── play_animation.h
│   └── storage_device.h
│
├── board/wl83/                         ◄── 板级构建配置
│   ├── Makefile                        ◄── ★ 构建核心：源文件收集/编译/链接/后处理
│   ├── board_config.h                  ◄── 板级宏选择（AC7926A）
│   ├── board_develop.c                 ◄── 板级初始化（GPIO/外设）
│   ├── board_develop_AC7926A.h         ◄── 外设宏：LCD=JD9261T 720x720 MIPI
│   ├── chip_cfg.h                      ◄── 芯片宏：Flash 8MB / SDRAM 16MB
│   └── sdk_config.h                    ◄── SDK 调试开关
│
├── class/                              ◄── ★ 硬件中间层（C 手写 OOP）
│   ├── Inc/
│   │   ├── object.h                    ◄── 基类：成员变量宏 + 虚函数表
│   │   ├── Switch.h                    ◄── 开关（bool 状态）
│   │   ├── Percent.h                   ◄── 百分比（0-100%）
│   │   ├── Light.h                     ◄── 灯光基类（Switch + Percent 组合）
│   │   ├── LightCT.h                   ◄── 色温灯（Light + 色温）
│   │   ├── LightRGB.h                  ◄── RGB 灯（Light + R/G/B 通道）
│   │   ├── Curtain.h                   ◄── 窗帘基类（start/current/target 运动模型）
│   │   ├── CurtainMotor.h              ◄── 窗帘电机（多帘管理）
│   │   └── AirCondition.h              ◄── 空调（模式/风速）
│   └── Soc/
│       ├── object.c
│       ├── Switch.c
│       ├── Percent.c
│       ├── Light.c
│       ├── LightCT.c
│       ├── LightRGB.c
│       ├── Curtain.c
│       ├── CurtainMotor.c
│       └── AirCondition.c              ◄── 注：此文件被 Makefile 排除（与 custom 影子头冲突）
│
├── Task/                               ◄── RTOS 任务层
│   ├── Inc/
│   │   ├── TheOnlyTask.h               ◄── 色温灯轮询任务
│   │   └── hw_cloud_task.h             ◄── 云端/硬件消息队列任务
│   └── Soc/
│       ├── TheOnlyTask.c               ◄── 轮询 HWInterface.changed → Apply
│       └── hw_cloud_task.c             ◄── HW_Msg 队列消费者
│
├── bsp/LightCT/                        ◄── 板级支持（色温灯驱动）
│   ├── lightct.c
│   └── lightct.h
│
├── Fuc/                                ◄── 功能模块（预留，当前空）
│   ├── Inc/.gitkeep
│   └── Soc/.gitkeep
│
└── GUI_app/                            ◄── GUI-Guider 符号链接网关
    ├── custom  →  D:/.../custom/       ◄── 手写 UI 逻辑（见第三节）
    └── generated → D:/.../generated/   ◄── 自动生成 UI 代码（见第四节）
```

---

## 三、custom/ — 手写 UI 逻辑层

```
GUI_app/custom/  (物理位置: D:/7.NXP-GUI-PROJECT/4_inch_screen_tileview/custom/)
│
├── custom.c                           ◄── ★ custom_init()：守护/禁滚/下拉面板/性能日志
├── custom.mk                          ◄── 构建辅助（CUSTOM_SRC_DIRS / CUSTOM_INC_DIRS）
├── HWDataAccess.c                     ◄── ★ 硬件数据出入口：LightCT/LEDStrip/CurtainMotor 实例
│
├── include/                           ◄── 头文件
│   ├── custom.h                       ◄── custom_init() 声明
│   ├── custom_modules.h               ◄── 所有屏头文件总汇（include-all）
│   ├── HWDataAccess.h                 ◄── HWInterface 全局结构体 + HW_Msg 消息枚举
│   ├── lv_conf_ext.h                  ◄── LVGL 扩展配置
│   ├── my_app.h                       ◄── 应用级宏/常量
│   ├── scr_guard.h                    ◄── 屏幕指针守卫（防野指针）
│   ├── scr_noscroll.h                 ◄── 递归关弹性滚动（防 tileview 深层卡死）
│   ├── pulldown.h                     ◄── 下拉面板
│   ├── LVGL_Memory.h                  ◄── LVGL 内存管理
│   ├── device_management.h            ◄── 设备管理总览屏
│   │
│   │  以下每个 .h 对应一个子界面屏：
│   ├── Home.h                         ├── light_CT_screen.h
│   ├── LEDStrip.h                     ├── MagLight.h
│   ├── RGBLight.h                     ├── FabricCurtian.h
│   ├── Sheers.h                       ├── RollBlind.h
│   ├── Dream.h                        ├── AirCondition.h
│   ├── Music.h                        ├── DryRack.h
│   ├── FanAndLight.h                  ├── Heater.h
│   ├── NetSetting.h                   ├── PlaySet.h
│   └── Setting.h
│
├── screen/                            ◄── ★ 各子界面屏逻辑实现（核心）
│   ├── Home.c                         ◄── 主页 tileview（7 tile + 下拉面板）
│   ├── light_CT_screen.c              ◄── 色温灯控制（亮度条+色温条+白光/橙光叠图）
│   ├── LEDStrip.c                     ◄── LED 灯带（亮度+混色）
│   ├── RGBLight.c                     ◄── RGB 彩灯（红绿蓝三色条+#RRGGBB显示）
│   ├── MagLight.c                     ◄── 磁吸灯（亮度下限不归0+开关不碰透明度）
│   ├── FabricCurtian.c                ◄── 布艺窗帘（拖动开合+对称平移）
│   ├── Sheers.c                       ◄── 纱帘（同窗帘模型）
│   ├── RollBlind.c                    ◄── 卷帘（同窗帘模型，待重构）
│   ├── Dream.c                        ◄── 梦幻帘（无遮罩+旋转角 HW_MSG_CURTAIN_ANGLE）
│   ├── AirCondition.c                 ◄── 空调（模式/风速两组叠图循环切换+自动档 timer）
│   ├── Music.c                        ◄── 音乐播放器（未完成）
│   ├── DryRack.c                      ◄── 晾衣机（拖动升降-110~160+Open/Pause/Close动画）
│   ├── FanAndLight.c                  ◄── 风扇灯（未完成）
│   ├── Heater.c                       ◄── 暖气（未完成）
│   ├── NetSetting.c                   ◄── 网络设置
│   ├── PlaySet.c                      ◄── 显示设置（手风琴折叠菜单设计已定稿）
│   └── Setting.c                      ◄── 设置主页
│
├── widget/                            ◄── 自定义控件
│   └── pulldown.c                     ◄── ★ 下拉面板（btn 绑定必须在此捕获真身指针）
│
└── rule/                              ◄── 通用规则/守护
    ├── scr_guard.c                    ◄── ★ 屏幕指针守卫：切屏时把旧屏指针标脏，防 timer 野指针
    ├── scr_noscroll.c                 ◄── ★ 递归关弹性：遍历所有子控件 kill scroolbar/snap/elastic
    └── LVGL_Memory.c                  ◄── LVGL 内存池配置
```

---

## 四、generated/ — GUI-Guider 自动生成层

```
GUI_app/generated/  (物理位置: D:/7.NXP-GUI-PROJECT/4_inch_screen_tileview/generated/)
│
├── gui_guider.c                       ◄── ★ UI 框架：setup_ui() 创建所有屏幕 + ui_load_scr_animation()
├── gui_guider.h                       ◄── lv_ui 结构体（所有屏指针 + 控件指针）
│
├── events_init.c                      ◄── ★ 事件绑定：GUI-Guider 面板配置的事件回调（会被自动覆盖！）
├── events_init.h
│
├── widgets_init.c / widgets_init.h    ◄── 控件初始化
│
├── setup_scr_ui_home_screen.c         ◄── 主页 tileview 布局（7 tile + btn/panel）
├── setup_scr_light_CT_screen.c        ◄── 色温灯屏 UI 布局
├── setup_scr_device_management_screen.c ◄── 设备管理总览屏
├── setup_scr_setting_screen.c         ◄── 设置主页
│
│  以下每个 setup_scr_*.c 生成一个子界面 UI 布局：
├── setup_scr_LedStrip.c               ├── setup_scr_MagLight.c
├── setup_scr_RGBLight.c               ├── setup_scr_FabricCurtian.c
├── setup_scr_Sheers.c                 ├── setup_scr_RollBlind.c
├── setup_scr_Dream.c                  ├── setup_scr_AirCondition.c
├── setup_scr_Music.c                  ├── setup_scr_DryRack.c
├── setup_scr_FanAndLight.c            ├── setup_scr_Heater.c
├── setup_scr_NetSett.c                ├── setup_scr_PlaySet.c
├── setup_scr_Helper.c                 ├── setup_scr_Reset.c
├── setup_scr_SensorSet.c              ├── setup_scr_SwitchSet.c
├── setup_scr_Light_Scene.c            ├── setup_scr_Curtain_Scene.c
└── setup_scr_huifuchuchangshezhi.c
│
├── images/                            ◄── 153 个 .c 图片数组 + images.mk + images_list.mk
│   └── mergeBinFile.bin               ◄── 合并的二进制图像数据
│
├── guider_fonts/                      ◄── GUI-Guider 内置字体（MiSans + montserrat）
│   ├── lv_font_MiSansNormal_*.c       (12/30 号)
│   ├── lv_font_ZiTiQuanWeiJunHeiW22_*.c (12/16/20/24/30 号)
│   └── lv_font_montserratMedium_*.c   (12/16/30 号)
│
├── guider_customer_fonts/             ◄── 自定义字体
│   └── lv_customer_font_ZiTiQuanWeiJunHeiW22_30.c
│
├── generated.mk                       ◄── 构建辅助
└── MicroPython/                       ◄── MicroPython 用 .bin 资源副本（146个） + .fnt
```

---

## 五、构建流程

```
make ac792n_demo_demo_ui
│
├─ 1. PRE-BUILD（Makefile → 生成中间文件）
│   ├── sdk_used_list.c  ──→  sdk_used_list.used
│   ├── sdk_ld.c         ──→  sdk.ld（链接脚本，含 UI 专用段）
│   ├── download.c       ──→  download.bat（设置 UI_RES_PREFIX=demo_）
│   └── isd_config_rule.c ──→ isd_config.ini（Flash 分区表，UIPACKRES 4MB@尾部）
│
├─ 2. COMPILE（pi32v2 clang 工具链，-mcpu=r3）
│   ├── apps/demo/demo_ui/*.c
│   ├── GUI_app/generated/*.c + images/*.c + guider_fonts/*.c  （通过 symlink）
│   ├── GUI_app/custom/*.c + rule/*.c + screen/*.c + widget/*.c （通过 symlink）
│   ├── class/Soc/*.c（排除 AirCondition.c ─ 和 custom 影子头冲突）
│   ├── Task/Soc/*.c
│   ├── bsp/LightCT/*.c
│   └── LVGL v8 库 + freetype + rlottie + LCD 驱动 + ...
│
├─ 3. LINK
│   └── → cpu/wl83/tools/sdk.elf（含 .ui_module_event_handler 等专用段）
│
└─ 4. POST-BUILD（download.bat 自动执行）
    ├── objcopy 提取段 → app.bin
    ├── packres -n ui  demo_ui_res/   → UIPACKRES（4MB 资源包）
    ├── packres -n logo poweronoff_res/ → LOGOPACKRES（开机 Logo）
    └── isd_download.exe 合成最终固件（jl_isd.fw + jl_isd.bin）
        └── UIPACKRES 烧录到 Flash 0x7FEFFF 处（8MB-4MB-4KB）
```

**关键构建文件：**
- [Makefile](apps/demo/demo_ui/board/wl83/Makefile) — 1051 行，完整的编译/链接/后处理规则
- [app_config.h](apps/demo/demo_ui/include/app_config.h) — `CONFIG_UI_PACKRES_LEN=0x400000`（4MB）
- [board_develop_AC7926A.h](apps/demo/demo_ui/board/wl83/board_develop_AC7926A.h) — LCD=JD9261T 720×720 MIPI
- [chip_cfg.h](apps/demo/demo_ui/board/wl83/chip_cfg.h) — Flash 8MB / SDRAM 16MB

---

## 六、运行时启动流程

```
上电 → bootloader → app_main()
                        │
                        ├─ 1. 轮询等待文件系统挂载（mnt/sdfile/.../1111.avi）
                        │
                        ├─ 2. play_animation_start()（开机动画，当前禁用）
                        │
                        ├─ 3. HW_Init()          ◄── class/Soc/*.c 各模块 Init
                        │
                        ├─ 4. TheOnlyTaskCreate() ◄── Task/Soc/TheOnlyTask.c，轮询 HWInterface.changed
                        │
                        └─ 5. lvgl_main_task_init()
                              │
                              └─ lv_init() → jl_gui_init()
                                               │
                                               ├─ setup_ui(&guider_ui)
                                               │   └── 创建所有 screen（generated/gui_guider.c）
                                               │       每个 setup_scr_* 创建各自的控件树
                                               │
                                               ├─ events_init(&guider_ui)
                                               │   └── 绑定 GUI-Guider 面板配置的事件回调
                                               │       （★ 注意：会覆盖 custom 同属性修改！）
                                               │
                                               └─ custom_init(&guider_ui)
                                                   ├── os_task_suspend("video_engine_server")
                                                   ├── scr_guard_init()     ◄── 屏指针野指针守护
                                                   ├── scr_noscroll_init()  ◄── 递归关弹性滚动
                                                   ├── pulldown_init()     ◄── 下拉面板绑定
                                                   └── lv_timer_create(perf_mon_cb) ◄── 性能日志
```

**运行时数据流：**
```
触摸/按键 → LVGL indev → 事件回调 → screen/*.c 逻辑
                                      │
                                      ├── 更新 LVGL 控件（进度条/透明度/动画）
                                      └── HWDataAccess API → HWInterface.xxx = 新值
                                                              │
                                                              └── TheOnlyTask 轮询 changed
                                                                    → HWInterface.Apply()
                                                                    → class/Soc/*.c → 硬件
```

---

## 七、各层职责与文件映射

| 层 | 职责 | 关键文件 |
|---|---|---|
| **应用入口** | 初始化顺序、任务创建、LVGL 启动 | [app_main.c](apps/demo/demo_ui/app_main.c) |
| **板级配置** | 芯片宏、外设宏、Flash 分区、Makefile | [board/](apps/demo/demo_ui/board/wl83/) |
| **GUI 生成层** | 控件树创建、事件绑定框架、图片/字体资源 | [generated/](apps/demo/demo_ui/GUI_app/generated/) |
| **GUI 手写层** | 屏交互逻辑、自定义控件、守护规则 | [custom/](apps/demo/demo_ui/GUI_app/custom/) |
| **硬件中间层** | C 手写 OOP：Switch→Percent→Light→LightCT/LightRGB、Curtain 运动模型 | [class/](apps/demo/demo_ui/class/) |
| **硬件数据面** | HWInterface 全局实例、消息枚举、Apply 下发 | [HWDataAccess.c](apps/demo/demo_ui/GUI_app/custom/HWDataAccess.c) |
| **任务层** | RTOS 任务：TheOnlyTask 轮询、hw_cloud_task 消息消费 | [Task/](apps/demo/demo_ui/Task/) |
| **板级支持** | 色温灯 bsp 驱动 | [bsp/LightCT/](apps/demo/demo_ui/bsp/LightCT/) |
| **开机动画** | MJPEG AVI 解析 + JPEG 硬解 + YUV→RGB + Canvas 推屏 | [play_animation.c](apps/demo/demo_ui/play_animation.c) |
| **SD 资源** | PNG 图片 → lvgl cache 常驻（替代 img.c C 数组） | `s:/sdfile/EXT_RESERVED/uipackres/ui/*.png` |

---

## 八、class 继承关系（硬件中间层）

```
object (基类)
  └── Switch         ◄── 开关（bool on/off）
  └── Percent        ◄── 百分比（0-1000，对应 0.0%-100.0%）
  └── Light          ◄── 灯光基类：Switch + Percent 组合
        ├── LightCT  ◄── 色温灯：Light + color_temp + 白光/橙光混色公式
        └── LightRGB ◄── RGB 灯：Light + R/G/B 三通道 + #RRGGBB 合成
  └── Curtain        ◄── 窗帘基类：start/current/target 运动模型 + lv_anim 驱动
        └── CurtainMotor ◄── 多帘管理（CURTAIN_COUNT_MAX 路）
  └── AirCondition   ◄── 空调：模式+风速两组叠图循环
```

---

## 九、子界面屏 → 文件映射速查表

| 屏幕 | GUI-Guider 布局（generated） | 手写逻辑（custom） |
|---|---|---|
| 主页 Home | [setup_scr_ui_home_screen.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_ui_home_screen.c) | [Home.c](apps/demo/demo_ui/GUI_app/custom/screen/Home.c) |
| 色温灯 LightCT | [setup_scr_light_CT_screen.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_light_CT_screen.c) | [light_CT_screen.c](apps/demo/demo_ui/GUI_app/custom/screen/light_CT_screen.c) |
| LED 灯带 | [setup_scr_LedStrip.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_LedStrip.c) | [LEDStrip.c](apps/demo/demo_ui/GUI_app/custom/screen/LEDStrip.c) |
| RGB 彩灯 | [setup_scr_RGBLight.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_RGBLight.c) | [RGBLight.c](apps/demo/demo_ui/GUI_app/custom/screen/RGBLight.c) |
| 磁吸灯 | [setup_scr_MagLight.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_MagLight.c) | [MagLight.c](apps/demo/demo_ui/GUI_app/custom/screen/MagLight.c) |
| 布艺窗帘 | [setup_scr_FabricCurtian.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_FabricCurtian.c) | [FabricCurtian.c](apps/demo/demo_ui/GUI_app/custom/screen/FabricCurtian.c) |
| 纱帘 | [setup_scr_Sheers.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_Sheers.c) | [Sheers.c](apps/demo/demo_ui/GUI_app/custom/screen/Sheers.c) |
| 卷帘 | [setup_scr_RollBlind.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_RollBlind.c) | [RollBlind.c](apps/demo/demo_ui/GUI_app/custom/screen/RollBlind.c) |
| 梦幻帘 | [setup_scr_Dream.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_Dream.c) | [Dream.c](apps/demo/demo_ui/GUI_app/custom/screen/Dream.c) |
| 空调 | [setup_scr_AirCondition.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_AirCondition.c) | [AirCondition.c](apps/demo/demo_ui/GUI_app/custom/screen/AirCondition.c) |
| 音乐 | [setup_scr_Music.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_Music.c) | [Music.c](apps/demo/demo_ui/GUI_app/custom/screen/Music.c) |
| 晾衣机 | [setup_scr_DryRack.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_DryRack.c) | [DryRack.c](apps/demo/demo_ui/GUI_app/custom/screen/DryRack.c) |
| 风扇灯 | [setup_scr_FanAndLight.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_FanAndLight.c) | [FanAndLight.c](apps/demo/demo_ui/GUI_app/custom/screen/FanAndLight.c) |
| 暖气 | [setup_scr_Heater.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_Heater.c) | [Heater.c](apps/demo/demo_ui/GUI_app/custom/screen/Heater.c) |
| 网络设置 | [setup_scr_NetSett.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_NetSett.c) | [NetSetting.c](apps/demo/demo_ui/GUI_app/custom/screen/NetSetting.c) |
| 显示设置 | [setup_scr_PlaySet.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_PlaySet.c) | [PlaySet.c](apps/demo/demo_ui/GUI_app/custom/screen/PlaySet.c) |
| 设置主页 | [setup_scr_setting_screen.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_setting_screen.c) | [Setting.c](apps/demo/demo_ui/GUI_app/custom/screen/Setting.c) |
| 设备管理 | [setup_scr_device_management_screen.c](apps/demo/demo_ui/GUI_app/generated/setup_scr_device_management_screen.c) | [device_management.h](apps/demo/demo_ui/GUI_app/custom/include/device_management.h) |

---

## 十、关键设计原则

1. **GUI-Guider 生成代码 ≠ 手写代码**：generated/ 每次导出覆盖，custom/ 永不被覆盖。事件回调名在 GUI-Guider 面板填写，实现在 custom/screen/*.c。
2. **events_init 会偷覆盖 custom 属性**：GUI-Guider 自动生成的事件回调里可能写同一属性（如 white opa），custom 改用正交属性（如 HIDDEN flag）规避。见 [gui-guider-event-overwrites-custom 记忆](memory://gui-guider-event-overwrites-custom)。
3. **屏指针守护**：切屏后 timer/poll 里的 `guider_ui.screen_X` 变野指针。必须用 `lv_obj_get_screen(控件)` 取当前屏。见 [scr_guard](apps/demo/demo_ui/GUI_app/custom/rule/scr_guard.c)。
4. **下拉面板 btn 绑定必须在 pulldown.c**：Home.c 用 `guider_ui.btn_x` 会因主屏重建变幽灵指针→野指针崩。见 [pulldown-buttons-in-pulldown-c 记忆](memory://pulldown-buttons-in-pulldown-c)。
5. **图片存储混合策略**：壁纸→C 数组进固件；场景图→SD PNG 通过 lvgl cache 常驻。见 [wallpaper-flash-status 记忆](memory://wallpaper-flash-status)。
6. **SDK 侧 class/ 与 custom 侧头文件同名冲突**：`class/Soc/AirCondition.c` 被 Makefile 排除，因为 `custom/include/AirCondition.h` 影子头抢占。见 [demo-ui-class-build-wiring 记忆](memory://demo-ui-class-build-wiring)。
