/*
 * JD9261T 触显一体屏的触摸驱动(杰理 tp_driver 框架版)。
 * 协议依据厂商 NXP 参考驱动 jadard_jd9261t.c/.h:
 *   坐标在固定 6 字节子地址 0xF32001112003 处, 读 13 字节(3头 + 每点5字节, 取2点)。
 *   包格式: buf[0]=触摸点数 buf[1]=保留 buf[2]=手势 buf[3..]=点0{XH XL YH YL W} buf[8..]=点1
 * 框架结构仿 cst3240.c。
 */
#include "lcd_config.h"
#include "tp_driver.h"
#include "asm/exti.h"
#include "device/gpio.h"
#include "perf_counter.h"
#include "iic.h"

#if TCFG_TP_JD9261T_ENABLE

#define LOG_TAG_CONST       TP
#define LOG_TAG             "[TP]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DEBUG_ENABLE
#include "debug.h"
#undef  _LOG_TAG
#define _LOG_TAG "[TP]JD9261T>"


/* ======================== 配置 ======================== */

/* 触摸调试 log 开关: 0=关(默认), 1=开(打印 init/raw/PRESS 坐标等)。调触摸时改 1。 */
#define JD9261T_DBG  0
#if JD9261T_DBG
#define JD_LOG(...)  printf(__VA_ARGS__)
#else
#define JD_LOG(...)  do {} while (0)
#endif

#define JD9261T_READ_XY_MODE     0     // 取坐标模式 0:定时轮询 1:中断。本芯片 INT 疑似心跳, 默认轮询
#define JD9261T_POLLING_XY_TIME  30    // 轮询周期(ms)
#define JD9261T_INT_EDGE         EDGE_NEGATIVE

/* I2C 8 位地址: 7 位 0x68 << 1 = 0xD0(写), 0xD1(读) */
#define JD9261T_ADDR             0xD0

/* 坐标包: 3 头字节 + 每点 5 字节, 取 2 点 = 13(与厂商参考一致) */
#define JD9261T_MAX_POINTS       2
#define JD9261T_COORD_LEN        (3 + JD9261T_MAX_POINTS * 5)
#define JD9261T_FINGER_OFFSET    0     // 触摸点数在包里的偏移
#define JD9261T_POINT0_OFFSET    3     // 点0坐标起始偏移


/* ======================== 模块变量 ======================== */

static void (*tp_drdy_sem_post_func)(void);
static void *iic;
static volatile int jd9261t_int_id = -1;
static u16 jd9261t_timer_id = 0;

/* 坐标寄存器固定 6 字节子地址(厂商 JD9261T_RT_TOUCH_DATA_SUBADDR = 0xF32001112003) */
static const u8 jd9261t_coord_subaddr[6] = {0xF3, 0x20, 0x01, 0x11, 0x20, 0x03};


/* ======================== I2C 读坐标 ========================
 * 时序: START [写0xD0] 6字节子地址 -重复START- [读0xD1] 收 len 字节 STOP */
static int jd9261t_read_coord(u8 *buf, u8 len)
{
    int ret = 0;
    int idx; // idx index

    dev_ioctl(iic, IOCTL_IIC_START, 0);

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, JD9261T_ADDR)) {
        ret = -EIO;
        goto exit;
    }
    for (idx = 0; idx < 6; idx++) {
        if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, (u32)jd9261t_coord_subaddr[idx])) {
            ret = -EIO;
            goto exit;
        }
    }

    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, JD9261T_ADDR | 0x01)) {
        ret = -EIO;
        goto exit;
    }
    for (idx = 0; idx < (len - 1); idx++) {
        if (dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_ACK, (u32)(buf + idx))) {
            ret = -EIO;
            goto exit;
        }
    }
    if (dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (u32)(buf + idx))) {
        ret = -EIO;
        goto exit;
    }

exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}


