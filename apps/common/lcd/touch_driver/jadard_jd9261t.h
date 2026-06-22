/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _JADARD_JD9261T_H_
#define _JADARD_JD9261T_H_

#include "sys.h"

/*!
 * @addtogroup jd9261t_rt
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief JD9261T_RT I2C address. */
#define JD9261T_RT_I2C_ADDRESS        (0x68)

/*! @brief JD9261T_RT maximum number of simultaneously detected touches. */
#define JD9261T_RT_MAX_TOUCHES 		  (2U)

/*! @brief JD9261T_RT register address where touch data begin. */
#define JD9261T_RT_TOUCH_DATA_SUBADDR (0xF32001112003)

/*! @brief JD9261T_RT raw touch data length. */
#define JD9261T_RT_TOUCH_DATA_LEN 	  (3 + JD9261T_RT_MAX_TOUCHES*5)

/*! @brief LCD resolution */
#define TP_SCREEN_WIDTH               (480)
#define TP_SCREEN_HEIGHT              (960)

typedef enum _touch_event
{
    kTouch_Down     = 0, /*!< The state changed to touched. */
    kTouch_Up       = 1, /*!< The state changed to not touched. */
    kTouch_Contact  = 2, /*!< There is a continuous touch being detected. */
    kTouch_Reserved = 3  /*!< No touch information available. */
} touch_event_t;

typedef struct _touch_point
{
    touch_event_t TOUCH_EVENT; /*!< Indicates the state or event of the touch point. */
    uint8_t TOUCH_ID; /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X; /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y; /*!< Y coordinate of the touch point */
} touch_point_t;

typedef struct _jd9261t_rt_handle
{
    LPI2C_Type *base;
    lpi2c_master_transfer_t xfer;
    uint8_t touch_buf[JD9261T_RT_TOUCH_DATA_LEN];
} jd9261t_rt_handle_t;

extern status_t JD9261T_RT_Init(jd9261t_rt_handle_t *handle, LPI2C_Type *base);

extern status_t JD9261T_RT_Denit(jd9261t_rt_handle_t *handle);

extern status_t JD9261T_RT_GetSingleTouch(jd9261t_rt_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y);

extern status_t JD9261T_RT_GetMultiTouch(jd9261t_rt_handle_t *handle,
                                 int *touch_count,
                                 touch_point_t touch_array[JD9261T_RT_MAX_TOUCHES]);

#endif

