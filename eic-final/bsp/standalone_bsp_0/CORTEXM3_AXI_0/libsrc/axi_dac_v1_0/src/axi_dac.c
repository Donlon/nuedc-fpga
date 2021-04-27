

/***************************** Include Files *******************************/
#include "axi_dac.h"
#include "xil_io.h"

#define REG32(base, offset) (*(volatile u32 *) ((u32) (base) + (offset)))

/************************** Function Definitions ***************************/
XStatus AXI_DAC_convertSingle(void *baseaddr_p, u8 data) {
	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) &= ~(1 << AXI_DAC_CTL_REG_REPEAT_BIT);

    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_DATA_REG_OFFSET, (u32) data);

    return XST_SUCCESS;
}

XStatus AXI_DAC_setDacClockDivision(void *baseaddr_p, u16 division) {
    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_CLK_DIV_REG_OFFSET, (u32) division);

    return XST_SUCCESS;
}

XStatus AXI_DAC_startSequenceConversion(void *baseaddr_p, u8 *data_src, u32 length) {
    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_SRC_ADDR_REG_OFFSET, (u32) data_src);
    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_SRC_SIZE_REG_OFFSET, (u32) length);

	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_REPEAT_BIT);
	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) &= ~(1 << AXI_DAC_CTL_REG_LOOP_BIT);

	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_START_BIT);
    return XST_SUCCESS;
}

XStatus AXI_DAC_startSequenceConversionLooped(void *baseaddr_p, u8 *data_src, u32 length) {
    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_SRC_ADDR_REG_OFFSET, (u32) data_src);
    AXI_DAC_mWriteReg((u32) baseaddr_p, AXI_DAC_SRC_SIZE_REG_OFFSET, (u32) length);

	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_REPEAT_BIT);
	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_LOOP_BIT);

	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_START_BIT);
    return XST_SUCCESS;
}

XStatus AXI_DAC_isBusy(void *baseaddr_p, u8 *busy) {
	*busy = (AXI_DAC_mReadReg((u32) baseaddr_p, AXI_DAC_CTL_REG_OFFSET) & (1 << AXI_DAC_CTL_REG_BUSY_BIT)) ? 1 : 0;
    return XST_SUCCESS;
}

XStatus AXI_DAC_stopConversion(void *baseaddr_p) {
	REG32(baseaddr_p, AXI_DAC_CTL_REG_OFFSET) |= (1 << AXI_DAC_CTL_REG_STOP_BIT);
    return XST_SUCCESS;
}
