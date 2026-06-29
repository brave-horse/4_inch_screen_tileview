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

static lv_i18n_phrase_t en_singulars[] = {
    {"ZhiLeng", "Cool"},
    {"ZhiRe", "Heat"},
    {"SongFeng", "Fan"},
    {"ChuShi", "Dry"},
    {"ZiDong", "Auto"},
    {"DiFeng", "Low"},
    {"ZhongFeng", "Medium"},
    {"GaoFeng", "High"},
    {"NuanFengGao", "High Heat"},
    {"NuanFengDi", "Low Heat"},
    {"HuanQi", "Air Circulation"},
    {"DianShi", "TV"},
    {"LingZhongLi", "Zero Gravity"},
    {"ZhiHan", "Anti-Snoring"},
    {"PingTang", "Flat Lying"},
    {"BeiBuShengJiang", "Back Lift"},
    {"TuiBuShengJiang", "Leg Lift"},
    {"DaKai", "Turn On"},
    {"ZanTing", "Pause"},
    {"KaiHeDu", "Opening Degree"},
    {"SheBeiGuanLi", "Device Management"},
    {"YiXuanZeDaiJiXianShiXiPing", "The Standby Display Off option has been selected, yet the operation is invalid."},
    {"QiangFeng", "Powerful"},
    {"XingQiYi", "Mon."},
    {"XingQiEr", "Tue."},
    {"XingQiSan", "Wed."},
    {"XingQiSi", "Thu."},
    {"XingQiWu", "Fri."},
    {"XingQiLiu", "Sat."},
    {"XingQiTian", "Sun."},
    {"AnJian1", "Button 1"},
    {"AnJian2", "Button 2"},
    {"AnJian3", "Button 3"},
    {"ZhuYeFengGeSheZhi", "Homepage Style Settings"},
    {"RiGuangMoShi", "Daylight"},
    {"YueGuangMoShi", "Moonlight"},
    {"WenXinMoShi", "Warm"},
    {"YingYuanMoShi", "Cinema"},
    {"YueDuMoShi", "Reading"},
    {"BanGongMoShi", "Office"},
    {"LiangDu", "Brightness"},
    {"SeWen", "Color Temperature"},
    {"SuiJiZhengXiang", "Forward"},
    {"SuiJiFanXiang", "Reverse"},
    {"LiuXingPaoMa", "Meteor"},
    {"CaiSeZhuiZhu", "Chase"},
    {"CaiHongJianBian", "Rainbow"},
    {"CaiSeTianChong", "Fill"},
    {"MingLiang", "Bright"},
    {"WenXin", "Warm"},
    {"YueDu", "Reading"},
    {"GuanYing", "Movie Watching"},
    {"XiuXian", "Leisure"},
    {"LiKai", "Leave"},
    {"JiuCan", "Dining"},
    {"QiChuang", "Wake Up"},
    {"ShuiMian", "Sleep"},
    {"QiYe", "Night Urination"},
    {"PengRen", "Cooking"},
    {"XiShu", "Washing"},
    {"RuCe", "Using the Bathroom"},
    {"MuYu", "Bathing"},
    {"YinYue", "Music"},
    {"DianJing", "E-sports"},
    {"QuXiao", "Cancel"},
    {"QueDing", "Confirm"},
    {"NuanFeng", "Warm Fan"},
    {"QingFeng", "Fresh Breeze"},
    {"ZhiNengChangJing1", "Smart Scene 1"},
    {"ZhiNengChangJing2", "Smart Scene 2"},
    {"ZhiNengChangJing3", "Smart Scene 3"},
    {"ZhiNengChangJing4", "Smart Scene 4"},
    {"ZhiNengChangJing5", "Smart Scene 5"},
    {"ZhiNengChangJing6", "Smart Scene 6"},
    {"ZhiNengChangJing7", "Smart Scene 7"},
    {"ZhiNengChangJing8", "Smart Scene 8"},
    {"SheZhi", "Settings"},
    {"ChanPinXingHao", "Product Model"},
    {"GuJianBanBen", "Firmware Version"},
    {"YingJianBanBen", "Hardware Version"},
    {"GuanYuChanPin", "About the Product"},
    {"WangLuoSheZhi", "Network Settings"},
    {"SheBeiWeiBangDingMiJia", "The device is not bound to Mijia."},
    {"KaiShiBangDing", "Start Binding"},
    {"QingShiYongMiJiaAppSaoMa", "Please scan the QR code using the Mijia App."},
    {"SheBeiYiBangDingMiJiaApp", "The device has been bound to the Mijia App."},
    {"JieBangSheBei", "Unbind Device"},
    {"ShiFouQueDingYaoJieBangSheBei", "Are you sure you want to unbind the device?"},
    {"SheBeiChongQi", "Device Restart"},
    {"ShiFouChongQiSheBei", "Would you like to restart the device?"},
    {"ChongQi", "Restart"},
    {"HuiFuChuChang", "Restore Factory Settings"},
    {"QingChuSuoYouShuJu", "Erase all data. Please confirm carefully!"},
    {"ChongZhi", "Reset"},
    {"15Miao", "15 s"},
    {"30Miao", "30 s"},
    {"1FenZhong", "1 mins"},
    {"2FenZhong", "2 mins"},
    {"5FenZhong", "5 mins"},
    {"10FenZhong", "10 mins"},
    {"YongBu", "Never"},
    {"XiPing", "Screen Off"},
    {"PingBao", "Screensaver"},
    {"ZhuPing", "Main Screen"},
    {"SheBei", "Device"},
    {"BenDIChangJing", "Local Scenes"},
    {"ZhiNengChangJing", "Smart Scenes"},
    {"Jin", "Near"},
    {"Zhong", "Medium"},
    {"Yuan", "Far"},
    {"XianShiSheZhi", "Display Settings"},
    {"ZiDongSuoPing", "Automatic Screen Lock"},
    {"SuoPingXianShi", "Lock-screen Display"},
    {"JieJinLiangPing", "Proximity Screen Lighting"},
    {"XiTongSheZhi", "System Settings"},
    {"YuYan", "Language"},
    {"ShiYongShuoMing", "Operating Instructions"},
    {"GuanBi", "Turn Off"},
    {"BenDiChangJing", "Local Scenes"},
    {"YuYanSheZhi", "Language Settings"},
    {"TianQi_QingJianDuoYun", "Partly Cloudy"},
    {"TianQi_DaBuDuoYun", "Mostly Cloudy"},
    {"TianQi_LeiZhenYu", "Thundershower"},
    {"TianQi_LeiZhenYuBanYouBingBao", "Thundershower with Hail"},
    {"TianQi_ZhenXue", "Snow Flurry"},
    {"TianQi_ShaChenBao", "Duststorm"},
    {"TianQi_Feng", "Windy"},
    {"TianQi_DaFeng", "Blustery"},
    {"TianQi_JuFeng", "Hurricane"},
    {"TianQi_ReDaiFengBao", "Tropical Storm"},
    {"TianQi_LongJuanFeng", "Tornado"},
    {"TianQi_Leng", "Cold"},
    {"TianQi_Re", "Hot"},
    {"TianQi_WeiZhi", "Unknown"},
    {"TianQi_Qing", "Sunny"},
    {"TianQi_DuoYun", "Cloudy"},
    {"TianQi_Yin", "Overcast"},
    {"TianQi_ZhenYu", "Shower"},
    {"TianQi_XiaoYu", "Light Rain"},
    {"TianQi_ZhongYu", "Moderate Rain"},
    {"TianQi_DaYu", "Heavy Rain"},
    {"TianQi_BaoYu", "Rainstorm"},
    {"TianQi_DaBaoYu", "Heavy Rainstorm"},
    {"TianQi_TeDaBaoYu", "Severe Rainstorm"},
    {"TianQi_DongYu", "Ice Rain"},
    {"TianQi_YuJiaXue", "Sleet"},
    {"TianQi_XiaoXue", "Light Snow"},
    {"TianQi_ZhongXue", "Moderate Snow"},
    {"TianQi_DaXue", "Heavy Snow"},
    {"TianQi_BaoXue", "Snowstorm"},
    {"TianQi_FuChen", "Dust"},
    {"TianQi_YangSha", "Sand"},
    {"TianQi_QiangShaChenBao", "Sandstorm"},
    {"TianQi_Wu", "Foggy"},
    {"TianQi_Mai", "Haze"},
    {"diandong", "Jog"},
    {"DangQianMeiYouSheBei", "\t\tNo devices currently, \nplease add devices in the App"},
    {"DaKaiDingShiXiPing", "Turn on auto screen off"},
    {"GuanBiDingShiXiPing", "Turn off auto screen off"},
    {"DaKai_Open", "Open"},
    {"GuanBi_Close", "Close"},
    {"QingJing1", "Scene 1"},
    {"QingJing2", "Scene 2"},
    {"QingJing3", "Scene 3"},
    {"QingJing4", "Scene 4"},
    {"QingJing5", "Scene 5"},
    {"QingJing6", "Scene 6"},
    {"GuJianGengXinZhong", "Firmware updating..."},
    {"ZhengZaiShengJi", "Upgrading in progress, \nplease don't power outage"},
    {"NeiCunFenPeiShiBai", "RAM allocation failed"},
    {"GuJianXiaZaiShiBai", "Firmware download failed"},
    {"GuJianJieXiShiBai", "Firmware parsing failed"},
    {"ZhengZaiAnZhuangGuJian", "Installing firmware..."},
    {"GuJianAnZhuangChengGong", "Firmware installation successful, \nrestarting..."},
    {"GuJianYanZhengShiBai", "Firmware verification failed"},
    {"XiaXaiJinDu", "Download progress: %d%%"},
    {"ShuiMianMoShi", "Sleep Mode"},
    {"GanYingKaiGuan", "Proximity Mode"},
    {"WuRaoMoShi", "Silent mode"},
    {NULL, NULL} // End mark
};



