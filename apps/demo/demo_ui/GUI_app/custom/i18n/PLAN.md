# UI 多语言(i18n) 实施计划

> 依据 [DESIGN.md](DESIGN.md)。方案: GUI-Guider **中文当 key**,进屏遍历 label 查表换语言。
> 翻译数据用**现成的**(用户提供, 拼音 msg_id + 中英对照), 转成"中文→英文"手写进
> `lv_i18n.c`, 格式学 `D:/13.tool/lv_i18n/lv_i18n.c`(但 msg_id 用中文)。
> 验证方式: 嵌入式无单测框架, 每个任务靠**编译通过 + 模拟器目测**验证。

**全局约束**(每个任务都适用):
- 不改 GUI-Guider 生成的 `setup_scr_*.c` 的中文(永远先设中文, 进屏后替换)。
- 代码注释极简, 变量名 ≥5 字母或加全称注释, 禁单字母。
- 文件放 `GUI_app/i18n/`, 平台相关只在 `i18n_storage.c`。

---

## 阶段 1: 搭框架(先跑通"切英文→几条字变英文")

### 任务 1.1: 建 lv_i18n 翻译包骨架
- **建** `GUI_app/i18n/lv_i18n.h`: 复制参考 `D:/13.tool/lv_i18n/lv_i18n.h`(标准模板, 不改)。
- **建** `GUI_app/i18n/lv_i18n.c`: 复制参考的函数实现部分(init/set_locale/get_text/plural);
  数据部分先填**少量验证条目**(中文当 key):
  ```c
  static lv_i18n_phrase_t en_singulars[] = {
      {"网络设置", "Network Settings"},
      {"显示设置", "Display Settings"},
      {"语言设置", "Language Settings"},
      {NULL, NULL}
  };
  static const lv_i18n_lang_t en_lang = {
      .locale_name = "en", .singulars = en_singulars, .locale_plural_fn = en_plural_fn,
  };
  static const lv_i18n_lang_t zh_lang = {   // 默认语言, 查不到 fallback 返回中文 key
      .locale_name = "zh-CN", .singulars = NULL, .locale_plural_fn = NULL,
  };
  const lv_i18n_language_pack_t lv_i18n_language_pack[] = { &zh_lang, &en_lang, NULL };
  ```
- **验证**: 暂不编译, 阶段 1.4 一起编。

### 任务 1.2: 建 i18n 持久化(平台相关, 隔离单文件)
- **建** `GUI_app/i18n/i18n_storage.h`: 声明 `void i18n_storage_save_lang(uint8_t lang);`
  `uint8_t i18n_storage_load_lang(void);`
- **建** `GUI_app/i18n/i18n_storage.c`: 先用**静态变量桩**(VM API 待查 SDK, 阶段 4 补真持久化):
  ```c
  static uint8_t s_saved_lang;   // saved language: 0=中文 1=英文
  void i18n_storage_save_lang(uint8_t lang) { s_saved_lang = lang; }
  uint8_t i18n_storage_load_lang(void) { return s_saved_lang; }
  ```
- **验证**: 阶段 1.4 一起编。

### 任务 1.3: 建 i18n 核心
- **建** `GUI_app/i18n/i18n.h`: 对外 API
  ```c
  typedef enum { I18N_ZH = 0, I18N_EN = 1 } i18n_lang_t;
  void i18n_init(void);                       // 开机: lv_i18n_init + 读存储 + set_locale
  void i18n_apply_screen(lv_obj_t *scr);      // 遍历 scr 所有 label 换当前语言
  void i18n_set_lang(i18n_lang_t lang);       // 切换 + 存储 + 重载当前屏
  i18n_lang_t i18n_get_lang(void);
  ```
- **建** `GUI_app/i18n/i18n.c`:
  - `i18n_init`: `lv_i18n_init(lv_i18n_language_pack)` → 读 `i18n_storage_load_lang()` →
    `lv_i18n_set_locale(lang==I18N_EN?"en":"zh-CN")`, 存当前语言到 static。
  - `i18n_apply_screen`: 递归遍历 scr 子对象, 对每个 `lv_label`:
    ```c
    if (当前语言 == I18N_ZH) return;                 // 中文即 setup 原文, 不动
    const char *zh = lv_label_get_text(label);
    const char *tr = lv_i18n_get_text(zh);
    if (tr != zh) lv_label_set_text(label, tr);     // 查到才换(查不到 lv_i18n 返回原 key)
    ```
  - `i18n_set_lang`: `lv_i18n_set_locale(...)` + `i18n_storage_save_lang(lang)` + 存 static +
    重载当前屏(取 `lv_scr_act()` 对应的 setup 重建, 阶段 4 接 LanguageSet 时细化)。
  - `i18n_get_lang`: 返回 static 当前语言。
