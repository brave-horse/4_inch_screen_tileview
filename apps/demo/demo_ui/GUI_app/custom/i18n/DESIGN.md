# UI 多语言(i18n)设计文档

> 日期: 2026-06-27
> 目标: 给 demo_ui(LVGL v8.3, GUI-Guider) 加中英文切换,默认中文,可断电记住,
>       架构与杰理 SDK 解耦,方便日后移植到其他芯片/SDK。

## 1. 目标与约束

- 默认中文,设置→语言界面点击可切换中/英,以后能扩展第三种语言。
- 切换后**断电记住**(存 VM/flash),开机读回。
- **中间层 HWInterface 记录当前语言**。
- **零改 GUI-Guider**:它生成的 setup 每次覆盖,i18n 不能依赖改它的代码。
- **可移植**:平台无关核心 + 一个薄适配层,换芯片只改一个文件。

现状(摸底结论):
- 24 个屏,`lv_label_set_text` 共 265 处,含中文 133 处,去重后 **95 条**唯一中文。
- 中文字体 MiSans/全维君黑**已含拉丁字母**→ 切语言基本不换字体,只换文字。
- 仅首页 6 个 label(除湿/制热/制冷/送风/关/16℃)用全维君黑显示中文,建议在
  GUI-Guider 里统一改 MiSans_30。

## 2. 核心决策:方案A——中文原文当 key

不碰 GUI-Guider 的 133 处 `lv_label_set_text(label,"中文")`。setup **永远先设中文**,
进屏后按"中文原文"查翻译表换成当前语言。

为什么不用 lv_i18n 标准 `_("中文")` 内联:GUI-Guider 生成的代码没有 `_()`,且每次
重新生成会覆盖,塞不进去。所以改用"**进屏遍历 label 替换**"绕开。

切回中文不需要反向表:setup 总是先设中文,切换时**重载当前屏**即可回到中文再 apply。

## 3. 工具链与数据流

`lv_i18n`(LVGL 官方 npm 工具)负责"翻译包生成 + O(1) 查找函数";我们只补"扫中文"
和"进屏替换"两块。全部命令行步骤离线跑,不在 GUI-Guider 里,可由助手代跑。

```
构建期(改文案/加语言时离线跑一次):
  setup_scr_*.c ─[extract.js 扫中文]→ zh-CN.yml/en-GB.yml
                                      ↓(填英文翻译)
                 lv_i18n compile  ─→ lv_i18n.c/.h (翻译包 + 查找函数)
                                      ↓
                            编进固件(普通 .c,Makefile wildcard 自动收)

运行期(MCU):
  进屏 → GUI-Guider setup 设中文 → screen_loaded → i18n_apply_screen(本屏)
       → 遍历 label,lv_i18n_get_text(中文) → 换当前语言

切换(LanguageSet 点确定):
  i18n_set_lang(EN) → lv_i18n_set_locale + 存VM → 重载当前屏 → 新语言显示
```

`extract.js` 与 `lv_i18n extract` 区别只有一个正则:前者找 `lv_label_set_text(x,"...")`,
后者找 `_("...")`。其余一致。

## 4. 目录结构与文件清单

放 `GUI_app/i18n/`(独立真实目录,脱离 GUI-Guider 符号链接,整体可移植)。

```
GUI_app/i18n/
  DESIGN.md          本文档
  i18n.h             对外 API: i18n_init/set_lang/get_lang/apply_screen   [可移植]
  i18n.c             运行时核心: 遍历 label 替换 + 管当前语言            [可移植,纯LVGL]
  i18n_storage.h     持久化接口声明: storage_save_lang/storage_load_lang  [可移植]
  i18n_storage.c     VM 持久化实现(存/读语言)                  [平台相关,移植适配这个]
  lv_i18n.h          lv_i18n compile 生成,翻译包头                        [可移植]
  lv_i18n.c          lv_i18n compile 生成,翻译表+查找                     [可移植,勿手改]
  tools/             离线工具,不进固件
    extract.js       扫 setup_scr_*.c 抠中文 → yml
    zh-CN.yml        中文源(key=中文, 值=中文)
    en-GB.yml        英文翻译(key=中文, 值=英文; 助手填)
    package.json     锁 lv_i18n 版本
```

Makefile(board/wl83/Makefile)需加两行:
- `DEMO_UI_AUTO_SRCS += $(wildcard $(GUI_APP_DIR)/i18n/*.c)`
- `INCLUDES += -I../../../../../apps/demo/demo_ui/GUI_app/i18n`

## 5. 移植策略(诚实版)

整个应用层(bsp/class/Fuc/GUI_app/Task)一起移植是个工程,不是改一个文件的事:
项目**没有统一 HAL**,平台相关的 SDK 调用(os_ 队列/VM/硬件驱动)直接散在各模块的
`Soc/` 实现里(如 Task/Soc 直接调 os_q_create),移植时逐个适配。i18n 能做的,是把
自己的平台相关面**收敛到最小**——只有一个 `i18n_storage.c` 碰 VM。

