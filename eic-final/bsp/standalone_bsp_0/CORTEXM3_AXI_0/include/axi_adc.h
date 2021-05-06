
#ifndef AXI_ADC_H
#define AXI_ADC_H

/****************** Include Files ********************/
#include "xstatus.h"

/****************** Register Definitions ********************/
#define AXI_ADC_CTL_REG_OFFSET      0x00
#define AXI_ADC_DATA_REG_OFFSET     0x04
#define AXI_ADC_DST_ADDR_REG_OFFSET 0x08
#define AXI_ADC_DST_SIZE_REG_OFFSET 0x0c
#define AXI_ADC_CLK_DIV_REG_OFFSET  0x10
#define AXI_ADC_TRIG_CTL_REG_OFFSET 0x14
#define AXI_ADC_CMPR_H_REG_OFFSET   0x18
#define AXI_ADC_CMPR_L_REG_OFFSET   0x1c

#define AXI_ADC_CTL_REG_REPEAT_BIT      0x01
#define AXI_ADC_CTL_REG_NOOUT_BIT       0x02
#define AXI_ADC_CTL_REG_TRIGSTART_BIT   0x04
#define AXI_ADC_CTL_REG_BUSY_BIT        0x08
#define AXI_ADC_CTL_REG_START_BIT       0x10
#define AXI_ADC_CTL_REG_STARTSINGLE_BIT 0x20
#define AXI_ADC_CTL_REG_STOP_BIT        0x40
#define AXI_ADC_CTL_REG_STOPTRIG_BIT    0x80

#define AXI_ADC_TRIGCTL_REG_MODE_BITS   0x03
#define AXI_ADC_TRIGCTL_REG_HCMPEN_BIT  0x04
#define AXI_ADC_TRIGCTL_REG_LCMPEN_BIT  0x08
#define AXI_ADC_TRIGCTL_REG_IEN_BIT     0x10

/****************** Functions ********************/
uint8_t AXI_ADC_getDataReg(uint32_t baseAddress);

uint8_t AXI_ADC_isBusy(uint32_t baseAddress);

XStatus AXI_ADC_reset(uint32_t baseAddress);

XStatus AXI_ADC_waitIdle(uint32_t baseAddress);

XStatus AXI_ADC_convertSingle(uint32_t baseAddress);

uint8_t AXI_ADC_convertSingleBlocked(uint32_t baseAddress);

XStatus AXI_ADC_setSamplingClockDivision(uint32_t baseAddress, u16 division);

XStatus AXI_ADC_startSequentialConversion(uint32_t baseAddress, const u8 *dstAddr, u32 length);

XStatus AXI_ADC_stopConversion(uint32_t baseAddress);

XStatus AXI_ADC_stopTrigger(uint32_t baseAddress);

#endif // AXI_ADC_H
