/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "pulldown.h"
#include "img.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    custom_img_set_src(ui->screen_img_1, "1111.png");
    lv_img_set_size_mode(ui->screen_img_1, LV_IMG_SIZE_MODE_REAL);

    custom_img_set_src(ui->screen_img_2, "1111.png");
    lv_img_set_size_mode(ui->screen_img_2, LV_IMG_SIZE_MODE_REAL);

    custom_img_set_src(ui->screen_img_3, "1111.png");
    lv_img_set_size_mode(ui->screen_img_3, LV_IMG_SIZE_MODE_REAL);


/*******************************安卓下拉初始化开始****************************/
    pulldown_init(ui);

}
