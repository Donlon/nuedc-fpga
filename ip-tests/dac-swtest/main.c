#include <cm3soc/cm3soc.h>

#include <xparameters.h>
#include <xgpio.h>
#include <axi_dac.h>
#include <axi_adc.h>
#include <math.h>

#define AX7020_KEY2  (1 << 4) // GPIO4
#define AX7020_KEY3  (1 << 3) // GPIO3
#define AX7020_KEY4  (1 << 2) // GPIO2
#define AX7020_LED1  (1 << 1) // GPIO1
#define AX7020_LED2  (1 << 0) // GPIO0

#define ADC_BASE     XPAR_AXI_ADC_0_S_AXI_BASEADDR
#define DAC_BASE     XPAR_AXI_DAC_0_S_AXI_BASEADDR

struct {
    int switch_test_mode: 1;
} pendingEvents = {};

typedef enum {
    IDLE,

    TEST_DAC_SINGLE_MODE, // DAC 单次转换，重复，使用SysTick作为定时器
    TEST_DAC_REPEAT_MODE, // DAC 重复模式，不循环
    TEST_DAC_LOOP_MODE,   // DAC 循环模式

    TEST_ADC_SINGLE,      // ADC 单次采样并用 DAC 输出
    TEST_ADC_REPEAT,      // ADC 连续采样并用 DAC 输出
} test_state_t;

test_state_t state;

XGpio gpio;   /* The driver instance for GPIO Device 0 */

#define DAC_BUFFER_SIZE 4096
#define ADC_FREQ_KHZ    30000 // 30000 kHz

__section(".exdata")
__aligned(64)
uint8_t dac_buffer[DAC_BUFFER_SIZE];

int gpio_init() {
    int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize GPIO
    if (status != XST_SUCCESS) {
        return status;
    }
    XGpio_SetDataDirection(&gpio, 1, AX7020_KEY2 | AX7020_KEY3 | AX7020_KEY4); // set GPIO direction
    XGpio_DiscreteWrite(&gpio, 1, AX7020_LED1); // LED1 off, LED2 on

    XGpio_InterruptEnable(&gpio, XGPIO_IR_CH1_MASK); // Channel 1 interrupt enable
    XGpio_InterruptGlobalEnable(&gpio);

    NVIC_ClearAllPendingIRQ();
    return status;
}

void initDAC() {
    AXI_DAC_stopConversion(DAC_BASE);
    uint8_t busy = 1;
    while (busy) {
        AXI_DAC_isBusy(DAC_BASE, &busy);
    }
    AXI_DAC_setOutputClockDivision(DAC_BASE, 150000 / ADC_FREQ_KHZ); // 50 / 1 MHz
}

void initADC() {
    AXI_ADC_reset(ADC_BASE);
    AXI_ADC_setSamplingClockDivision(ADC_BASE, 150000 / ADC_FREQ_KHZ);
}

int system_init() {
    int status;
    status = gpio_init();
    if (status != XST_SUCCESS) {
        return status;
    }
    initDAC();
    initADC();
    return status;
}

void buildDACBuffer() {
#if 1
    const float max = 255;
    for (int i = 0; i < DAC_BUFFER_SIZE; i++) {
        float phase = (float) ((float) i * 2.f * M_PI / DAC_BUFFER_SIZE);
        dac_buffer[i] = (uint8_t) floorf(max * (1.f - sinf(phase) / 2.f));
    }
#elif 0
    for (int i = 0; i < DAC_BUFFER_SIZE; i++) {
        dac_buffer[i] = rand() & 255;
        // dac_buffer[i] = i;
    }
#endif
}

void startRepeatMode(int loop) {
    if (loop) {
        AXI_DAC_startSequenceConversionLooped(DAC_BASE, dac_buffer, sizeof(dac_buffer));
    } else {
        AXI_DAC_startSequenceConversion(DAC_BASE, dac_buffer, sizeof(dac_buffer));
    }
}

uint8_t adcSingleConv() {
    AXI_ADC_convertSingle(ADC_BASE);
    AXI_ADC_waitIdle(ADC_BASE);
    return AXI_ADC_getDataReg(ADC_BASE);
}

void main_loop() {
    while (1) {
        if (pendingEvents.switch_test_mode) {
            switch (state) { // last state
                default:
                case IDLE:
                    state = TEST_DAC_REPEAT_MODE;
                    break;
                case TEST_DAC_REPEAT_MODE:
                    buildDACBuffer();
                    AXI_DAC_stopConversion(DAC_BASE);
                    state = TEST_DAC_LOOP_MODE;
                    break;
                case TEST_DAC_LOOP_MODE:
                    AXI_DAC_stopConversion(DAC_BASE);
                    state = TEST_DAC_SINGLE_MODE;
                    break;
                case TEST_DAC_SINGLE_MODE:
                    SysTick->CTRL = 0; // disable SysTick
                    state = TEST_ADC_SINGLE;
                    break;
                case TEST_ADC_SINGLE:
                    state = TEST_ADC_REPEAT;
                    break;
                case TEST_ADC_REPEAT:
                    state = IDLE;
                    break;
            }
            switch (state) { // next state
                default:
                case IDLE:
                    break;
                case TEST_DAC_LOOP_MODE:
                    startRepeatMode(0);
                    break;
                case TEST_DAC_REPEAT_MODE:
                    startRepeatMode(1);
                    break;
                case TEST_DAC_SINGLE_MODE:
                    SysTick_Config((uint32_t) (50e6 / 256000)); // 256 kHz
                    break;
            }
            // Switch test mode
            pendingEvents.switch_test_mode = 0;

            switch (state) {
                case TEST_ADC_SINGLE:
                    while (!pendingEvents.switch_test_mode) {
                        AXI_ADC_waitIdle(ADC_BASE);
                        AXI_ADC_startSequentialConversion(ADC_BASE, dac_buffer, sizeof(dac_buffer));
                        AXI_ADC_waitIdle(ADC_BASE);
                        AXI_DAC_startSequenceConversion(DAC_BASE, dac_buffer, sizeof(dac_buffer));
                    }
                    break;
                case TEST_ADC_REPEAT:
                    while (!pendingEvents.switch_test_mode) {
                        uint8_t v = adcSingleConv();
                        AXI_DAC_convertSingle(DAC_BASE, v);
                    }
                    break;
                default:
                    break;
            }
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

    main_loop();
}

void SysTick_Handler() {
    static int isUpMode = 1;
    static int value = 0;
    if (state == TEST_DAC_SINGLE_MODE) {
        // Output a 0.5 kHz/256 kSps triangle wave
        AXI_DAC_convertSingle(DAC_BASE, value);
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
    pendingEvents.switch_test_mode = 1;
    while (1);
}
