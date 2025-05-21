#ifndef __CST816D_H
#define __CST816D_H
#include "main.h"

#ifdef __cplusplus
extern "C"
{
#endif

// CST816D I2C地址
#define CST816D_ADDR 0x15

// CST816D寄存器地址
#define CST816D_REG_GESTURE 0x01    // 手势寄存器
#define CST816D_REG_FINGER_NUM 0x02 // 手指数量寄存器
#define CST816D_REG_XPOS_H 0x03     // X坐标高4位
#define CST816D_REG_XPOS_L 0x04     // X坐标低8位
#define CST816D_REG_YPOS_H 0x05     // Y坐标高4位
#define CST816D_REG_YPOS_L 0x06     // Y坐标低8位
#define CST816D_REG_XY_POS 0x07     // 触摸XY位置
#define CST816D_REG_MISC 0x08       // 杂项

#define CST816D_REG_CHIP_ID 0xA7    // 芯片ID寄存器
#define CST816D_REG_PROJECT_ID 0xA8 // 项目ID
#define CST816D_REG_FW_VERSION 0xA9 // 固件版本

#define CST816D_REG_DEEP_SLEEP 0xE5   // 深度休眠
#define CST816D_REG_MOTION_MASK 0xEC  // 动作掩码
#define CST816D_REG_IRQ_PULSE 0xED    // 中断脉冲宽度
#define CST816D_REG_NOR_SCAN 0xEE     // 正常扫描周期
#define CST816D_REG_MOTION_ANGLE 0xEF // 动作滑动角度

#define CST816D_REG_AUTO_SLEEP 0xF9     // 自动休眠时间
#define CST816D_REG_IRQ_CTL 0xFA        // 中断控制
#define CST816D_REG_AUTO_RESET 0xFB     // 自动复位
#define CST816D_REG_LONG_PRESS 0xFC     // 长按时间设置
#define CST816D_REG_IO_CTL 0xFD         // IO控制
#define CST816D_REG_DIS_AUTO_SLEEP 0xFE // 禁用自动休眠

// 手势值定义
#define CST816D_GESTURE_NONE 0x00
#define CST816D_GESTURE_SLIDE_UP 0x01
#define CST816D_GESTURE_SLIDE_DOWN 0x02
#define CST816D_GESTURE_SLIDE_LEFT 0x03
#define CST816D_GESTURE_SLIDE_RIGHT 0x04
#define CST816D_GESTURE_CLICK 0x05
#define CST816D_GESTURE_DOUBLE_CLICK 0x0B
#define CST816D_GESTURE_LONG_PRESS 0x0C

    // 手势定义
    typedef enum
    {
        GESTURE_NONE = 0x00,
        GESTURE_SLIDE_UP = 0x01,
        GESTURE_SLIDE_DOWN = 0x02,
        GESTURE_SLIDE_LEFT = 0x03,
        GESTURE_SLIDE_RIGHT = 0x04,
        GESTURE_SINGLE_CLICK = 0x05,
        GESTURE_DOUBLE_CLICK = 0x0B,
        GESTURE_LONG_PRESS = 0x0C
    } CST816D_Gesture_t;

    // 触摸数据结构体
    typedef struct
    {
        uint8_t gesture;    // 手势类型
        uint8_t finger_num; // 手指数量
        uint16_t x;         // X坐标 (12位分辨率)
        uint16_t y;         // Y坐标 (12位分辨率)
    } CST816D_TouchData;

    /* 连续动作配置选项 */
    typedef enum
    {
        M_DISABLE = 0x00,   // 不需要任何连续动作
        EnConLR = 0x01,     // 左右滑动
        EnConUD = 0x02,     // 上下滑动
        EnDClick = 0x03,    // 双击
        M_ALLENABLE = 0x07, // 启用所有连续动作配置 (0x01+0x02+0x03)
    } MotionMask_TypeDef;

    /* 中断控制寄存器位定义 */
    typedef enum
    {
        OnceWLP = 0x00,  // 单次脉冲发射
        EnMotion = 0x10, // 运动变化
        EnChange = 0x20, // 检测某些特定变化
        EnTouch = 0x40,  // 触摸事件
        EnTest = 0x80,   // 检测中断是否正常
    } IrqCtl_TypeDef;

    // 函数声明
    uint8_t CST816D_Init(void);
    HAL_StatusTypeDef CST816D_ReadReg(uint8_t reg_addr, uint8_t *data, uint16_t len);
    HAL_StatusTypeDef CST816D_WriteReg(uint8_t reg_addr, uint8_t *data, uint16_t len);
    HAL_StatusTypeDef CST816D_EnterDeepSleep(void);
    HAL_StatusTypeDef CST816D_SetAutoSleep(uint8_t enable);
    HAL_StatusTypeDef CST816D_GetTouchData(CST816D_TouchData *touch_data);
    uint8_t CST816D_IsTouched(void);

    HAL_StatusTypeDef CST816D_SetIrqPulseWidth(uint8_t width);
    HAL_StatusTypeDef CST816D_SetMotionMask(uint8_t mask);
    HAL_StatusTypeDef CST816D_SetMotionAngle(uint8_t angle);
    HAL_StatusTypeDef CST816D_ConfigureContinuousMotion(uint8_t enable_slide_lr, uint8_t enable_slide_ud, uint8_t enable_dclick);
    HAL_StatusTypeDef CST816D_SetIrqCtl(uint8_t irq_ctl);

#ifdef __cplusplus
}
#endif

#endif