- **验证**: 阶段 1.4 一起编。

### 任务 1.4: Makefile 接入 + 开机初始化 + 编译
- **改** `board/wl83/Makefile`: `DEMO_UI_AUTO_SRCS` 加
  `$(wildcard $(GUI_APP_DIR)/i18n/*.c)`; `INCLUDES` 加
  `-I../../../../../apps/demo/demo_ui/GUI_app/i18n`。
- **改** `GUI_app/custom/custom.c` 的 `custom_init()` 末尾加 `i18n_init();`(此时所有屏已建)。
- **验证**: MCU `make` + 模拟器编译, 都过。开机日志正常。

### 任务 1.5: home 屏接入 apply, 验证机制通
- **改** `GUI_app/custom/screen/Home.c` 的 `home_on_screen_load()` 末尾加
  `i18n_apply_screen(guider_ui.ui_home_screen);`(此处仅为验证, 阶段 3 统一接全部屏)。
- **临时**: 把 `i18n_storage.c` 桩的 `s_saved_lang` 默认改 1(英文)试一次。
- **验证**: 模拟器进首页, "网络设置/显示设置/语言设置"(若 home 有)显示英文 → 机制通。
  验证后默认改回 0(中文)。

---

## 阶段 2: 翻译数据全量导入

### 任务 2.1: 现成数据转"中文当 key"
- 把用户提供的 `en_singulars`(拼音→英文) 与 `zh_cn_singulars`(拼音→中文) 按拼音 join,
  生成 `{中文: 英文}` 填进 `lv_i18n.c` 的 `en_singulars`。
- 撞车中文(如"打开"对 `DaKai`/`DaKai_Open`)取一个默认译文, 记下歧义点留阶段 4 处理。

### 任务 2.2: extract.js 覆盖核对
- **建** `GUI_app/i18n/tools/extract.js`: 扫 `setup_scr_*.c` 抠中文(正则
  `lv_label_set_text\([^,]+,\s*"([^"]*)"\)`, 筛含中文), 跟 `en_singulars` 比对,
  **打印没翻译的中文**。
- 跑一遍, 把缺失的中文补进表。

---

## 阶段 3: 接入各屏 apply

### 任务 3.1: 有 on_screen_load 的屏
- 每个 `custom/screen/*.c` 的 `*_on_screen_load()` 末尾加 `i18n_apply_screen(本屏)`。

### 任务 3.2: 纯 GUI-Guider 屏(无 custom)
- 在 GUI-Guider 给这些屏挂 `LV_EVENT_SCREEN_LOADED` → 调一个统一 apply 包装函数。

---

## 阶段 4: LanguageSet 切换 + 中间层 + 真持久化

### 任务 4.1: LanguageSet 接 set_lang
- **改** `custom/screen/LanguageSet.c`: `on_ok` 里调 `i18n_set_lang(s_pending_chinese?I18N_ZH:I18N_EN)`。

### 任务 4.2: 中间层记录语言
- **改** `HWDataAccess.c/.h`: 加 `HWInterface.Language`(current + SetLang/GetLang 转调 i18n)。

### 任务 4.3: 真持久化(VM)
- 查杰理 SDK 的 VM/syscfg API, 把 `i18n_storage.c` 的 static 桩换成真 flash 读写。

### 任务 4.4: 撞车词 + 动态文字
- 撞车中文 label 在对应屏 custom 里点名 `lv_i18n_get_text("正确msg_id")`(此处需中文区分,
  改用该 label 专属处理)。
- 动态文字(下载进度/天气)在 custom 里 `lv_i18n_get_text("中文")` 拼接。

---

## 阶段 5: 逐屏校验(模拟器, 用户主导)
- 逐屏切英文, 查: 字符缺失(字体没该字母)、排版溢出(英文比中文长撑破 label)。
- 缺字 → GUI-Guider 重生成字体补 ASCII; 溢出 → 调宽度/字号。
