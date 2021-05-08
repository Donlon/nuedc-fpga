/// @file axi_dac.h

#ifndef AXI_DAC_H
#define AXI_DAC_H

/****************** Include Files ********************/
#include "xstatus.h"

/****************** Register Definitions ********************/
#define AXI_DAC_CTL_REG_OFFSET      0x00  /**< CTL register offset */
#define AXI_DAC_DATA_REG_OFFSET     0x04  /**< DATA register offset */
#define AXI_DAC_SRC_ADDR_REG_OFFSET 0x08  /**< SRC_ADDR register offset */
#define AXI_DAC_SRC_SIZE_REG_OFFSET 0x0c  /**< SRC_SIZE register offset */
#define AXI_DAC_CLK_DIV_REG_OFFSET  0x10  /**< CLK_DIV register offset */

#define AXI_DAC_CTL_REG_REPEAT_BIT  0x01  /**< CTL register REPEAT bit */
#define AXI_DAC_CTL_REG_LOOP_BIT    0x02  /**< CTL register LOOP bit */
#define AXI_DAC_CTL_REG_BUSY_BIT    0x04  /**< CTL register BUSY bit */
#define AXI_DAC_CTL_REG_START_BIT   0x08  /**< CTL register START bit */
#define AXI_DAC_CTL_REG_STOP_BIT    0x10  /**< CTL register STOP bit */

/**
 * @brief 进行 DAC 的单次转换输出
 * @param baseAddress DAC Controller base address
 * @param data        输出电平
 */
XStatus AXI_DAC_convertSingle(uint32_t baseAddress, uint8_t data);

/**
 * @brief 设置 DAC 输出时钟分频系数
 * 设置 DAC 输出时钟分频系数。当 division = 0 或 division = 1 时，输出时钟速率与模块时钟速率相同。
 * @param baseAddress DAC Controller base address
 * @param division    分频系数
 */
XStatus AXI_DAC_setOutputClockDivision(uint32_t baseAddress, uint16_t division);

/**
 * @brief 开始 DAC 重复输出
 * @param baseAddress DAC Controller base address
 * @param dataSrc 输出数据所在地址
 * @param length  输出长度
 */
XStatus AXI_DAC_startSequenceConversion(uint32_t baseAddress, const uint8_t *dataSrc, uint32_t length);

/**
 * @brief 开始 DAC 循环输出
 * @param baseAddress DAC Controller base address
 * @param dataSrc     输出数据所在地址
 * @param length      输出长度
 */
XStatus AXI_DAC_startSequenceConversionLooped(uint32_t baseAddress, const uint8_t *dataSrc, uint32_t length);

/**
 * @brief 获取 DAC 控制器繁忙状态
 * @param baseAddress DAC Controller base address
 * @param busy  繁忙状态，0: 空闲，其他值: 繁忙
 */
XStatus AXI_DAC_isBusy(uint32_t baseAddress, uint8_t *busy);

/**
 * @brief 停止当前 DAC 转换
 * @param baseAddress DAC Controller base address
 */
XStatus AXI_DAC_stopConversion(uint32_t baseAddress);

#endif // AXI_DAC_H
