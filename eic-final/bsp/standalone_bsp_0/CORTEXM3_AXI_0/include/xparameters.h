#ifndef XPARAMETERS_H   /* prevent circular inclusions */
#define XPARAMETERS_H   /* by using protection macros */

/* Definition for CPU ID */
#define XPAR_CPU_ID 0U

/* Definitions for peripheral CORTEXM3_AXI_0 */
#define XPAR_CORTEXM3_AXI_0_CPU_CLK_FREQ_HZ 0


/******************************************************************/

/* Canonical definitions for peripheral CORTEXM3_AXI_0 */
#define XPAR_CPU_CORTEXM3_0_CPU_CLK_FREQ_HZ 0


/******************************************************************/


/******************************************************************/

/* Platform specific definitions */
#define PLATFORM_ARM
 
/* Definitions for sleep timer configuration */
#define XSLEEP_TIMER_IS_DEFAULT_TIMER
 
 
/******************************************************************/
/* Definitions for driver AXI_DAC */
#define XPAR_AXI_DAC_NUM_INSTANCES 1

/* Definitions for peripheral AXI_DAC_0 */
#define XPAR_AXI_DAC_0_DEVICE_ID 0
#define XPAR_AXI_DAC_0_S_AXI_BASEADDR 0x40200000
#define XPAR_AXI_DAC_0_S_AXI_HIGHADDR 0x4020FFFF


/******************************************************************/

/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 2U

/* Definitions for peripheral AXI_BRAM_DATA_0 */
#define XPAR_AXI_BRAM_DATA_0_DEVICE_ID 0U
#define XPAR_AXI_BRAM_DATA_0_DATA_WIDTH 32U
#define XPAR_AXI_BRAM_DATA_0_ECC 0U
#define XPAR_AXI_BRAM_DATA_0_FAULT_INJECT 0U
#define XPAR_AXI_BRAM_DATA_0_CE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_DATA_0_UE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_DATA_0_ECC_STATUS_REGISTERS 0U
#define XPAR_AXI_BRAM_DATA_0_CE_COUNTER_WIDTH 0U
#define XPAR_AXI_BRAM_DATA_0_ECC_ONOFF_REGISTER 0U
#define XPAR_AXI_BRAM_DATA_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_AXI_BRAM_DATA_0_WRITE_ACCESS 0U
#define XPAR_AXI_BRAM_DATA_0_S_AXI_BASEADDR 0x21000000U
#define XPAR_AXI_BRAM_DATA_0_S_AXI_HIGHADDR 0x21003FFFU
#define XPAR_AXI_BRAM_DATA_0_S_AXI_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_AXI_BRAM_DATA_0_S_AXI_CTRL_HIGHADDR 0xFFFFFFFFU  


/* Definitions for peripheral AXI_BRAM_INSN_0 */
#define XPAR_AXI_BRAM_INSN_0_DEVICE_ID 1U
#define XPAR_AXI_BRAM_INSN_0_DATA_WIDTH 32U
#define XPAR_AXI_BRAM_INSN_0_ECC 0U
#define XPAR_AXI_BRAM_INSN_0_FAULT_INJECT 0U
#define XPAR_AXI_BRAM_INSN_0_CE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_INSN_0_UE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_INSN_0_ECC_STATUS_REGISTERS 0U
#define XPAR_AXI_BRAM_INSN_0_CE_COUNTER_WIDTH 0U
#define XPAR_AXI_BRAM_INSN_0_ECC_ONOFF_REGISTER 0U
#define XPAR_AXI_BRAM_INSN_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_AXI_BRAM_INSN_0_WRITE_ACCESS 0U
#define XPAR_AXI_BRAM_INSN_0_S_AXI_BASEADDR 0x00000000U
#define XPAR_AXI_BRAM_INSN_0_S_AXI_HIGHADDR 0x00003FFFU
#define XPAR_AXI_BRAM_INSN_0_S_AXI_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_AXI_BRAM_INSN_0_S_AXI_CTRL_HIGHADDR 0xFFFFFFFFU  


/******************************************************************/

/* Canonical definitions for peripheral AXI_BRAM_DATA_0 */
#define XPAR_BRAM_0_DEVICE_ID XPAR_AXI_BRAM_DATA_0_DEVICE_ID
#define XPAR_BRAM_0_DATA_WIDTH 32U
#define XPAR_BRAM_0_ECC 0U
#define XPAR_BRAM_0_FAULT_INJECT 0U
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0U
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0U
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0U
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_BRAM_0_WRITE_ACCESS 0U
#define XPAR_BRAM_0_BASEADDR 0x21000000U
#define XPAR_BRAM_0_HIGHADDR 0x21003FFFU
#define XPAR_BRAM_0_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_BRAM_0_CTRL_HIGHADDR 0xFFFFFFFEU  

/* Canonical definitions for peripheral AXI_BRAM_INSN_0 */
#define XPAR_BRAM_1_DEVICE_ID XPAR_AXI_BRAM_INSN_0_DEVICE_ID
#define XPAR_BRAM_1_DATA_WIDTH 32U
#define XPAR_BRAM_1_ECC 0U
#define XPAR_BRAM_1_FAULT_INJECT 0U
#define XPAR_BRAM_1_CE_FAILING_REGISTERS 0U
#define XPAR_BRAM_1_UE_FAILING_REGISTERS 0U
#define XPAR_BRAM_1_ECC_STATUS_REGISTERS 0U
#define XPAR_BRAM_1_CE_COUNTER_WIDTH 0U
#define XPAR_BRAM_1_ECC_ONOFF_REGISTER 0U
#define XPAR_BRAM_1_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_BRAM_1_WRITE_ACCESS 0U
#define XPAR_BRAM_1_BASEADDR 0x00000000U
#define XPAR_BRAM_1_HIGHADDR 0x00003FFFU
#define XPAR_BRAM_1_CTRL_BASEADDR 0xFFFFFFFFU  
#define XPAR_BRAM_1_CTRL_HIGHADDR 0xFFFFFFFEU  


/******************************************************************/

/* Definitions for driver GPIO */
#define XPAR_XGPIO_NUM_INSTANCES 1

/* Definitions for peripheral AXI_GPIO_0 */
#define XPAR_AXI_GPIO_0_BASEADDR 0x40100000
#define XPAR_AXI_GPIO_0_HIGHADDR 0x4010FFFF
#define XPAR_AXI_GPIO_0_DEVICE_ID 0
#define XPAR_AXI_GPIO_0_INTERRUPT_PRESENT 1
#define XPAR_AXI_GPIO_0_IS_DUAL 0


/******************************************************************/

/* Canonical definitions for peripheral AXI_GPIO_0 */
#define XPAR_GPIO_0_BASEADDR 0x40100000
#define XPAR_GPIO_0_HIGHADDR 0x4010FFFF
#define XPAR_GPIO_0_DEVICE_ID XPAR_AXI_GPIO_0_DEVICE_ID
#define XPAR_GPIO_0_INTERRUPT_PRESENT 1
#define XPAR_GPIO_0_IS_DUAL 0


/******************************************************************/

#endif  /* end of protection macro */
