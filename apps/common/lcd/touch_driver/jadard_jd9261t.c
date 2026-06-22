/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "jadard_jd9261t.h"
#include "FreeRTOS.h"
#include "task.h"

uint16_t JD_TOUCH_X[JD9261T_RT_MAX_TOUCHES];
typedef struct _jd9261t_rt_touch_point
{
    uint8_t XH;
    uint8_t XL;
    uint8_t YH;
    uint8_t YL;
    uint8_t WEIGHT;
} jd9261t_rt_touch_point_t;

typedef struct _jd9261t_rt_touch_data
{
    uint8_t FINGER_NUMBER;
    uint8_t RESERVED;
    uint8_t GESTURE;
    jd9261t_rt_touch_point_t TOUCH[JD9261T_RT_MAX_TOUCHES];
} jd9261t_rt_touch_data_t;

#define TOUCH_POINT_GET_X(T)     (((T).XH << 8) | (T).XL)
#define TOUCH_POINT_GET_Y(T)     (((T).YH << 8) | (T).YL)

static void JD9261T_PORT_Init(void)
{
	gpio_pin_config_t config;
		
	/// IO功能设置
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28, 0); /// GPIO_AD_B1_12配置为ALT5,即GPIO1_IO28
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14, 0); /// GPIO_AD_B0_14配置为ALT5,即GPIO1_IO14
		
	/// 配置IO功能
	/// 低转换速度,关闭输出驱动,速度为100Mhz，关闭开路功能，使能pull/keepr
	/// 选择pull功能，上拉22K Ohm，关闭Hyst
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28, 0xF080);

	config.direction	 = kGPIO_DigitalInput; /// 输入
	config.interruptMode = kGPIO_NoIntmode;    /// 不使用中断功能
	config.outputLogic	 = 1;				   /// 默认高电平
	GPIO_PinInit(GPIO1, 28, &config);		   /// 初始化GPIO1_28 
	
	/// 配置IO引脚GPIO_AD_B0_14的功能
	/// 低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
	/// 选择keeper功能，下拉100K Ohm，关闭Hyst
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14, 0x10B0);

	config.direction	 = kGPIO_DigitalOutput; /// 输出
	config.interruptMode = kGPIO_NoIntmode; 	/// 不使用中断功能
	config.outputLogic	 = 0;					/// 默认低电平，TP复位
	GPIO_PinInit(GPIO1, 14, &config);			/// 初始化GPIO1_14
	/// 延时10ms
	vTaskDelay(10 / portTICK_RATE_MS);
	
	GPIO_PinWrite(GPIO1, 14, 1);
	/// 延时10ms
	vTaskDelay(10 / portTICK_RATE_MS);
}

static void JD9261T_PORT_DeInit(void)
{
	gpio_pin_config_t config;
		
	/// IO功能设置
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28, 0); /// GPIO_AD_B1_12配置为ALT5,即GPIO1_IO28
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14, 0); /// GPIO_AD_B0_14配置为ALT5,即GPIO1_IO14
		
	/// 配置IO功能
	/// 低转换速度,关闭输出驱动,速度为100Mhz，关闭开路功能，使能pull/keepr
	/// 选择pull功能，上拉22K Ohm，关闭Hyst
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28, 0xF080);

	config.direction	 = kGPIO_DigitalInput; /// 输入
	config.interruptMode = kGPIO_NoIntmode;    /// 不使用中断功能
	config.outputLogic	 = 1;				   /// 默认高电平
	GPIO_PinInit(GPIO1, 28, &config);		   /// 初始化GPIO1_28 
	
	/// 配置IO引脚GPIO_AD_B0_14的功能
	/// 低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
	/// 选择keeper功能，下拉100K Ohm，关闭Hyst
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14, 0x10B0);

	config.direction	 = kGPIO_DigitalOutput; /// 输出
	config.interruptMode = kGPIO_NoIntmode; 	/// 不使用中断功能
	config.outputLogic	 = 0;					/// 默认低电平，TP复位
	GPIO_PinInit(GPIO1, 14, &config);			/// 初始化GPIO1_14

	/// 延时10ms
	vTaskDelay(10 / portTICK_RATE_MS);
}

status_t JD9261T_RT_Init(jd9261t_rt_handle_t *handle, LPI2C_Type *base)
{
    lpi2c_master_transfer_t *xfer = &(handle->xfer);
    status_t status;

    assert(handle);
    assert(base);

    if (!handle || !base)
    {
        return kStatus_InvalidArgument;
    }

	JD9261T_PORT_Init();

    handle->base = base;

    /* clear transfer structure and buffer */
    memset(xfer, 0, sizeof(*xfer));
    memset(handle->touch_buf, 0, JD9261T_RT_TOUCH_DATA_LEN);
    memset(JD_TOUCH_X, 0xFF, 2*JD9261T_RT_MAX_TOUCHES);

    /* prepare transfer structure for reading touch data */
    xfer->slaveAddress   = JD9261T_RT_I2C_ADDRESS;
    xfer->direction      = kLPI2C_Read;
    xfer->subaddress     = JD9261T_RT_TOUCH_DATA_SUBADDR;
    xfer->subaddressSize = 6;
    xfer->data           = handle->touch_buf;
    xfer->dataSize       = JD9261T_RT_TOUCH_DATA_LEN;
    xfer->flags          = kLPI2C_TransferDefaultFlag;
    status = LPI2C_MasterTransferBlocking(handle->base, &handle->xfer);

    return status;
}

