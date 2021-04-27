
#ifndef AXI_DAC_H
#define AXI_DAC_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"

#define AXI_DAC_CTL_REG_OFFSET       0
#define AXI_DAC_DATA_REG_OFFSET      4
#define AXI_DAC_SRC_ADDR_REG_OFFSET  8
#define AXI_DAC_SRC_SIZE_REG_OFFSET 12
#define AXI_DAC_CLK_DIV_REG_OFFSET  16

#define AXI_DAC_CTL_REG_REPEAT_BIT  0x00
#define AXI_DAC_CTL_REG_LOOP_BIT    0x01
#define AXI_DAC_CTL_REG_BUSY_BIT    0x02
#define AXI_DAC_CTL_REG_START_BIT   0x03
#define AXI_DAC_CTL_REG_STOP_BIT    0x04


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a AXI_DAC register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the AXI_DACdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void AXI_DAC_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define AXI_DAC_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a AXI_DAC register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the AXI_DAC device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 AXI_DAC_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define AXI_DAC_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the AXI_DAC instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus AXI_DAC_Reg_SelfTest(void * baseaddr_p);

/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the AXI_DAC instance to be worked on.
 * @param   data       DAC output data
 */
XStatus AXI_DAC_convertSingle(void *baseaddr_p, u8 data);

// not implemented
XStatus AXI_DAC_setDacClockDivision(void *baseaddr_p, u16 division);

// not implemented
XStatus AXI_DAC_startSequenceConversion(void *baseaddr_p, u8 *data_src, u32 length);

// not implemented
XStatus AXI_DAC_startSequenceConversionLooped(void *baseaddr_p, u8 *data_src, u32 length);

// not implemented
XStatus AXI_DAC_isBusy(void *baseaddr_p, u8 *busy);

// not implemented
XStatus AXI_DAC_stopConversion(void *baseaddr_p);

#endif // AXI_DAC_H
