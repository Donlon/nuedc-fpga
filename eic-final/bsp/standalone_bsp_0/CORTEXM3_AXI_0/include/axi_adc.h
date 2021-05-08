/// @file axi_adc.h

#ifndef AXI_ADC_H
#define AXI_ADC_H

/****************** Include Files ********************/
#include "xstatus.h"

/****************** Register Definitions ********************/
#define AXI_ADC_CTL_REG_OFFSET      0x00  /**< CTRL register offset */
#define AXI_ADC_DATA_REG_OFFSET     0x04  /**< DATA register offset */
#define AXI_ADC_DST_ADDR_REG_OFFSET 0x08  /**< DST_ADDR register offset */
#define AXI_ADC_DST_SIZE_REG_OFFSET 0x0c  /**< DST_SIZE register offset */
#define AXI_ADC_CLK_DIV_REG_OFFSET  0x10  /**< DST_ADDR register offset */
#define AXI_ADC_TRIG_CTL_REG_OFFSET 0x14  /**< TRIG_CTL register offset */
#define AXI_ADC_CMPR_H_REG_OFFSET   0x18  /**< CMPR_H register offset */
#define AXI_ADC_CMPR_L_REG_OFFSET   0x1c  /**< CMPR_L register offset */

#define AXI_ADC_CTL_REG_REPEAT_BIT      0x01  /**< CTL register Repeat bit */
#define AXI_ADC_CTL_REG_NOOUT_BIT       0x02  /**< CTL register Repeat bit */
#define AXI_ADC_CTL_REG_TRIGSTART_BIT   0x04  /**< CTL register Repeat bit */
#define AXI_ADC_CTL_REG_BUSY_BIT        0x08  /**< CTL register TrigStart bit */
#define AXI_ADC_CTL_REG_START_BIT       0x10  /**< CTL register Busy bit */
#define AXI_ADC_CTL_REG_STARTSINGLE_BIT 0x20  /**< CTL register Start bit */
#define AXI_ADC_CTL_REG_STOP_BIT        0x40  /**< CTL register StartSingle bit */
#define AXI_ADC_CTL_REG_STOPTRIG_BIT    0x80  /**< CTL register Stop bit */

#define AXI_ADC_TRIGCTL_REG_MODE_BITS   0x03  /**< TRIG_CTL register Mode bit */
#define AXI_ADC_TRIGCTL_REG_HCMPEN_BIT  0x04  /**< TRIG_CTL register HCMP_EN bit */
#define AXI_ADC_TRIGCTL_REG_LCMPEN_BIT  0x08  /**< TRIG_CTL register LCMP_EN bit */
#define AXI_ADC_TRIGCTL_REG_IEN_BIT     0x10  /**< TRIG_CTL register IEN bit */

/**
 * @brief 获取 DATA 寄存器的数据
 * @param baseAddress ADC Controller base address
 * @return DATA 寄存器的数据
 */
uint8_t AXI_ADC_getDataReg(uint32_t baseAddress);

/**
 * @brief 获取当前繁忙状态
 * @param baseAddress ADC Controller base address
 * @return 0: 空闲，其他值: 繁忙
 */
uint8_t AXI_ADC_isBusy(uint32_t baseAddress);

/**
 * @brief 复位 ADC 状态
 * 向 CTL 寄存器写入 STOP 位，并等待直至 BUSY 位为 0
 * @param baseAddress ADC Controller base address
 */
XStatus AXI_ADC_reset(uint32_t baseAddress);

/**
 * @brief 等待 ADC 模块空闲
 * @param baseAddress ADC Controller base address
 */
XStatus AXI_ADC_waitIdle(uint32_t baseAddress);

/**
 * @brief 从 ADC 输入进行单次采样
 * @param baseAddress ADC Controller base address
 */
XStatus AXI_ADC_convertSingle(uint32_t baseAddress);

/**
 * @brief 从 ADC 输入进行单次采样，阻塞
 * @param baseAddress ADC Controller base address
 */
uint8_t AXI_ADC_convertSingleBlocked(uint32_t baseAddress);

/**
 * @brief 设置 ADC 时钟分频系数
 * @param baseAddress ADC Controller base address
 * @param division    分频系数
 */
XStatus AXI_ADC_setSamplingClockDivision(uint32_t baseAddress, uint16_t division);

/**
 * @brief 开始 ADC 重复转换
 * @param baseAddress ADC Controller base address
 * @param dstAddr 数据的保存地址
 * @param length  数据的采样数量
 */
XStatus AXI_ADC_startSequentialConversion(uint32_t baseAddress, const uint8_t *dstAddr, uint32_t length);

/**
 * @brief 停止 ADC 转换
 * 停止当前未结束的 ADC 转换
 * @param baseAddress ADC Controller base address
 */
XStatus AXI_ADC_stopConversion(uint32_t baseAddress);

/**
 * @brief 停止 ADC 的触发等待
 * 若 ADC 控制器处于等待触发状态，则停止触发。若 ADC 控制器处于采样状态，该操作则不会产生效果
 * @param baseAddress ADC Controller base address
 */
XStatus AXI_ADC_stopTrigger(uint32_t baseAddress);

#endif // AXI_ADC_H
