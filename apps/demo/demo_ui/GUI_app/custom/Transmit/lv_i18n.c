#include "./lv_i18n.h"


////////////////////////////////////////////////////////////////////////////////
// Define plural operands
// http://unicode.org/reports/tr35/tr35-numbers.html#Operands

// Integer version, simplified

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static lv_i18n_phrase_t zh_cn_singulars[] = {
    {"10分钟", "10分钟"},
    {"15秒", "15秒"},
    {"1分钟", "1分钟"},
    {"2分钟\n", "2分钟\n"},
    {"30秒", "30秒"},
    {"5分钟", "5分钟"},
    {"中", "中"},
    {"中文(简体)", "中文(简体)"},
    {"亮 度 | 50%", "亮 度 | 50%"},
    {"传感器配置", "传感器配置"},
    {"使用说明", "使用说明"},
    {"关", "关"},
    {"关于产品", "关于产品"},
    {"关闭", "关闭"},
    {"制冷", "制冷"},
    {"制热", "制热"},
    {"卷  帘", "卷  帘"},
    {"取消", "取消"},
    {"场景", "场景"},
    {"场景一", "场景一"},
    {"场景七", "场景七"},
    {"场景三", "场景三"},
    {"场景二", "场景二"},
    {"场景五", "场景五"},
    {"场景八", "场景八"},
    {"场景六", "场景六"},
    {"场景四", "场景四"},
    {"型号", "型号"},
    {"屏保", "屏保"},
    {"布  帘", "布  帘"},
    {"延时进入待机时间", "延时进入待机时间"},
    {"开关\n", "开关\n"},
    {"开关配置", "开关配置"},
    {"开始学码", "开始学码"},
    {"开始绑定", "开始绑定"},
    {"彩色灯", "彩色灯"},
    {"待机显示", "待机显示"},
    {"恢复出厂", "恢复出厂"},
    {"情景模式1", "情景模式1"},
    {"情景模式2", "情景模式2"},
    {"情景模式3", "情景模式3"},
    {"情景模式4", "情景模式4"},
    {"按键1", "按键1"},
    {"按键1  互控", "按键1  互控"},
    {"按键2", "按键2"},
    {"按键2  互控", "按键2  互控"},
    {"按键3", "按键3"},
    {"按键3  互控", "按键3  互控"},
    {"接近亮屏", "接近亮屏"},
    {"星期一", "星期一"},
    {"是否将语言更改为:", "是否将语言更改为:"},
    {"是否重启设备?", "是否重启设备?"},
    {"显示设置", "显示设置"},
    {"晾衣机", "晾衣机"},
    {"梦幻帘", "梦幻帘"},
    {"永久", "永久"},
    {"浴  霸", "浴  霸"},
    {"清除已学", "清除已学"},
    {"清除所有数据,请谨慎确认!", "清除所有数据,请谨慎确认!"},
    {"温度", "温度"},
    {"湿度", "湿度"},
    {"灯  带", "灯  带"},
    {"灯光", "灯光"},
    {"灯光全关", "灯光全关"},
    {"灯光全开", "灯光全开"},
    {"灯光情景", "灯光情景"},
    {"熄屏", "熄屏"},
    {"确定", "确定"},
    {"磁吸灯", "磁吸灯"},
    {"空  调", "空  调"},
    {"窗帘", "窗帘"},
    {"窗帘全关", "窗帘全关"},
    {"窗帘全开", "窗帘全开"},
    {"窗帘情景", "窗帘情景"},
    {"纱  帘", "纱  帘"},
    {"网络设置", "网络设置"},
    {"色 温 | 4850K", "色 温 | 4850K"},
    {"色温灯", "色温灯"},
    {"解除设备", "解除设备"},
    {"设  置", "设  置"},
    {"设备", "设备"},
    {"设备已经绑定米家App", "设备已经绑定米家App"},
    {"设备未绑定米家", "设备未绑定米家"},
    {"设备管理", "设备管理"},
    {"设备重启", "设备重启"},
    {"语言设置", "语言设置"},
    {"近", "近"},
    {"远\n", "远\n"},
    {"送风", "送风"},
    {"重启", "重启"},
    {"重置", "重置"},
    {"除湿", "除湿"},
    {"音  乐", "音  乐"},
    {"颜 色 | #00718D", "颜 色 | #00718D"},
    {"风扇灯", "风扇灯"},
    {NULL, NULL} // End mark
};



