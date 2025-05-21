/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.25.0. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */
#include "cst816d.h"
#include <stdio.h>

#include <STM32TouchController.hpp>

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    CST816D_Init();
    uint8_t irq_setting = EnTouch | EnChange | EnMotion;
    CST816D_SetIrqCtl(irq_setting);
    CST816D_SetMotionMask(0x07);
    printf("cst816d init\n");
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
		static int32_t lastX = 0;
	    static int32_t lastY = 0;
	    static bool wasTouched = false;
	    static bool justReleased = false;  // 新增：跟踪触摸刚刚释放的状态

	    // 设置有效的屏幕尺寸范围
	    const int32_t MIN_X = 0;
	    const int32_t MAX_X = 239;  // 根据您的屏幕实际宽度-1
	    const int32_t MIN_Y = 0;
	    const int32_t MAX_Y = 295;  // 根据您的屏幕实际高度-1
	    const int32_t MIN_DELTA = 2; // 防抖动阈值

	    // 检查触摸状态
	    if (CST816D_IsTouched())
	    {
	        CST816D_TouchData touchData;

	        if (CST816D_GetTouchData(&touchData) == HAL_OK)
	        {
	            if (touchData.finger_num > 0)
	            {
	                // 获取坐标
	                int32_t newX = touchData.x;
	                int32_t newY = touchData.y;

	                // 确保坐标在有效范围内
	                if (newX < MIN_X) newX = MIN_X;
	                if (newX > MAX_X) newX = MAX_X;
	                if (newY < MIN_Y) newY = MIN_Y;
	                if (newY > MAX_Y) newY = MAX_Y;

	                // 简单的防抖动处理
	                bool significantChange = !wasTouched ||
	                                      abs(newX - lastX) > MIN_DELTA ||
	                                      abs(newY - lastY) > MIN_DELTA;

	                if (significantChange || !wasTouched)
	                {
	                    // 更新坐标
	                    x = newX;
	                    y = newY;
	                    lastX = x;
	                    lastY = y;
	                }
	                else
	                {
	                    // 使用上次的有效坐标
	                    x = lastX;
	                    y = lastY;
	                }

	                // 设置触摸状态
	                wasTouched = true;
	                justReleased = false;

	                // 偶尔打印日志，而不是每次都打印
	                static uint32_t logCounter = 0;
	                if (++logCounter % 100 == 0) {
	                    printf("Touch at: x=%ld, y=%ld\n", x, y);
	                }

	                return true;
	            }
	        }
	    }
	    else if (wasTouched)
	    {
	        // 触摸刚刚结束
	        if (!justReleased) {
	            // 发送最后一个触摸位置，让TouchGFX识别释放事件
	            x = lastX;
	            y = lastY;
	            justReleased = true;
	            wasTouched = false;

	            // 可选：记录触摸释放事件
	            // printf("Touch released at: x=%ld, y=%ld\n", x, y);

	            return true;  // 重要：返回true让TouchGFX知道这是释放事件
	        }
	        else {
	            // 已经处理过释放事件，恢复到未触摸状态
	            justReleased = false;
	        }
	    }

	    return false;  // 无触摸

}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
