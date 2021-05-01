#include <cm3soc/cm3soc.h>

#include <xparameters.h>
#include <xgpio.h>
#include <axi_dac.h>
#include <math.h>

struct {
    int switch_test_mode: 1;
} pending_events = {};

int value = 0;

typedef enum {
    IDLE,
    TEST_REPEAT_MODE,
    TEST_LOOP_MODE,
    TEST_SINGLE_MODE,
} test_state_t;

test_state_t state;

int isUpMode = 1;

XGpio gpio;   /* The driver instance for GPIO Device 0 */

#define DAC_BUFFER_SIZE 512

__section(".exdata")
__aligned(32)
uint8_t dac_buffer[DAC_BUFFER_SIZE];

void initDAC();

int systick_init() {
    return (int) SysTick_Config((uint32_t) (50e6 / 256000)); // 256 kHz
}

int gpio_init() {
    int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize GPIO
    if (status != XST_SUCCESS) {
        return status;
    }
    XGpio_SetDataDirection(&gpio, 1, 0); // set GPIO direction
    XGpio_DiscreteWrite(&gpio, 1, 0x2); // set GPIO output

    XGpio_InterruptGlobalEnable(&gpio);
    XGpio_InterruptEnable(&gpio, 0b011100); // 2, 3, 4: buttons

    return status;
}

int system_init() {
    int status;
    status = gpio_init();
    if (status != XST_SUCCESS) {
        return status;
    }
    initDAC();
    return status;
}

void buildDACBuffer() {
#if 0
    for (int i = 0; i < DAC_BUFFER_SIZE; i++) {
        dac_buffer[i] = (uint8_t) floorf(127.5f
                                         - 127.5f * sinf((float) ((float) i * 2.f * M_PI / (float) DAC_BUFFER_SIZE)));
    }
#else
    for (int i = 0; i < DAC_BUFFER_SIZE / 2; i++) {
        dac_buffer[i] = i;
        dac_buffer[DAC_BUFFER_SIZE - (i + 1)] = i;
    }
#endif
}

void startRepeatMode(int loop) {
    AXI_DAC_setDacClockDivision((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR, 1); // 1 MHz
    if (loop) {
        AXI_DAC_startSequenceConversionLooped((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR,
                                              dac_buffer,
                                              sizeof(dac_buffer));
    } else {
        AXI_DAC_startSequenceConversion((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR,
                                        dac_buffer,
                                        sizeof(dac_buffer));
    }
}

void stopRepeatMode() {
    AXI_DAC_stopConversion((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR);
}

void initDAC() {
    AXI_DAC_stopConversion((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR);
    uint8_t busy = 1;
    while (busy) {
        AXI_DAC_isBusy((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR, &busy);
    }
}

void main_loop() {
    while (1) {
        if (pending_events.switch_test_mode) {
            switch (state) {
                default:
                case IDLE:
                    state = TEST_REPEAT_MODE;
                    break;
                case TEST_REPEAT_MODE:
                    state = TEST_LOOP_MODE;
                    break;
                case TEST_LOOP_MODE:
                    state = TEST_SINGLE_MODE;
                    break;
                case TEST_SINGLE_MODE:
                    state = IDLE;
                    SysTick->CTRL = 0; // disable SysTick
                    break;
            }
            stopRepeatMode();
            switch (state) {
                default:
                case IDLE:
                    break;
                case TEST_LOOP_MODE:
                    startRepeatMode(0);
                    break;
                case TEST_REPEAT_MODE:
                    startRepeatMode(1);
                    break;
                case TEST_SINGLE_MODE:
                    SysTick_Config((uint32_t) (50e6 / 256000)); // 256 kHz
                    break;
            }
            // Switch test mode
            pending_events.switch_test_mode = 0;
        } else {
            // no pending events and wait for interrupt
            __WFI();
        }
    }
}

int main() {
    int init_status = system_init();
    if (init_status != XST_SUCCESS) {
        while (1);
    }
    buildDACBuffer();

#if 0
    startRepeatMode(0);
#else
    startRepeatMode(1);
#endif

#if 0
    state = TEST_SINGLE_MODE;
#endif

    main_loop();
}

void SysTick_Handler() {
    if (state == TEST_SINGLE_MODE) {
        // Output a 0.5 kHz/256 kSps triangle wave
        AXI_DAC_convertSingle((void *) XPAR_AXI_DAC_0_S_AXI_BASEADDR, value);
        if (isUpMode) {
            if (value >= 255) {
                value--;
                isUpMode = 0;
            } else {
                value++;
            }
        } else {
            if (value <= 0) {
                value++;
                isUpMode = 1;
            } else {
                value--;
            }
        }
    }
}

void GPIO_Handler() {
    pending_events.switch_test_mode = 1;
    while (1);
}