i18n 内部依赖方向:
```
屏 on_screen_load ─→ i18n_apply_screen()  ┐ 都只调 i18n.h
LanguageSet 确定  ─→ i18n_set_lang()       ┘
i18n.c(核心,纯LVGL) ─→ lv_i18n_get_text()/set_locale()  (官方,通用)
                    └→ i18n_storage_save/load_lang()  ─→ i18n_storage.h(接口)
                                                            ↑
                                          i18n_storage.c(杰理 VM, 平台相关只在这一个文件)
```

核心 `i18n.c` 不直接碰杰理 VM,只调 `i18n_storage_*()` 接口。移植 i18n 模块时:
1. 复制整个 `GUI_app/i18n/` 目录(自包含,一拎就走)。
2. 适配 `i18n_storage.c` 的 VM 调用 → 新芯片存储 API。这是**整个应用层移植的一环**,
   跟 Task/Soc 适配 os_、bsp 适配硬件驱动 同性质,不是 i18n 独有的负担。
3. 其余文件(i18n.c / lv_i18n.c / 翻译包)与平台无关,不改。
4. 语言状态在 `HWInterface.Language` 做薄封装转调 i18n;i18n 核心**不依赖**
   HWInterface,新项目无此中间层也能用。

## 6. 运行时机制

### i18n_apply_screen(scr)
递归遍历 scr 全部子对象,对每个 `lv_label`:
```
text = lv_label_get_text(label)          // 进屏时是中文(setup 设的)
if 当前 locale 非中文:
    tr = lv_i18n_get_text(text)          // text=中文原文当 key
    if tr != text: lv_label_set_text(label, tr)   // 查到才换;查不到保持中文(安全)
```

### 接入点
每屏 `*_on_screen_load` 末尾调 `i18n_apply_screen(本屏)`。已有 on_screen_load 的屏
直接加一行;没有的屏(纯 GUI-Guider)在 GUI-Guider 里挂 screen_loaded 事件调用。

### i18n_set_lang(lang)
```
lv_i18n_set_locale(locale_name[lang])
i18n_storage_save_lang(lang)             // 存 VM
重载当前屏(lv_scr 重新 setup → 中文 → apply 新语言)
```
重载是因为当前屏 label 可能已是英文,无法再用中文 key 查;重载回中文最简单可靠。

### 开机 i18n_init()
```
lv_i18n_init(翻译包)
lang = i18n_storage_load_lang()          // VM 读,默认中文
lv_i18n_set_locale(locale_name[lang])
```
之后每屏 screen_loaded 自动 apply。

### 中间层 HWInterface.Language
`{ current_lang; SetLang(); GetLang(); }`,SetLang 内部转调 i18n_set_lang。
满足"中间层记录当前语言"。

## 7. 边界与风险

- **动态文字**:custom 里 `lv_label_set_text_fmt` 拼的(如"亮度|50%"、温度、百分比)
  不在静态 setup 中文里,apply 扫不到。其中纯数字不用翻译;少数含中文前缀的,在
  custom 代码里单独用 `lv_i18n_get_text` 拼。**逐处人工处理**。
- **字符缺失**:英文翻译若用到字体里没有的字母,显示空白。需在 GUI-Guider 重新生成
  MiSans 时勾选完整 ASCII。**翻译完成后逐屏切英文目测排查**。
- **排版溢出**:英文通常比中文长,可能撑破固定宽度 label。逐屏目测,必要时调宽度
  或缩字号。
- **lv_i18n 查不到**:`lv_i18n_get_text` 查不到返回原 key(中文),不会崩,安全降级。

## 8. 分阶段实施

1. **搭框架**:i18n.c/h + i18n_port_jl.c + lv_i18n 接入 + Makefile + 中间层
   Language + LanguageSet 接 set_lang。翻译表先填几条(网络/显示/语言)验证机制通。
2. **全量翻译**:extract.js 扫 95 条 → 助手全翻译填 en-GB.yml → compile。
3. **接入各屏**:每屏 on_screen_load 加 apply;纯 GUI-Guider 屏挂 screen_loaded。
4. **动态文字**:处理 custom 里含中文的动态拼接文字。
5. **校验**:逐屏切英文,查字符缺失/排版溢出;首页 6 label 改 MiSans_30。

## 9. 待定项

- VM 存储具体 API(syscfg/vm)在实施阶段查 SDK 确认。
- locale 命名:用 lv_i18n 习惯的 `zh-CN` / `en-GB`。
- 第三语言扩展:加 yml 文件 + 助手翻译 + recompile,核心代码不动。
