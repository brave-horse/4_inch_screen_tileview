#include <stdio.h>
#include "app_config.h"
#include "system/task.h"
#include "os/os_api.h"
#include "HWDataAccess.h"
#include "hw_cloud_task.h"

#define TASK_NAME   "hw_cloud_task"
#define QUEUE_SIZE  128

static OS_QUEUE g_queue;
static void   *g_queue_buf;

static void handle_msg(HW_Msg *msg)
{
    switch (msg->type) {

    case HW_MSG_LIGHT_CT_SWITCH:
        HWInterface.LightCT.SetOnOff(msg->on);
        HWInterface.LightCT.Apply();
        break;

    case HW_MSG_LIGHT_CT_BRI:
        HWInterface.LightCT.SetBrightness(msg->val);
        HWInterface.LightCT.Apply();
        break;

    case HW_MSG_LIGHT_CT_CT:
        HWInterface.LightCT.SetColorTemp(msg->val);
        HWInterface.LightCT.Apply();
        break;

    case HW_MSG_LIGHT_LED_SWITCH:
        HWInterface.LEDStrip.SetOnOff(msg->on);
        break;

    case HW_MSG_LIGHT_MAG_SWITCH:
        HWInterface.MagLight.SetOnOff(msg->on);
        break;

    case HW_MSG_LIGHT_RGB_SWITCH:
        HWInterface.RGBLight.SetOnOff(msg->on);
        break;

    case HW_MSG_LIGHT_RGB_COLOR:
        break;

    case HW_MSG_CURTAIN_SWITCH:
        HWInterface.Curtain.SetOnOff(msg->idx, msg->on);
        HWInterface.Curtain.Apply(msg->idx);
        break;

    case HW_MSG_CURTAIN_POS:
        HWInterface.Curtain.SetPos(msg->idx, msg->val);
        HWInterface.Curtain.Apply(msg->idx);
        break;

    case HW_MSG_FANLIGHT_POWER:
        HWInterface.FanAndLight.SetPower(msg->on);
        HWInterface.FanAndLight.Apply();
        break;

    case HW_MSG_FANLIGHT_FAN:
        HWInterface.FanAndLight.SetFan(msg->on);
        HWInterface.FanAndLight.SetSpeed((uint8_t)msg->val);
        HWInterface.FanAndLight.Apply();
        break;

    case HW_MSG_FANLIGHT_SPEED:
        HWInterface.FanAndLight.SetSpeed((uint8_t)msg->val);
        HWInterface.FanAndLight.Apply();
        break;

    case HW_MSG_FANLIGHT_LIGHT:
        HWInterface.FanAndLight.SetLight(msg->on);
        HWInterface.FanAndLight.Apply();
        break;

    case HW_MSG_CLOUD_CMD:
        break;

    default:
        break;
    }
}

static void hw_cloud_task(void *parm)
{
    (void)parm;

    while (1) {
        HW_Msg msg;
        if (os_q_pend(&g_queue, 0, &msg) == 0)
            handle_msg(&msg);
    }
}

int hw_cloud_task_create(void)
{
    g_queue_buf = os_q_malloc();
    if (!g_queue_buf) {
        puts("[hw_cloud] os_q_malloc fail\n");
        return -1;
    }
    int ret = os_q_create(&g_queue, QUEUE_SIZE);
    if (ret) {
        puts("[hw_cloud] os_q_create fail\n");
        return ret;
    }
    return task_create(hw_cloud_task, NULL, TASK_NAME);
}

void hw_cloud_post(HW_Msg *msg)
{
    if (msg && msg->type > HW_MSG_NONE && msg->type < HW_MSG_COUNT)
        os_q_post(&g_queue, msg);
}
