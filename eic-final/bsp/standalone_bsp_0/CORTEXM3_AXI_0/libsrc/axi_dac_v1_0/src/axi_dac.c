//! @addtogroup axi-dac AXI DAC Controller
//! @{

/***************************** Include Files *******************************/
#include "axi_dac.h"

#define REG32(base, offset) (*(volatile uint32_t *) ((u32) (base) + (offset)))

/************************** Function Definitions ***************************/
XStatus AXI_DAC_convertSingle(uint32_t baseAddress, uint8_t data) {
    REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) &= ~AXI_DAC_CTL_REG_REPEAT_BIT;
    REG32(baseAddress, AXI_DAC_DATA_REG_OFFSET) = data;
    return XST_SUCCESS;
}

XStatus AXI_DAC_setOutputClockDivision(uint32_t baseAddress, uint16_t division) {
    REG32(baseAddress, AXI_DAC_CLK_DIV_REG_OFFSET) = division;
    return XST_SUCCESS;
}

XStatus AXI_DAC_startSequenceConversion(uint32_t baseAddress, const uint8_t *dataSrc, uint32_t length) {
    REG32(baseAddress, AXI_DAC_SRC_ADDR_REG_OFFSET) = (uint32_t) dataSrc;
    REG32(baseAddress, AXI_DAC_SRC_SIZE_REG_OFFSET) = length;

    REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) &= ~AXI_DAC_CTL_REG_LOOP_BIT;
    REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) |= AXI_DAC_CTL_REG_REPEAT_BIT + AXI_DAC_CTL_REG_START_BIT;
    return XST_SUCCESS;
}

XStatus AXI_DAC_startSequenceConversionLooped(uint32_t baseAddress, const uint8_t *dataSrc, uint32_t length) {
    REG32(baseAddress, AXI_DAC_SRC_ADDR_REG_OFFSET) = (uint32_t) dataSrc;
    REG32(baseAddress, AXI_DAC_SRC_SIZE_REG_OFFSET) = length;

    REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) |= AXI_DAC_CTL_REG_REPEAT_BIT + AXI_DAC_CTL_REG_LOOP_BIT
                                                  + AXI_DAC_CTL_REG_START_BIT;
    return XST_SUCCESS;
}

XStatus AXI_DAC_isBusy(uint32_t baseAddress, uint8_t *busy) {
    *busy = (REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) & AXI_DAC_CTL_REG_BUSY_BIT) ? 1 : 0;
    return XST_SUCCESS;
}

XStatus AXI_DAC_stopConversion(uint32_t baseAddress) {
    REG32(baseAddress, AXI_DAC_CTL_REG_OFFSET) |= AXI_DAC_CTL_REG_STOP_BIT;
    return XST_SUCCESS;
}

//! @}
