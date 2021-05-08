#include "common.h"
#include "lcd.h"
#include "lcd_commands.h"
#include "gpio.h"
#include "main.h"
#include <xparameters.h>
#include <cm3soc/cm3soc.h>

// Clock pin
static void PIN_SCL_LOW() {pin_drive_low(&gpio, GPIO14);}
static void PIN_SCL_HIGH() {pin_drive_high(&gpio, GPIO14);}
// Data pin
static void PIN_SI_LOW()   {pin_drive_low(&gpio, GPIO15);}
static void PIN_SI_HIGH()  {pin_drive_high(&gpio, GPIO15);}
// Chip select pin
static void PIN_CS_LOW()   {pin_drive_low(&gpio, GPIO12);}
static void PIN_CS_HIGH()  {pin_drive_high(&gpio, GPIO12);}
// A0 pin
static void PIN_A0_LOW()   {pin_drive_low(&gpio, GPIO13);}
static void PIN_A0_HIGH()  {pin_drive_high(&gpio, GPIO13);}

#define SCL_PERIOD 0 //  fSCL≈100kHz when MCLK=16MHz

void lcd_write_byte(uchar byte) {
    PIN_CS_LOW();
    for (uchar i = 0; i < 8; i++) {
        PIN_SCL_LOW();

        if (byte & 0x80) {
            PIN_SI_HIGH();
        } else {
            PIN_SI_LOW();
        }
        PIN_SCL_HIGH();

        byte <<= 1;
    }
    PIN_CS_HIGH();
}

void lcd_write_data(uchar dat) {
    PIN_A0_HIGH();
    lcd_write_byte(dat);
}

void lcd_write_command(uchar cmd) {
    PIN_A0_LOW();
    lcd_write_byte(cmd);
}

void lcd_select_address(uchar page, uchar column) {
    lcd_write_command(CMD_SET_PAGE_ADDRESS(page));          // page address
    lcd_write_command(CMD_SET_COLUMN_ADDRESS_HIGH(column)); // column address high 4 bits
    lcd_write_command(CMD_SET_COLUMN_ADDRESS_LOW(column));  // column address low 4 bits
}

void lcd_initialize(void) {

    lcd_write_command(0xaf);
    //ON DISPLAY
    lcd_write_command(0x40); // CMD_POWER_CONTROL | 0
    //STAR DISPLAY
    lcd_write_command(0xa0); // ADC NORMAL
    lcd_write_command(0xa6); // CMD_REVERSE_DISPLAY_OFF
    lcd_write_command(0xa4); // CMD_ENTIRE_DISPLAY_OFF CLEAR
    lcd_write_command(0xa2); // 1/9 BIAS
    lcd_write_command(0xc8); // COMMON OUTPUT DIRECTION: reverse
    lcd_write_command(0x2f); // CMD_POWER_CONTROL | 0b111  POWER CONTROL
    lcd_write_command(0x24); // RESISTER RATIO
    lcd_write_command(0x81); // VOLUM MODE SET
    lcd_write_command(0x24); // RESISTER RATIO
}

int init_gpio(void) {

    int status = XGpio_Initialize(&gpio, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize GPIO
    if (status != XST_SUCCESS) {
        return status;
    }
    XGpio_SetDataDirection(&gpio, 1, 0); // set GPIO direction
    PIN_SI_LOW();
    PIN_SCL_LOW();
    PIN_A0_LOW();
    PIN_CS_HIGH();
    return status;
}

void lcm_clear(void) {
    for (int i = 0; i < 8; i++) {
        lcd_select_address(i, 0);
        for (int j = 0; j < 128; j++) {
            lcd_write_data(0x00);
        }
    }
}

int lcd_init() {
    int status = init_gpio();
    if (status != XST_SUCCESS) {
        return status;
    }
    lcd_initialize();
    lcm_clear();
    return status;
}
