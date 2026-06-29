# screen/ — 单屏控件改动

放"只影响单个屏幕"的控件改动（对应需求文档 custom 第 4 项）。

- 与 `generated/` 里的 `setup_scr_screen*.c` 一一对应：要改某个屏的控件，就建一个同名的
  `scr_xxx.c`（如 `scr_screen_1.c`），把改动放进去，**不要去动 generated**。
- 改动靠"轮询发现活动屏指针变化后再 apply"的方式落到对应屏上（屏会被 auto_del 重建，
  指针会变，参考 rule/scr_noscroll.c 的 poll 模式）。
- 在 `custom.c` 里调用其入口函数拉起。

当前为空：暂无单屏改动需求，按产品需要逐步添加。
