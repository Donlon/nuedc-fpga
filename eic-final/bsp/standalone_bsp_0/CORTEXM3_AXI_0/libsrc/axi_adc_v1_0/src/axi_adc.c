//! @addtogroup axi-adc AXI ADC Controller
//! @{

/***************************** Include Files *******************************/
#include "axi_adc.h"

#define REG32(base, offset) (*(volatile u32 *) ((u32) (base) + (offset)))

/************************** Function Definitions ***************************/

uint8_t AXI_ADC_getDataReg(uint32_t baseAddress) {
    return REG32(baseAddress, AXI_ADC_DATA_REG_OFFSET);
}

XStatus AXI_ADC_convertSingle(uint32_t baseAddress) {
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) &= ~AXI_ADC_CTL_REG_REPEAT_BIT;
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) |= AXI_ADC_CTL_REG_START_BIT;
    return XST_SUCCESS;
}

uint8_t AXI_ADC_isBusy(uint32_t baseAddress) {
    return (REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) & AXI_ADC_CTL_REG_BUSY_BIT) ? 1 : 0;
}

XStatus AXI_ADC_reset(uint32_t baseAddress) {
    AXI_ADC_stopConversion(baseAddress);
    AXI_ADC_waitIdle(baseAddress);
    return XST_SUCCESS;
}

XStatus AXI_ADC_waitIdle(uint32_t baseAddress) {
    uint8_t busy = 1;
    while (busy) {
        busy = AXI_ADC_isBusy(baseAddress);
    }
    return XST_SUCCESS;
}

uint8_t AXI_ADC_convertSingleBlocked(uint32_t baseAddress) {
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) |= AXI_ADC_CTL_REG_STARTSINGLE_BIT;
    return AXI_ADC_getDataReg(baseAddress);
}

XStatus AXI_ADC_setSamplingClockDivision(uint32_t baseAddress, uint16_t division) {
    REG32(baseAddress, AXI_ADC_CLK_DIV_REG_OFFSET) = division;
    return XST_SUCCESS;
}

XStatus AXI_ADC_startSequentialConversion(uint32_t baseAddress, const uint8_t *data_src, uint32_t length) {
    REG32(baseAddress, AXI_ADC_DST_ADDR_REG_OFFSET) = (uint32_t) data_src;
    REG32(baseAddress, AXI_ADC_DST_SIZE_REG_OFFSET) = (uint32_t) length;
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) |= AXI_ADC_CTL_REG_REPEAT_BIT | AXI_ADC_CTL_REG_START_BIT;
    return XST_SUCCESS;
}

XStatus AXI_ADC_stopConversion(uint32_t baseAddress) {
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) |= AXI_ADC_CTL_REG_STOP_BIT;
    return XST_SUCCESS;
}

XStatus AXI_ADC_stopTrigger(uint32_t baseAddress) {
    REG32(baseAddress, AXI_ADC_CTL_REG_OFFSET) |= AXI_ADC_CTL_REG_STOPTRIG_BIT;
    return XST_SUCCESS;
}

//! @}
