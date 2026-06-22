# demo_ui LVGL Porting Notes

这份笔记用于把 `apps/demo/demo_ui` 示例的启动链路、硬件配置和 LVGL 适配点先理清楚，方便后续移植或替换成自己的 UI。

## 1. 当前工程结构

`demo_ui` 本身只保留了很薄的一层应用入口，主要代码分布如下：

| 路径 | 作用 |
| --- | --- |
| `apps/demo/demo_ui/app_main.c` | 应用入口；注册系统任务表/中断表；启动 LVGL 主任务。 |
| `apps/demo/demo_ui/include/app_config.h` | demo 级配置；打开 `CONFIG_UI_ENABLE` 后启用 `USE_LVGL_V9_UI_DEMO`，并配置 LVGL framebuffer 数量。 |
| `apps/demo/demo_ui/board/wl83/board_config.h` | 板级配置入口；选择 AC7926A 开发板配置。 |
| `apps/demo/demo_ui/board/wl83/board_develop_AC7926A.h` | 具体板级宏：时钟、Flash、SD、IIC、SPI、LCD、TP、按键、电源等。 |
| `apps/demo/demo_ui/board/wl83/board_develop.c` | 把板级宏落成平台设备表；注册 `lcd`、`fb0/fb1/fb2`、`fb_out`、`iic`、`sd`、`uart` 等设备。 |
| `apps/demo/demo_ui/board/wl83/Makefile` | 工程编译入口；把 app、board、LCD、TP、LVGL v9、demo widgets 等源文件全部纳入构建。 |
| `apps/common/lvgl_v9/lvgl_main.c` | LVGL 任务运行框架：消息队列、触摸/按键事件转发、`lv_timer_handler()` 调度、挂起/恢复。 |
| `apps/common/lvgl_v9/lvgl_v9_main_task_init.c` | 当前 demo 的 LVGL 初始化和示例 UI 创建位置；调用 `lv_init()`、display/input/fs port，并默认运行 `lv_demo_widgets()`。 |
| `apps/common/lvgl_v9/examples/porting/lv_port_disp.c` | LVGL v9 display port；创建 `lv_display_t`，绑定 framebuffer，提供 `flush_cb`。 |
| `apps/common/lvgl_v9/examples/porting/lv_port_indev.c` | LVGL v9 input port；注册触摸、按键、编码器输入设备。 |
| `apps/common/lvgl_v9/examples/porting/lv_port_fs.c` | LVGL 文件系统 port；注册 `s:` 和 `m:` 盘符。 |
| `apps/common/lcd` | SDK 的 LCD/TP/fb 驱动公共层。 |

## 2. 启动链路

当前 demo 的运行路径可以按下面理解：

1. 系统启动后进入 `app_main()`
2. `app_main()` 调用 `lvgl_main_task_init()`
3. `lvgl_main_task_init()` 转到 `lvgl_v9_main_task_init()`
4. `lvgl_v9_main_task_init()` 创建 `LVGL_TASK_NAME` 任务，入口为 `lvgl_main_task()`
5. `lvgl_main_task()` 调用 `lvgl_v9_gui_init()`
6. `lvgl_v9_gui_init()` 完成：
   - `lv_init()`
   - `lv_port_disp_init()`
   - `lv_port_indev_init()`
   - `lv_port_fs_init()`
   - `lv_tick_set_cb(&timer_get_ms)`
   - 当前默认运行 `lv_demo_widgets()`
7. `lvgl_main_task()` 循环等待消息，并在合适时机调用 `lv_timer_handler()`

后续替换自己的 UI 时，优先关注 `lvgl_v9_gui_init()`。当前它在 `apps/common/lvgl_v9/lvgl_v9_main_task_init.c` 中，不在 `demo_ui` app 目录内，这是后续整理时最值得迁回 app 层的点。

## 3. LVGL 移植时要稳定保留的接口

这些接口是 SDK 和 LVGL 之间的桥，移植时不要轻易删：

| 接口 | 当前位置 | 说明 |
| --- | --- | --- |
| `lvgl_main_task_init()` | `apps/common/lvgl_v9/lvgl_v9_main_task_init.c` | app 入口调用的统一启动接口。 |
| `lvgl_v9_main_task_init()` | `apps/common/lvgl_v9/lvgl_main.c` | 创建 LVGL 主任务。 |
| `lvgl_main_task()` | `apps/common/lvgl_v9/lvgl_main.c` | LVGL 线程主体；处理 timer、touch、key、encoder、rpc、suspend/resume。 |
| `lvgl_v9_gui_init()` | `apps/common/lvgl_v9/lvgl_v9_main_task_init.c` | 当前 demo UI 初始化落点。 |
| `lv_port_disp_init()` | `apps/common/lvgl_v9/examples/porting/lv_port_disp.c` | display/FB 适配。 |
| `lv_port_indev_init()` | `apps/common/lvgl_v9/examples/porting/lv_port_indev.c` | 输入设备适配。 |
| `lv_port_fs_init()` | `apps/common/lvgl_v9/examples/porting/lv_port_fs.c` | 文件系统适配。 |
| `lcd_touch_interrupt_event()` | `apps/common/lvgl_v9/lvgl_main.c` | TP 驱动上报触摸中断后，转成 LVGL 触摸消息。 |
| `lvgl_key_event_handler_2()` | `apps/common/lvgl_v9/lvgl_main.c` | 系统按键事件转成 LVGL keypad/encoder 消息。 |

## 4. LCD/TP 配置入口

LCD 和触摸参数主要在 `apps/demo/demo_ui/board/wl83/board_develop_AC7926A.h`：

