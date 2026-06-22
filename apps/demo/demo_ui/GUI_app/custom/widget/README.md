# widget/ — 跨单屏的新增控件

放"自己新增、可跨屏复用"的 LVGL 控件（对应需求文档 custom 第 3 项）。

- 每个控件一个 `.c`，对外接口放到 `include/` 下对应的 `.h`，并在 `include/custom_modules.h` 里 `#include`。
- 在 `custom.c` 的 `custom_init()` 里调用其 `xxx_init(ui)` 拉起。
- 参考 dem3333 的 `widgets/`：tileview_fix、btn 置顶、pulldown（安卓下拉面板）、curtain。
  这些都**绑死了 dem3333 自己的控件名**，本工程控件不同，需要按本工程 `gui_guider.h` 重写后再放进来。

当前为空：本工程暂无跨屏自定义控件需求，按产品需要逐步添加。