status_t JD9261T_RT_Denit(jd9261t_rt_handle_t *handle)
{
    assert(handle);

    if (!handle)
    {
        return kStatus_InvalidArgument;
    }

	JD9261T_PORT_DeInit();

    handle->base = NULL;
    return kStatus_Success;
}

status_t JD9261T_RT_ReadTouchData(jd9261t_rt_handle_t *handle)
{
    assert(handle);

    if (!handle)
    {
        return kStatus_InvalidArgument;
    }

    return LPI2C_MasterTransferBlocking(handle->base, &handle->xfer);
}

status_t JD9261T_RT_GetSingleTouch(jd9261t_rt_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y)
{
    status_t status;
    touch_event_t touch_event_local;
    int x, y;

    status = JD9261T_RT_ReadTouchData(handle);

    if (status == kStatus_Success)
    {
        jd9261t_rt_touch_data_t *touch_data = (jd9261t_rt_touch_data_t *)(void *)(handle->touch_buf);

        if (touch_event == NULL)
        {
            touch_event = &touch_event_local;
        }
        
        x = TOUCH_POINT_GET_X(touch_data->TOUCH[0]);
        y = TOUCH_POINT_GET_Y(touch_data->TOUCH[0]);

        if ((x >= 0 && x < TP_SCREEN_WIDTH) &&
            (y >= 0 && y < TP_SCREEN_HEIGHT))
        {
            if (JD_TOUCH_X[0] == 0xFFFF)
            {
                *touch_event = kTouch_Down;
            }
            else
            {
                *touch_event = kTouch_Contact;
            }
            JD_TOUCH_X[0] = x;
            if (touch_x)
            {
                *touch_x = x;
            }
            if (touch_y)
            {
                *touch_y = y;
            }
        }
        else
        {
            if (JD_TOUCH_X[0] == 0xFFFF)
            {
                *touch_event = kTouch_Reserved;
            }
            else
            {
                *touch_event = kTouch_Up;
            }
            JD_TOUCH_X[0] = 0xFFFF;
            if (touch_x)
            {
                *touch_x = 0xFFFF;
            }
            if (touch_y)
            {
                *touch_y = 0xFFFF;
            }
        }
    }

    return status;
}

status_t JD9261T_RT_GetMultiTouch(jd9261t_rt_handle_t *handle,
                                 int *touch_count,
                                 touch_point_t touch_array[JD9261T_RT_MAX_TOUCHES])
{
    status_t status;

    status = JD9261T_RT_ReadTouchData(handle);

    if (status == kStatus_Success)
    {
        jd9261t_rt_touch_data_t *touch_data = (jd9261t_rt_touch_data_t *)(void *)(handle->touch_buf);
        int i, x, y;

        /* Decode number of touches */
        if (touch_count)
        {
            if (touch_data->FINGER_NUMBER > JD9261T_RT_MAX_TOUCHES)
            {
                *touch_count = 0;
            }
            else
            {
                *touch_count = touch_data->FINGER_NUMBER;
            }
        }

        /* Decode valid touch points */
        for (i = 0; i < JD9261T_RT_MAX_TOUCHES; i++)
        {
            x = TOUCH_POINT_GET_X(touch_data->TOUCH[i]);
            y = TOUCH_POINT_GET_Y(touch_data->TOUCH[i]);
            touch_array[i].TOUCH_ID = i;

            if ((x >= 0 && x < TP_SCREEN_WIDTH) &&
                (y >= 0 && y < TP_SCREEN_HEIGHT))
            {
                if (JD_TOUCH_X[i] == 0xFFFF)
                {
                    touch_array[i].TOUCH_EVENT = kTouch_Down;
                }
                else
                {
                    touch_array[i].TOUCH_EVENT = kTouch_Contact;
                }
                JD_TOUCH_X[i] = x;
                touch_array[i].TOUCH_X = x;
                touch_array[i].TOUCH_Y = y;
            }
            else
            {
                if (JD_TOUCH_X[i] == 0xFFFF)
                {
                    touch_array[i].TOUCH_EVENT = kTouch_Reserved;
                }
                else
                {
                    touch_array[i].TOUCH_EVENT = kTouch_Up;
                }
                JD_TOUCH_X[i] = 0xFFFF;
                touch_array[i].TOUCH_X = 0xFFFF;
                touch_array[i].TOUCH_Y = 0xFFFF;
            }
        }
    }

    return status;
}

