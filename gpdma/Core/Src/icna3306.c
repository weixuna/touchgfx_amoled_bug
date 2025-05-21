#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "main.h"
#include "octospi.h"
#include "icna3306.h"
#include "stm32u5xx_hal.h"
#include <string.h>
#include "core_cm33.h"
#include "gpdma.h"
#include <stdio.h>

#define WIDTH 240
#define HEIGHT 296

extern OSPI_HandleTypeDef hospi1;
extern DMA_HandleTypeDef handle_GPDMA1_Channel13;

static void DMA_TxCpltCallback(DMA_HandleTypeDef *hdma);
static void DMA_TxErrorCallback(DMA_HandleTypeDef *hdma);

static volatile bool displayRefreshing = false;

/**
 * @brief Register DMA callbacks
 */
void GPDMA_Callback(void)
{
    HAL_DMA_RegisterCallback(&handle_GPDMA1_Channel13, HAL_DMA_XFER_CPLT_CB_ID, DMA_TxCpltCallback);
    HAL_DMA_RegisterCallback(&handle_GPDMA1_Channel13, HAL_DMA_XFER_ERROR_CB_ID, DMA_TxErrorCallback);
}

/**
 * @brief DMA transfer complete callback
 * @param hdma: DMA handle
 */
static void DMA_TxCpltCallback(DMA_HandleTypeDef *hdma)
{
    if (hdma == &handle_GPDMA1_Channel13)
    {
                __DSB(); // 添加内存屏障
        displayRefreshing = false;
    }
}

/**
 * @brief DMA transfer error callback
 * @param hdma: DMA handle
 */
static void DMA_TxErrorCallback(DMA_HandleTypeDef *hdma)
{
    displayRefreshing = false;
}

/**
 * @brief Configure DMA Linked-list Queue
 */