static uint8_t en_plural_fn(int32_t num)
{
    uint32_t n = op_n(num); UNUSED(n);
    uint32_t i = op_i(n); UNUSED(i);
    uint32_t v = op_v(n); UNUSED(v);

    if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_lang = {
    .locale_name = "en",
    .singulars = en_singulars,

    .locale_plural_fn = en_plural_fn
};

static lv_i18n_phrase_t zh_cn_singulars[] = {
    {"SheZhi", "设置"},
    {"GuanYuChanPin", "关于产品"},
    {"WangLuoSheZhi", "网络设置"},
    {"SheBeiWeiBangDingMiJia", "设备未绑定米家"},
    {"KaiShiBangDing", "开始绑定"},
    {"QingShiYongMiJiaAppSaoMa", "请使用米家App扫码"},
    {"SheBeiYiBangDingMiJiaApp", "设备已绑定米家App"},
    {"JieBangSheBei", "解绑设备"},
    {"ShiFouQueDingYaoJieBangSheBei", "是否确定要解绑设备?"},
    {"SheBeiChongQi", "设备重启"},
    {"HuiFuChuChang", "恢复出厂"},
    {"XianShiSheZhi", "显示设置"},
    {"XiTongSheZhi", "系统设置"},
    {"YuYan", "语言"},
    {"QuXiao", "取消"},
    {"QueDing", "确定"},
    {"SheBeiGuanLi", "设备管理"},
    {"ZhuYeFengGeSheZhi", "主页风格设置"},
    {"BenDiChangJing", "本地场景"},
    {"ChuanGanQiPeiZhi", "传感器配置"},
    {"KaiGuanPeiZhi", "开关配置"},
    {"ShiYongShuoMing", "使用说明"},
    {"ChanPinXingHao", "产品型号"},
    {"GuJianBanBen", "固件版本"},
    {"YingJianBanBen", "硬件版本"},
    {"ShiFouChongQiSheBei", "是否重启设备?"},
    {"ChongQi", "重启"},
    {"QingChuSuoYouShuJu", "清除所有数据, 请谨慎确认！"},
    {"ChongZhi", "重置"},
    {"15Miao", "15秒"},
    {"30Miao", "30秒"},
    {"1FenZhong", "1分钟"},
    {"2FenZhong", "2分钟"},
    {"5FenZhong", "5分钟"},
    {"10FenZhong", "10分钟"},
    {"YongBu", "永不"},
    {"XiPing", "息屏"},
    {"PingBao", "屏保"},
    {"ZhuPing", "主屏"},
    {"SheBei", "设备"},
    {"BenDIChangJing", "本地场景"},
    {"ZhiNengChangJing", "智能场景"},
    {"GuanBi", "关闭"},
    {"Jin", "近"},
    {"Zhong", "中"},
    {"Yuan", "远"},
    {"ZiDongSuoPing", "自动锁屏"},
    {"SuoPingXianShi", "锁屏显示"},
    {"JieJinLiangPing", "接近亮屏"},
    {"RiGuangMoShi", "日光"},
    {"YueGuangMoShi", "月光"},
    {"WenXinMoShi", "温馨"},
    {"YingYuanMoShi", "影院"},
    {"YueDuMoShi", "阅读"},
    {"BanGongMoShi", "办公"},
    {"LiangDu", "亮 度"},
    {"SeWen", "色 温"},
    {"DaKai", "打开"},
    {"ZanTing", "暂停"},
    {"KaiHeDu", "开合度"},
    {"SuiJiZhengXiang", "随机正向"},
    {"SuiJiFanXiang", "随机反向"},
    {"LiuXingPaoMa", "流星跑马"},
    {"CaiSeZhuiZhu", "彩色追逐"},
    {"CaiHongJianBian", "彩虹渐变"},
    {"CaiSeTianChong", "彩色填充"},
    {"ZhiLeng", "制冷"},
    {"ZhiRe", "制热"},
    {"SongFeng", "送风"},
    {"ChuShi", "除湿"},
    {"ZiDong", "自动"},
    {"DiFeng", "低风"},
    {"ZhongFeng", "中风"},
    {"GaoFeng", "高风"},
    {"QiangFeng", "强风"},
    {"NuanFengGao", "暖风高"},
    {"NuanFengDi", "暖风低"},
    {"HuanQi", "换气"},
    {"NuanFeng", "暖风"},
    {"QingFeng", "清风"},
    {"DianShi", "电视"},
    {"LingZhongLi", "零重力"},
    {"ZhiHan", "止鼾"},
    {"PingTang", "平躺"},
    {"BeiBuShengJiang", "背部升降"},
    {"TuiBuShengJiang", "腿部升降"},
    {"MingLiang", "明亮"},
    {"WenXin", "温馨"},
    {"YueDu", "阅读"},
    {"GuanYing", "观影"},
    {"XiuXian", "休闲"},
    {"LiKai", "离开"},
    {"JiuCan", "就餐"},
    {"QiChuang", "起床"},
    {"ShuiMian", "睡眠"},
    {"QiYe", "起夜"},
    {"PengRen", "烹饪"},
    {"XiShu", "洗漱"},
    {"RuCe", "如厕"},
    {"MuYu", "沐浴"},
    {"YinYue", "音乐"},
    {"DianJing", "电竞"},
    {"ZhiNengChangJing1", "智能场景1"},
    {"ZhiNengChangJing2", "智能场景2"},
    {"ZhiNengChangJing3", "智能场景3"},
    {"ZhiNengChangJing4", "智能场景4"},
    {"ZhiNengChangJing5", "智能场景5"},
    {"ZhiNengChangJing6", "智能场景6"},
    {"ZhiNengChangJing7", "智能场景7"},
    {"ZhiNengChangJing8", "智能场景8"},
    {"YiXuanZeDaiJiXianShiXiPing", "已选择待机显示熄屏，操作无效"},
    {"XingQiYi", "星期一"},
    {"XingQiEr", "星期二"},
    {"XingQiSan", "星期三"},
    {"XingQiSi", "星期四"},
    {"XingQiWu", "星期五"},
    {"XingQiLiu", "星期六"},
    {"XingQiTian", "星期天"},
    {"AnJian1", "按键1"},
    {"AnJian2", "按键2"},
    {"AnJian3", "按键3"},
    {"YuYanSheZhi", "语言设置"},
    {"TianQi_QingJianDuoYun", "晴间多云"},
    {"TianQi_DaBuDuoYun", "大部多云"},
    {"TianQi_LeiZhenYu", "雷阵雨"},
    {"TianQi_LeiZhenYuBanYouBingBao", "雷阵雨伴有冰雹"},
    {"TianQi_ZhenXue", "阵雪"},
    {"TianQi_ShaChenBao", "沙尘暴"},
    {"TianQi_Feng", "风"},
    {"TianQi_DaFeng", "大风"},
    {"TianQi_JuFeng", "飓风"},
    {"TianQi_ReDaiFengBao", "热带风暴"},
    {"TianQi_LongJuanFeng", "龙卷风"},
    {"TianQi_Leng", "冷"},
    {"TianQi_Re", "热"},
    {"TianQi_WeiZhi", "未知"},
    {"TianQi_Qing", "晴"},
    {"TianQi_DuoYun", "多云"},
    {"TianQi_Yin", "阴"},
    {"TianQi_ZhenYu", "阵雨"},
    {"TianQi_XiaoYu", "小雨"},
    {"TianQi_ZhongYu", "中雨"},
    {"TianQi_DaYu", "大雨"},
    {"TianQi_BaoYu", "暴雨"},
    {"TianQi_DaBaoYu", "大暴雨"},
    {"TianQi_TeDaBaoYu", "特大暴雨"},
    {"TianQi_DongYu", "冻雨"},
    {"TianQi_YuJiaXue", "雨夹雪"},
    {"TianQi_XiaoXue", "小雪"},
    {"TianQi_ZhongXue", "中雪"},
    {"TianQi_DaXue", "大雪"},
    {"TianQi_BaoXue", "暴雪"},
    {"TianQi_FuChen", "浮尘"},
    {"TianQi_YangSha", "扬沙"},
    {"TianQi_QiangShaChenBao", "强沙尘暴"},
    {"TianQi_Wu", "雾"},
    {"TianQi_Mai", "霾"},
    {"diandong", "点动"},
    {"DangQianMeiYouSheBei", "当前没有设备，请到App中添加设备"},
    {"DaKaiDingShiXiPing", "打开定时息屏"},
    {"GuanBiDingShiXiPing", "关闭定时息屏"},
    {"DaKai_Open", "打开"},
    {"GuanBi_Close", "关闭"},
    {"QingJing1", "情景1"},
    {"QingJing2", "情景2"},
    {"QingJing3", "情景3"},
    {"QingJing4", "情景4"},
    {"QingJing5", "情景5"},
    {"QingJing6", "情景6"},
    {"GuJianGengXinZhong", "固件更新中..."},
    {"ZhengZaiShengJi", "正在升级请勿断电"},
    {"NeiCunFenPeiShiBai", "内存分配失败"},
    {"GuJianXiaZaiShiBai", "固件下载失败"},
    {"GuJianJieXiShiBai", "固件解析失败"},
    {"ZhengZaiAnZhuangGuJian", "正在安装固件..."},
    {"GuJianAnZhuangChengGong", "固件安装成功, 重启中..."},
    {"GuJianYanZhengShiBai", "固件验证失败"},
    {"XiaXaiJinDu", "下载进度: %d%%"},
    {"ShuiMianMoShi", "睡眠模式"},
    {"GanYingKaiGuan", "感应开关"},
    {"WuRaoMoShi", "勿扰模式"},
    {NULL, NULL} // End mark
};



static uint8_t zh_cn_plural_fn(int32_t num)
{



    return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
    .locale_name = "zh-cn",
    .singulars = zh_cn_singulars,

    .locale_plural_fn = zh_cn_plural_fn
};

const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
    &en_lang,
    &zh_cn_lang,
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
