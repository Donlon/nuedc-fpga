#include <cm3soc/cm3soc.h>

#include <xparameters.h>
#include <xgpio.h>
#include <axi_dac.h>

int value = 1;

XGpio gpio;   /* The driver instance for GPIO Device 0 */

int systick_init() {
    return SysTick_Config(50e6 / 256000); // 256 kHz
}

int gpio_init() {
    int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize GPIO
    if (status != XST_SUCCESS) {
        return status;
    }
    XGpio_SetDataDirection(&gpio, 1, 0); // set GPIO direction
    XGpio_DiscreteWrite(&gpio, 1, 0x2); // set GPIO output

    return status;
}

int system_init() {
    int status;
    status = systick_init();
    if (status != XST_SUCCESS) {
        return status;
    }
    status = gpio_init();
    if (status != XST_SUCCESS) {
        return status;
    }
    return status;
}

int main() {
    int status = system_init();
    if (status != XST_SUCCESS) {
        while (1);
    }
    return 0;
}

void SysTick_Handler() {
    // Output a 256 kHz saw wave
    AXI_DAC_convertSingle((void*) XPAR_AXI_DAC_0_S_AXI_BASEADDR, value & 0xff);
    value++;
}