| 宏 | 当前含义 |
| --- | --- |
| `TCFG_LCD_ENABLE` | UI 打开时使能 LCD。 |
| `TCFG_LCD_INPUT_FORMAT` | 当前为 `LCD_IN_RGB565`，需要和 `lv_conf.h` 的颜色深度保持一致。 |
| `TCFG_LCD_MIPI_ST7701S_480x800` | 当前启用的屏驱。 |
| `TCFG_LCD_DEVICE_NAME` | 当前为 `"MIPI_480x800_ST7701S"`。 |
| `TCFG_LCD_RESET_IO` / `TCFG_LCD_BL_IO` | LCD 复位和背光 IO。 |
| `TCFG_TP_DRIVER_ENABLE` | 使能触摸驱动。 |
| `TCFG_TP_CST3240_ENABLE` | 当前启用 CST3240 触摸 IC。 |
| `TCFG_TP_RST_PIN` / `TCFG_TP_INT_PIN` | 触摸复位和中断 IO。 |
| `TCFG_TP_COMMUNICATE_IF` | 当前为 `"iic0"`。 |
| `TCFG_TP_SWAP_X_Y` / `TCFG_TP_X_MIRROR` / `TCFG_TP_Y_MIRROR` | 触摸坐标旋转/镜像参数。 |

换屏或换触摸时，优先改这里；如果是新增屏驱/触摸 IC，再进入 `apps/common/lcd/lcd_driver` 或 `apps/common/lcd/touch_driver`。

## 5. Framebuffer 和颜色格式

当前 demo 的关键配置：

| 宏 | 当前值 | 影响 |
| --- | --- | --- |
| `LV_DISP_UI_FB_NUM` | `2` | LVGL 使用两个 UI framebuffer，display port 走 DIRECT 模式。 |
| `FB_LCD_BUF_NUM` | `0` | LCD 侧 buffer 数量。 |
| `TCFG_LCD_INPUT_FORMAT` | `LCD_IN_RGB565` | 屏输入格式。 |
| `LV_COLOR_DEPTH` | 在 `apps/common/lvgl_v9/lv_conf.h` | 必须和 LCD 输入格式匹配。 |

注意点：

- `LV_DISP_UI_FB_NUM == 2` 时，`lv_port_disp.c` 会从 `fb0` 获取两个 map，作为 LVGL draw buffer。
- `LV_DISP_UI_FB_NUM == 0` 或 `1` 时，代码有另一套和 `fb_combine` 交互的路径，后续如果要做视频叠 UI 或省内存，需要单独验证。
- RGB565 配置下，`lv_port_disp.c` 使用 `FB_COLOR_FORMAT_RGB565` 或 `FB_COLOR_FORMAT_ARGB8565`，取决于 `LV_COLOR_DEPTH_EXTEN`。

## 6. 文件系统和资源路径

`lv_port_fs_init()` 注册了两个 LVGL 盘符：

| LVGL 盘符 | 用途 |
| --- | --- |
| `s:` | SD/JLFAT 路径。 |
| `m:` | flash 路径。 |

当前示例里有资源加载示例：

```c
lv_img_set_src(img, "mnt/sdfile/EXT_RESERVED/uipackres/ui/logoargb.bin");
lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/font1.rle");
```

但这段 `lv_example_img_bin()` 默认没有被调用。后续做产品 UI 时，建议统一资源路径策略：

- SD 调试阶段：使用 `s:/...` 或 SDK 当前可识别的挂载路径。
- 量产阶段：使用 reserved expand zone 或外部 flash，并同步配置 `CONFIG_UI_PACKRES_LEN` / `CONFIG_UI_PACKRES_ADR`。

## 7. 后续建议整理方向

建议按三步来做，风险比较小：

1. 先保留 `apps/common/lvgl_v9/lvgl_main.c`、`lv_port_disp.c`、`lv_port_indev.c`、`lv_port_fs.c` 不动，只替换 `lv_demo_widgets()` 为一个最小自定义页面，确认 LVGL 基础链路稳定。
2. 把 demo UI 初始化从 `apps/common/lvgl_v9/lvgl_v9_main_task_init.c` 下沉/迁移到 `apps/demo/demo_ui`，例如新增 `ui/demo_ui_lvgl.c`，让 app 层拥有自己的 `lvgl_v9_gui_init()`。
3. 再开始换屏、调触摸坐标、整理资源路径和裁剪 Makefile 中不需要的 camera/demo/third_party 源文件。

优先验证清单：

- 开机后能进入 `lvgl_v9_main_task_init` 日志。
- `lv_port_disp_init()` 能成功打开 `fb0`。
- 第一帧能刷出纯 LVGL 页面。
- 触摸按下能进入 `lcd_touch_interrupt_event()`。
- `lv_port_indev.c` 中 `touchpad_read()` 得到的坐标方向正确。
- 按键能进入 `lvgl_key_event_handler_2()`，必要时实现 `lvgl_key_value_remap()`。
- `lv_timer_handler()` 不应被长耗时业务阻塞。

## 8. 建议的应用层骨架

后续可以把 app 自己的 UI 收口成下面这种结构：

```text
apps/demo/demo_ui/
  app_main.c
  include/
    app_config.h
    demo_ui.h
  ui/
    demo_ui_lvgl.c      // 实现 lvgl_v9_gui_init 或 app_ui_create
    demo_ui_screens.c   // 页面创建和切换
    demo_ui_events.c    // 按键/触摸/业务事件桥接
    demo_ui_assets.h    // 资源声明或路径
  board/wl83/
    board_config.h
    board_develop_AC7926A.h
    board_develop.c
```

最小 UI 初始化建议先保持简单：

```c
void lvgl_v9_gui_init(void)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_port_fs_init();
    lv_tick_set_cb(&timer_get_ms);

    app_ui_create();
}
```

这样后续移植 LVGL 时，SDK port 层和业务 UI 层会比较清楚地分开。
