#ifndef ICNA3306_H
#define ICNA3306_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm32u5xx_hal.h"

// 命令定义
#define CMD_NOP 0x00
#define CMD_RST 0x01
#define CMD_READ_ID 0x04
#define CMD_SLEEP_OUT 0x11
#define CMD_INVERSION_OFF 0x20
#define CMD_INVERSION_ON 0x21
#define CMD_ALL_PIXEL_OFF 0x22
#define CMD_ALL_PIXEL_ON 0x23
#define CMD_DISPLAY_OFF 0x28
#define CMD_DISPLAY_ON 0x29
#define CMD_COL_SET 0x2A
#define CMD_ROW_SET 0x2B
#define CMD_START_WRITE 0x2C
#define CMD_TE_OFF 0x34
#define CMD_TE_ON 0x35
#define CMD_IDLE_MODE_OFF 0x38
#define CMD_IDLE_MODE_ON 0x39
#define CMD_PIXEL_FORMAT 0x3A
#define CMD_WRITE_CONTINUE 0x3C
#define CMD_WRITE_TE_LINE 0x44
#define CMD_SET_BRIGHTNESS 0x51
#define CMD_WRITE_CTRL_DSP1 0x53
#define CMD_WRITE_CTRL_DPS2 0x55
#define CMD_SPI_MODE_CTRL 0xC4

// 函数声明
void ICNA3306_Init(void);
HAL_StatusTypeDef ICNA3306_WriteCmdParam(uint8_t cmd, size_t len, const uint8_t *params);
HAL_StatusTypeDef ICNA3306_WriteCmdData(uint8_t cmd, size_t len, const uint8_t *data);
void ICNA3306_DrawBuffer(int16_t x_start, int16_t y_start, int16_t width, int16_t height, const uint8_t *buf, size_t len);
void ICNA3306_DrawBlock(int x_start, int y_start, int width, int height, uint16_t colour);


#ifdef __cplusplus
}
#endif
#endif