static uint8_t zh_cn_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
    .locale_name = "zh-CN",
    .singulars = zh_cn_singulars,

    .locale_plural_fn = zh_cn_plural_fn
};

static lv_i18n_phrase_t en_gb_singulars[] = {
    {"10分钟", "10 mins"},
    {"15秒", "15 s"},
    {"1分钟", "1 mins"},
    {"30秒", "30 s"},
    {"5分钟", "5 mins"},
    {"中", "Medium"},
    {"使用说明", "Operating Instructions"},
    {"关于产品", "About the Product"},
    {"关闭", "Close"},
    {"制冷", "Cool"},
    {"制热", "Heat"},
    {"取消", "Cancel"},
    {"屏保", "Screensaver"},
    {"开始绑定", "Start Binding"},
    {"恢复出厂", "Restore Factory Settings"},
    {"按键1", "Button 1"},
    {"按键2", "Button 2"},
    {"按键3", "Button 3"},
    {"接近亮屏", "Proximity Screen Lighting"},
    {"星期一", "Mon."},
    {"是否重启设备?", "Would you like to restart the device?"},
    {"显示设置", "Display Settings"},
    {"确定", "Confirm"},
    {"网络设置", "Network Settings"},
    {"设备", "Device"},
    {"设备未绑定米家", "The device is not bound to Mijia."},
    {"设备管理", "Device Management"},
    {"设备重启", "Device Restart"},
    {"语言设置", "Language Settings"},
    {"近", "Near"},
    {"送风", "Fan"},
    {"重启", "Restart"},
    {"重置", "Reset"},
    {"除湿", "Dry"},
    {NULL, NULL} // End mark
};



static uint8_t en_gb_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_gb_lang = {
    .locale_name = "en-GB",
    .singulars = en_gb_singulars,

    .locale_plural_fn = en_gb_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &zh_cn_lang,
    &en_gb_lang,
    NULL // End mark
};

////////////////////////////////////////////////////////////////////////////////


// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
 * Reset internal state. For testing.
 */
void __lv_i18n_reset(void)
{
    current_lang_pack = NULL;
    current_lang = NULL;
}

/**
 * Set the languages for internationalization
 * @param langs pointer to the array of languages. (Last element has to be `NULL`)
 */
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
    if(langs == NULL) return -1;
    if(langs[0] == NULL) return -1;

    current_lang_pack = langs;
    current_lang = langs[0];     /*Automatically select the first language*/
    return 0;
}

/**
 * Change the localization (language)
 * @param l_name name of the translation locale to use. E.g. "en-GB"
 */
int lv_i18n_set_locale(const char * l_name)
{
    if(current_lang_pack == NULL) return -1;

    uint16_t i;

    for(i = 0; current_lang_pack[i] != NULL; i++) {
        // Found -> finish
        if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
            current_lang = current_lang_pack[i];
            return 0;
        }
    }

    return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
    uint16_t i;
    for(i = 0; trans[i].msg_id != NULL; i++) {
        if(strcmp(trans[i].msg_id, msg_id) == 0) {
            /*The msg_id has found. Check the translation*/
            if(trans[i].translation) return trans[i].translation;
        }
    }

    return NULL;
}


/**
 * Get the translation from a message ID
 * @param msg_id message ID
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text(const char * msg_id)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;

    // Search in current locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->singulars != NULL) {
        txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
        if (txt != NULL) return txt;
    }

    return msg_id;
}

/**
 * Get the translation from a message ID and apply the language's plural rule to get correct form
 * @param msg_id message ID
 * @param num an integer to select the correct plural form
 * @return the translation of `msg_id` on the set local
 */
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
    if(current_lang == NULL) return msg_id;

    const lv_i18n_lang_t * lang = current_lang;
    const void * txt;
    lv_i18n_plural_type_t ptype;

    // Search in current locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    // Try to fallback
    if(lang == current_lang_pack[0]) return msg_id;
    lang = current_lang_pack[0];

    // Repeat search for default locale
    if(lang->locale_plural_fn != NULL) {
        ptype = lang->locale_plural_fn(num);

        if(lang->plurals[ptype] != NULL) {
            txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
            if (txt != NULL) return txt;
        }
    }

    return msg_id;
}

/**
 * Get the name of the currently used locale.
 * @return name of the currently used locale. E.g. "en-GB"
 */
const char * lv_i18n_get_current_locale(void)
{
    if(!current_lang) return NULL;
    return current_lang->locale_name;
}