static HAL_StatusTypeDef GPDMA_Queue_Config(DMA_QListTypeDef *Queue, uint8_t node_cnt, uint8_t *src, uint8_t *dst, uint32_t data_size)
{
    static DMA_NodeTypeDef Nodes[(((WIDTH * HEIGHT * 2) / ((64 * 1024) - 2)) + 1)];
    HAL_StatusTypeDef ret = HAL_OK;
    /* DMA node configuration declaration */
    DMA_NodeConfTypeDef pNodeConfig;
    uint8_t i;

    /* Set node configuration ################################################*/
    pNodeConfig.NodeType = DMA_GPDMA_2D_NODE;
    pNodeConfig.Init.Mode = DMA_NORMAL;
    pNodeConfig.Init.Request = DMA_REQUEST_SW;
    pNodeConfig.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    pNodeConfig.Init.Direction = DMA_MEMORY_TO_PERIPH;
    pNodeConfig.Init.SrcInc = DMA_SINC_INCREMENTED;
    pNodeConfig.Init.DestInc = DMA_DINC_FIXED;
    pNodeConfig.Init.SrcDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    pNodeConfig.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
    pNodeConfig.Init.SrcBurstLength = 1;
    pNodeConfig.Init.DestBurstLength = 1;
    pNodeConfig.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT0;
    pNodeConfig.Init.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;
    pNodeConfig.RepeatBlockConfig.RepeatCount = 1;
    pNodeConfig.RepeatBlockConfig.SrcAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.DestAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.BlkSrcAddrOffset = 0;
    pNodeConfig.RepeatBlockConfig.BlkDestAddrOffset = 0;
    pNodeConfig.TriggerConfig.TriggerPolarity = DMA_TRIG_POLARITY_MASKED;
    pNodeConfig.DataHandlingConfig.DataExchange = DMA_EXCHANGE_NONE;
    pNodeConfig.DataHandlingConfig.DataAlignment = DMA_DATA_RIGHTALIGN_ZEROPADDED;
    pNodeConfig.SrcAddress = (uint32_t)src;
    pNodeConfig.DstAddress = (uint32_t)dst;
    if (node_cnt > 1)
    {
        pNodeConfig.DataSize = ((64 * 1024) - 2);
    }
    else
    {
        pNodeConfig.DataSize = data_size;
    }

    for (i = 0; ((ret == HAL_OK) && (i < node_cnt)); i++)
    {
        if (i == 0)
        {
            /* Reset The Queue */
            ret = HAL_DMAEx_List_ResetQ(Queue);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Build Node first Node */
            ret = HAL_DMAEx_List_BuildNode(&pNodeConfig, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Insert Node to Queue */
            ret = HAL_DMAEx_List_InsertNode_Head(Queue, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
        }
        else
        {
            /* Adjust size of last node */
            if ((node_cnt > 1) && (i == (node_cnt - 1)))
            {
                pNodeConfig.DataSize = (data_size - (i * ((64 * 1024) - 2)));
            }
            /* Build Node Node */
            ret = HAL_DMAEx_List_BuildNode(&pNodeConfig, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
            /* Insert Node to Queue */
            ret = HAL_DMAEx_List_InsertNode_Tail(Queue, &Nodes[i]);
            if (ret != HAL_OK)
            {
                return ret;
            }
        }
        pNodeConfig.SrcAddress += ((64 * 1024) - 2);
    }

    return ret;
}

/**
 * @brief Send data to ICNA3306 using DMA
 */
static HAL_StatusTypeDef ICNA3306_SendDataDMA(uint8_t *pData, uint32_t Length)
{
    static DMA_QListTypeDef Queue;
    uint32_t len = Length;
    uint8_t node_cnt = (len / ((64 * 1024) - 2));
    if (len % ((64 * 1024) - 2))
    {
        node_cnt++;
    }

    if ((handle_GPDMA1_Channel13.Mode & DMA_LINKEDLIST) == DMA_LINKEDLIST)
    {
        /* Link created queue to DMA channel */
        if (GPDMA_Queue_Config(&Queue, node_cnt, pData, (uint8_t *)&(hospi1.Instance->DR), len) != HAL_OK)
        {
            displayRefreshing = false;
            return HAL_ERROR;
        }

        /* Link created queue to DMA channel */
        if (HAL_DMAEx_List_LinkQ(&handle_GPDMA1_Channel13, &Queue) != HAL_OK)
        {
            displayRefreshing = false;
            return HAL_ERROR;
        }

        /* Enable All the DMA interrupts */
        if (HAL_DMAEx_List_Start_IT(&handle_GPDMA1_Channel13) != HAL_OK)
        {
            displayRefreshing = false;
            return HAL_ERROR;
        }
    }
    else
    {
        if (node_cnt > 1)
        {
            displayRefreshing = false;
            return HAL_ERROR;
        }

        switch (handle_GPDMA1_Channel13.Init.DestDataWidth)
        {
        case DMA_DEST_DATAWIDTH_WORD:
            len = (Length / 4);
            break;
        case DMA_DEST_DATAWIDTH_BYTE:
            len = Length;
            break;
        default:
        case DMA_DEST_DATAWIDTH_HALFWORD:
            len = (Length / 2);
            break;
        }

        if (HAL_DMA_Start_IT(&handle_GPDMA1_Channel13, (uint32_t)pData, (uint32_t)&(hospi1.Instance->DR), len) != HAL_OK)
        {
            displayRefreshing = false;
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


HAL_StatusTypeDef ICNA3306_WriteCmdParam(uint8_t cmd, size_t len, const uint8_t *params)
{
    OSPI_RegularCmdTypeDef sCommand = {0};

    sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    sCommand.Instruction = 0x02;
    sCommand.Address = ((uint32_t)cmd) << 8;

    sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
    sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
    sCommand.DummyCycles = 0;
    sCommand.DataMode = len > 0 ? HAL_OSPI_DATA_1_LINE : HAL_OSPI_DATA_NONE;
    sCommand.NbData = len;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (len > 0)
    {
        if (HAL_OSPI_Transmit(&hospi1, (uint8_t *)params, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}


HAL_StatusTypeDef ICNA3306_WriteCmdData(uint8_t cmd, size_t len, const uint8_t *data)
{
    HAL_StatusTypeDef status;
    OSPI_RegularCmdTypeDef sCommand = {0};

    if (len == 0 || data == NULL)
        return HAL_ERROR;

    HAL_OSPI_Abort(&hospi1);

    sCommand.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Instruction = 0x32;

    sCommand.Address = (cmd << 8);
    sCommand.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    sCommand.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
    sCommand.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = HAL_OSPI_DATA_4_LINES;
    sCommand.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    sCommand.DummyCycles = 0;
    sCommand.DQSMode = HAL_OSPI_DQS_DISABLE;
    sCommand.NbData = len;

    sCommand.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

    status = HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK)
    {
        return status;
    }
    printf("Transfer length: %d\r\n", len);
    if (len > 1024)
    {
        HAL_OSPI_Abort(&hospi1);
        __DSB();

        displayRefreshing = true;
        status = ICNA3306_SendDataDMA((uint8_t *)data, len);
        if (status != HAL_OK)
        {
            displayRefreshing = false;
            return status;
        }
        uint32_t timeout = HAL_GetTick() + 1000;
        while (displayRefreshing)
        {
            if (HAL_GetTick() >= timeout)
            {
                HAL_DMA_Abort_IT(&handle_GPDMA1_Channel13);
                displayRefreshing = false;
                return HAL_TIMEOUT;
            }
        }
    }

    return HAL_OK;
}


void ICNA3306_DrawBuffer(int16_t x_start, int16_t y_start, int16_t width, int16_t height, const uint8_t *buf, size_t len)
{
    uint8_t params[5] = {0};
    int16_t x_end = x_start + width - 1;
    int16_t y_end = y_start + height - 1;

    // （0x2A）
    params[0] = x_start >> 8;
    params[1] = x_start & 0xFF;
    params[2] = x_end >> 8;
    params[3] = x_end & 0xFF;
    ICNA3306_WriteCmdParam(CMD_COL_SET, 4, params);

    // （0x2B）
    params[0] = y_start >> 8;
    params[1] = y_start & 0xFF;
    params[2] = y_end >> 8;
    params[3] = y_end & 0xFF;
    ICNA3306_WriteCmdParam(CMD_ROW_SET, 4, params);

    // （0x2C）
    ICNA3306_WriteCmdData(CMD_START_WRITE, len, buf);
}


void ICNA3306_Init(void)
{
    uint8_t parameter[14];
    memset(parameter, 0, sizeof(parameter));

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_Delay(120);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(120);

    GPDMA_Callback();

    printf("OSPI DR Addr @ %p\r\n", &(hospi1.Instance->DR));
    printf("GPDMA1_Channel13 Instance @ 0x%08lX\r\n", (uint32_t)handle_GPDMA1_Channel13.Instance);


    ICNA3306_WriteCmdParam(CMD_RST, 0, NULL);
    HAL_Delay(150);

    ICNA3306_WriteCmdParam(CMD_SLEEP_OUT, 0, NULL);
    HAL_Delay(120);

    parameter[0] = 0x00;
    ICNA3306_WriteCmdParam(0xFE, 1, parameter);

    parameter[0] = 0x80;
    ICNA3306_WriteCmdParam(0xC4, 1, parameter);

    //  TearEffect
    parameter[0] = 0x00;
    ICNA3306_WriteCmdParam(0x35, 1, parameter);

    parameter[0] = 0x55;
    ICNA3306_WriteCmdParam(0x3A, 1, parameter);

     // (Memory Data Access Control)
     parameter[0] = 0x00; // RGB
     ICNA3306_WriteCmdParam(0x36, 1, parameter);

    parameter[0] = 0x20;
    ICNA3306_WriteCmdParam(0x53, 1, parameter);

    parameter[0] = 0xFF;
    ICNA3306_WriteCmdParam(0x51, 1, parameter);

    parameter[0] = 0xFF;
    ICNA3306_WriteCmdParam(0x63, 1, parameter);


    ICNA3306_WriteCmdParam(CMD_DISPLAY_ON, 0, NULL);
    HAL_Delay(120);
}
