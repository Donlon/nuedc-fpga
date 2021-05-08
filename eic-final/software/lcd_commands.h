#ifndef __LCD12864_COMMANDS_H__
#define __LCD12864_COMMANDS_H__

// Command list for SED1565 or ST7565R controller

#define LCD_CMD_MASK(arg, mask) ((arg) & (mask))

// (1) LCD display ON/OFF
#define CMD_DISPLAY_ON                       0b10101111 // Display on
#define CMD_DISPLAY_OFF                      0b10101110 // Display off

// (2) Sets the display RAM display start line address
#define CMD_DISPLAY_START_LINE(line)         (0b01000000 | LCD_CMD_MASK(line, 0b111111))  // 0x40, 64

// (3) Sets the display RAM page address
#define CMD_SET_PAGE_ADDRESS(address)        (0b10110000 | LCD_CMD_MASK(address, 0b1111)) // 0xb0,176

// (4)  Sets display RAM column address
#define CMD_SET_COLUMN_ADDRESS_HIGH(address) (0b00010000 | (0b1111 & (address >> 4))) // 0x10, 16
#define CMD_SET_COLUMN_ADDRESS_LOW(address)  (0b1111 & address)

// (8) Sets the display RAM address SEG output correspondence
// 0xa0, 160
#define CMD_SELECT_ADC_NORMAL             0b10100000 // normal
// 0xa1, 161
#define CMD_SELECT_ADC_REVERSED           0b10100001 // reverse

// (9) Sets the LCD display normal/reverse
// 0xa6, 166
#define CMD_REVERSE_DISPLAY_OFF           0b10100110
// 0xa7, 167"
#define CMD_REVERSE_DISPLAY_ON            0b10100111

// (10) Display all points
// 0xa4, 164
#define CMD_DISPLAY_ALL_POINTS_OFF        0b10100100 // normal display
// 0xa5, 165
#define CMD_DISPLAY_ALL_POINTS_ON         0b10100101 // all points ON

// (11) Sets the LCD drive voltage bias ratio
// ST7565R 0: 1/9 bias, 1: 1/7 bias
// SED1565*** ....... 0: 1/9, 1: 1/7
// SED1566***
// /SED1568***
// /SED1569*** ...... 0: 1/8, 1: 1/6
// SED1567*** ....... 0: 1/6, 1: 1/5
#define CMD_SET_BIAS_0                    0b10100010 // 0xa2, 162
#define CMD_SET_BIAS_1                    0b10100011 // 0xa3, 163

// (12) Sets the Read-Modify-Write mode
// At write: +1
// At read: 0
#define CMD_SET_MODIFY_READ               0b11100000 // 0xe0, 224

// (13) Clear read/modify/write mode
#define CMD_END_MODIFY_READ               0b11101110 // 0xee, 238

// (14) LCM internal reset
#define CMD_RESET                         0b11100010 // 0xe2, 226

// (15) Common output mode select
// Select COM output scan direction
// 0: normal direction,
// 1: reverse direction
#define CMD_SET_COM_OUTPUT_NORMAL         0b11000000 // 0xc0, 192
#define CMD_SET_COM_OUTPUT_REVERSED       0b11001000 // 0xc8, 200

// (16) Select internal power supply operating mode
#define BOOSTER_CIRCUIT_ON                0b100
#define VOLTAGE_REGULATOR_CIRCUIT_ON      0b10
#define VOLTAGE_FOLLOWER_CIRCUIT_ON       0b1
#define CMD_SET_POWER_CONTROL(mode)       (0b00101000 | LCD_CMD_MASK(mode, 0b111))  // 0x28, 40

// (17) Select internal resistor ratio (Rb/Ra) mode
#define CMD_SET_REGULATOR_RESISTOR(ratio) (0b00100000 | LCD_CMD_MASK(ratio, 0b111)) // 0x20, 32

// (18) Set the V5 output voltage electronic volume register
// 0x81, 129
#define CMD_SET_ELECTRONIC_MODE(mod)      (0b10000001) // Electronic volume mode set
#define CMD_SET_ELECTRONIC_REGISTER(mod)  (mod)        // Electronic volume register set

// Double Byte Command
// (19) Set the flashing mode
// Static indicator ON/OFF
#define CMD_STATIC_INDICATOR_OFF          0b10101100 // 0xac, 172
#define CMD_STATIC_INDICATOR_ON           0b10101101 // 0xad, 173
// Static indicator register set
#define STATIC_INDICATOR_OFF              0b00000000 // off
#define STATIC_INDICATOR_BLINKING         0b00000001 // blinking at approximately one second intervals
#define STATIC_INDICATOR_BLINKING_FAST    0b00000010 // blinking at approximately 0.5 second intervals
#define STATIC_INDICATOR_CONSTANTLY_ON    0b00000011 // constantly on

// (21) Command for non-operation
#define CMD_NOP                           0b11100011 // 0xe3,227

// (22) Command for IC test. Do not use this command
#define CMD_TEST(arg)                     0b11110000 | (arg & 0b1111) // 0xf0, 240

#endif // __LCD12864_COMMANDS_H__