#if JD9261T_DBG
/* 诊断用: 通用寄存器读(4字节地址 + 2字节长度框架), 读芯片ID确认 I2C 通路。仅调试用, DBG=0 不编译。 */
static int jd_reg_read(u32 addr, u8 *buf, u16 len)
{
    int ret = 0;
    int idx; // idx index
    u8 head[6];

    head[0] = (u8)((addr >> 24) & 0xFF);
    head[1] = (u8)((addr >> 16) & 0xFF);
    head[2] = (u8)((addr >> 8)  & 0xFF);
    head[3] = (u8)((addr >> 0)  & 0xFF);
    head[4] = (u8)((len >> 8)   & 0xFF);
    head[5] = (u8)((len >> 0)   & 0xFF);

    dev_ioctl(iic, IOCTL_IIC_START, 0);
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, JD9261T_ADDR)) { ret = -EIO; goto exit; }
    for (idx = 0; idx < 6; idx++) {
        if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE, (u32)head[idx])) { ret = -EIO; goto exit; }
    }
    if (dev_ioctl(iic, IOCTL_IIC_TX_BYTE_WITH_START_BIT, JD9261T_ADDR | 0x01)) { ret = -EIO; goto exit; }
    for (idx = 0; idx < (len - 1); idx++) {
        if (dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_ACK, (u32)(buf + idx))) { ret = -EIO; goto exit; }
    }
    if (dev_ioctl(iic, IOCTL_IIC_RX_BYTE_WITH_STOP_BIT, (u32)(buf + idx))) { ret = -EIO; goto exit; }
exit:
    dev_ioctl(iic, IOCTL_IIC_STOP, 0);
    return ret;
}
#endif /* JD9261T_DBG */


/* ======================== 取坐标 ======================== */

