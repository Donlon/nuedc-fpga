
#ifndef AXI_DAC_H
#define AXI_DAC_H

/****************** Include Files ********************/
#include "xstatus.h"

#define AXI_DAC_CTL_REG_OFFSET      0x00
#define AXI_DAC_DATA_REG_OFFSET     0x04
#define AXI_DAC_SRC_ADDR_REG_OFFSET 0x08
#define AXI_DAC_SRC_SIZE_REG_OFFSET 0x0c
#define AXI_DAC_CLK_DIV_REG_OFFSET  0x10

#define AXI_DAC_CTL_REG_REPEAT_BIT  0x01
#define AXI_DAC_CTL_REG_LOOP_BIT    0x02
#define AXI_DAC_CTL_REG_BUSY_BIT    0x04
#define AXI_DAC_CTL_REG_START_BIT   0x08
#define AXI_DAC_CTL_REG_STOP_BIT    0x10

XStatus AXI_DAC_convertSingle(uint32_t baseAddress, uint8_t data);

XStatus AXI_DAC_setOutputClockDivision(uint32_t baseAddress, uint16_t division);

XStatus AXI_DAC_startSequenceConversion(uint32_t baseAddress, const uint8_t *data_src, u32 length);

XStatus AXI_DAC_startSequenceConversionLooped(uint32_t baseAddress, const uint8_t *data_src, u32 length);

XStatus AXI_DAC_isBusy(uint32_t baseAddress, uint8_t *busy);

XStatus AXI_DAC_stopConversion(uint32_t baseAddress);

#endif // AXI_DAC_H
