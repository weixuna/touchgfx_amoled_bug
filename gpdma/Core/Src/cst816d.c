#include "cst816d.h"
#include <stdio.h>
// 外部声明
extern I2C_HandleTypeDef hi2c1;

// 读取CST816D寄存器
HAL_StatusTypeDef CST816D_ReadReg(uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, (CST816D_ADDR << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 100);
}

// 写入CST816D寄存器
HAL_StatusTypeDef CST816D_WriteReg(uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    return HAL_I2C_Mem_Write(&hi2c1, (CST816D_ADDR << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 100);
}

// 复位并初始化CST816D
uint8_t CST816D_Init(void)
{
    uint8_t temp_data;

    // 硬件复位CST816D
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); // RST引脚拉低
    HAL_Delay(20);                                         // 延时20ms（增加复位时间）
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);   // RST引脚拉高
    HAL_Delay(100);                                        // 延时100ms等待芯片稳定启动

    // 关闭自动休眠，确保持续工作
    temp_data = 0x01; // 禁用自动休眠
    CST816D_WriteReg(CST816D_REG_DIS_AUTO_SLEEP, &temp_data, 1);

    // 重新设置扫描周期 - 适合双击检测的更快扫描
    temp_data = 0; // 扫描周期设为最小值(0)，最高速
    CST816D_WriteReg(CST816D_REG_NOR_SCAN, &temp_data, 1);

    // 设置中断脉冲宽度
    temp_data = 5; // 更小的脉冲宽度，提高响应速度
    CST816D_WriteReg(CST816D_REG_IRQ_PULSE, &temp_data, 1);

    // 配置中断控制 - 启用触摸和所有变化检测
    temp_data = EnTouch | EnChange | EnMotion;
    CST816D_WriteReg(CST816D_REG_IRQ_CTL, &temp_data, 1);

    // 设置长按时间(500ms)
    temp_data = 10;
    CST816D_WriteReg(CST816D_REG_LONG_PRESS, &temp_data, 1);

    // 设置动作识别掩码 - 确保双击能被检测
    temp_data = 0x07; // 启用滑动和双击 (0x01+0x02+0x03)
    CST816D_WriteReg(CST816D_REG_MOTION_MASK, &temp_data, 1);

    // 配置动作角度 - 更宽松的滑动手势检测
    temp_data = 60;
    CST816D_WriteReg(CST816D_REG_MOTION_ANGLE, &temp_data, 1);

    return 1; // 初始化成功
}

// 获取触摸点数据 - 优化速度版本
HAL_StatusTypeDef CST816D_GetTouchData(CST816D_TouchData *touch_data)
{
    uint8_t data[7] = {0};

    // 设置初始值
    touch_data->gesture = GESTURE_NONE;
    touch_data->finger_num = 0;
    touch_data->x = 0;
    touch_data->y = 0;

    // 直接读取所需数据，减少一个字节的传输
    if (CST816D_ReadReg(CST816D_REG_GESTURE, data, 7) != HAL_OK)
    {
        return HAL_ERROR;
    }

    // 解析数据 - 简化处理逻辑
    touch_data->gesture = data[0];
    touch_data->finger_num = data[1];

    // X坐标位于寄存器2-3
    touch_data->x = ((uint16_t)(data[2] & 0x0F) << 8) | data[3];
    // Y坐标位于寄存器4-5
    touch_data->y = ((uint16_t)(data[4] & 0x0F) << 8) | data[5];

    return HAL_OK;
}

// 检测触摸(通过INT引脚) - 优化速度版本
uint8_t CST816D_IsTouched(void)
{
    // 直接返回INT引脚状态，移除2ms延时
    return (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET);
}

// 进入深度休眠模式
HAL_StatusTypeDef CST816D_EnterDeepSleep(void)
{
    uint8_t cmd = 0x03; // 深度休眠模式命令
    return CST816D_WriteReg(CST816D_REG_DEEP_SLEEP, &cmd, 1);
}

// 禁用/启用自动休眠
HAL_StatusTypeDef CST816D_SetAutoSleep(uint8_t enable)
{
    uint8_t cmd = enable ? 0x00 : 0x01; // 0x01禁用自动休眠，0x00启用
    return CST816D_WriteReg(CST816D_REG_DIS_AUTO_SLEEP, &cmd, 1);
}

// 设置中断脉冲宽度
HAL_StatusTypeDef CST816D_SetIrqPulseWidth(uint8_t width)
{
    return CST816D_WriteReg(CST816D_REG_IRQ_PULSE, &width, 1);
}

// 设置动作识别掩码 (使能/禁用特定手势)
HAL_StatusTypeDef CST816D_SetMotionMask(uint8_t mask)
{
    return CST816D_WriteReg(CST816D_REG_MOTION_MASK, &mask, 1);
}

// 设置滑动角度配置
HAL_StatusTypeDef CST816D_SetMotionAngle(uint8_t angle)
{
    return CST816D_WriteReg(CST816D_REG_MOTION_ANGLE, &angle, 1);
}

// 配置连续动作识别
HAL_StatusTypeDef CST816D_ConfigureContinuousMotion(uint8_t enable_slide_lr, uint8_t enable_slide_ud, uint8_t enable_dclick)
{
    uint8_t motion_mask = 0x00;

    if (enable_slide_lr)
        motion_mask |= EnConLR;

    if (enable_slide_ud)
        motion_mask |= EnConUD;

    if (enable_dclick)
        motion_mask |= EnDClick;

    return CST816D_SetMotionMask(motion_mask);
}

// 设置中断控制寄存器
HAL_StatusTypeDef CST816D_SetIrqCtl(uint8_t irq_ctl)
{
    return CST816D_WriteReg(CST816D_REG_IRQ_CTL, &irq_ctl, 1);
}