static void jd9261t_get_xy(tp_info_t *data)
{
    u8 buf[JD9261T_COORD_LEN];
    u8 finger;
    const u8 *point0; // 点0坐标区指针
    static tp_press_status_t last_status = TP_STATUS_RELEASE;
    static u32 dbg_cnt; // 诊断: 节流打印计数

    data->status = TP_STATUS_NULL;

    if (jd9261t_read_coord(buf, JD9261T_COORD_LEN)) {
        if ((dbg_cnt++ & 0x3f) == 0) JD_LOG("[jd9261t] read FAIL\n"); // 诊断
        return;
    }

#if JD9261T_DBG
    if ((dbg_cnt++ & 0x3f) == 0) {                                    // 诊断: ~每64次(约2s)打ID+原始包(此时FW已起)
        u8 idbuf[2] = {0};
        jd_reg_read(0x40008076UL, idbuf, 2);
        JD_LOG("[jd9261t] id=0x%02x%02x raw %02x %02x %02x %02x %02x %02x %02x %02x\n",
               idbuf[1], idbuf[0], buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
    }
#endif

    finger = buf[JD9261T_FINGER_OFFSET];
    /* 无触摸(0)或异常(含读到全0xFF的0xFF): 仅在上次按下时报抬起 */
    if (finger == 0 || finger > JD9261T_MAX_POINTS) {
        data->status = (last_status == TP_STATUS_PRESS) ? TP_STATUS_RELEASE : TP_STATUS_NULL;
        last_status = TP_STATUS_RELEASE;
        return;
    }

    point0 = buf + JD9261T_POINT0_OFFSET;            // XH XL YH YL W
    data->x = (u16)((point0[0] << 8) | point0[1]);
    data->y = (u16)((point0[2] << 8) | point0[3]);
    data->status = TP_STATUS_PRESS;
    last_status = TP_STATUS_PRESS;
    JD_LOG("[jd9261t] PRESS f=%d x=%d y=%d\n", finger, data->x, data->y); // 诊断
}


/* ======================== 中断/轮询 ======================== */

static void jd9261t_interrupt(void *arg, u32 parm)
{
    tp_drdy_sem_post_func();
}

static int jd9261t_int_enable(const tp_platform_data_t *pd_data)
{
#if JD9261T_READ_XY_MODE
    if (jd9261t_int_id < 0) {
        jd9261t_int_id = exti_init(pd_data->int_pin, JD9261T_INT_EDGE, jd9261t_interrupt, NULL);
        if (jd9261t_int_id < 0) {
            jd9261t_int_id = -1;
            return -EINVAL;
        }
    }
#else
    if (jd9261t_timer_id == 0) {
        jd9261t_timer_id = sys_s_hi_timer_add(NULL, jd9261t_interrupt, JD9261T_POLLING_XY_TIME);
        if (jd9261t_timer_id == 0) {
            return -EINVAL;
        }
    }
#endif
    return 0;
}

static int jd9261t_int_disable(const tp_platform_data_t *pd_data)
{
#if JD9261T_READ_XY_MODE
    if (jd9261t_int_id >= 0) {
        exti_uninit(jd9261t_int_id);
        jd9261t_int_id = -1;
    }
#else
    if (jd9261t_timer_id > 0) {
        sys_s_hi_timer_del(jd9261t_timer_id);
        jd9261t_timer_id = 0;
    }
#endif
    return 0;
}


/* ======================== 复位 ========================
 * 触显共用复位脚, 只拉高释放、不打脉冲; 脉冲会重启芯片丢失显示 init code 配的触摸扫描参数。 */
static void jd9261t_reset(const tp_platform_data_t *pd_data)
{
    log_info(">>>>> reset");
    if (pd_data->rst_pin == -1) {
        return;
    }
    gpio_direction_output(pd_data->rst_pin, 1);
    os_time_dly(2);
}


/* ======================== 在线检测 ========================
 * 一体屏触摸常在, 不做 ID 校验(NXP 参考也无), 恒返回在线。 */
static int jd9261t_check_online(void)
{
    return 0;
}


/* ======================== init/deinit ======================== */

static int jd9261t_init(const tp_platform_data_t *pd_data, void (*post_func)(void))
{
    JD_LOG("[jd9261t] init enter, if=%s rst=%d int=%d\n",  // 诊断
           pd_data->interface, pd_data->rst_pin, pd_data->int_pin);

    iic = dev_open(pd_data->interface, NULL);
    if (!iic) {
        JD_LOG("[jd9261t] open iic(%s) FAIL\n", pd_data->interface); // 诊断
        return -EINVAL;
    }

#if JD9261T_DBG
    {   // 诊断: 读芯片ID确认 I2C 通路(老驱动测得 0x9062)
        u8 idbuf[2] = {0};
        if (jd_reg_read(0x40008076UL, idbuf, 2) == 0) {
            JD_LOG("[jd9261t] chip id = 0x%02x%02x (expect 9062)\n", idbuf[1], idbuf[0]);
        } else {
            JD_LOG("[jd9261t] chip id read FAIL (i2c bad?)\n");
        }
    }
#endif

    /* 复位脚拉高释放(不脉冲) */
    if (pd_data->rst_pin != -1) {
        gpio_direction_output(pd_data->rst_pin, 1);
        os_time_dly(2);
    }

    tp_drdy_sem_post_func = post_func;

    if (jd9261t_int_enable(pd_data)) {
        JD_LOG("[jd9261t] int/timer enable FAIL\n");  // 诊断
        dev_close(iic);
        iic = NULL;
        return -EINVAL;
    }

    JD_LOG("[jd9261t] init done (mode=%s)\n", JD9261T_READ_XY_MODE ? "int" : "poll"); // 诊断
    return 0;
}

static int jd9261t_deinit(const tp_platform_data_t *pd_data)
{
    log_info(">>>>> deinit");

    jd9261t_int_disable(pd_data);

    if (pd_data->rst_pin != -1) {
        gpio_set_mode(pd_data->rst_pin, GPIO_DEINIT);
    }
    if (pd_data->int_pin != -1) {
        gpio_set_mode(pd_data->int_pin, GPIO_DEINIT);
    }
    if (iic) {
        dev_close(iic);
        iic = NULL;
    }
    return 0;
}


/* ======================== 注册到框架 ======================== */

REGISTER_TP_DRIVER(jd9261t_driver) = {
    .ic_name            = "JD9261T",
    .init               = jd9261t_init,
    .get_xy_and_status  = jd9261t_get_xy,
    .check_online       = jd9261t_check_online,
    .deinit             = jd9261t_deinit,
    .reset              = jd9261t_reset,
    /* .sleep / .wakeup 暂未实现 */
};

#endif /* TCFG_TP_JD9261T_ENABLE */
