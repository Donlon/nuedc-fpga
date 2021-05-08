#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
//define gpio point high or low

#define GPIO0 0x0001

#define GPIO1 0x0002

#define GPIO2 0x0004

#define GPIO3 0x0008

#define GPIO4 0x0010

#define GPIO5 0x0020

#define GPIO6 0x0040

#define GPIO7 0x0080

#define GPIO8 0x0100

#define GPIO9 0x0200

#define GPIO10 0x0400

#define GPIO11 0x0800

#define GPIO12 0x1000

#define GPIO13 0x2000

#define GPIO14 0x4000

#define GPIO15 0x8000

#define CONST_PI 3.141592653589793238462643

// #define SET_BIT(group, index, val) group##OUT =
#define SET_BIT_HIGH_(group, index) group##OUT |= 1 << (index);
#define SET_BIT_LOW_(group, index) group##OUT &= ~(1 << (index));
#define SWAP_BIT_(group, index) group##OUT ^= 1 << (index);

#define SET_BIT_HIGH(arg) SET_BIT_HIGH_(arg);
#define SET_BIT_LOW(arg) SET_BIT_LOW_(arg);
#define SWAP_BIT(arg) SWAP_BIT_(arg);

#define SET_PORT_DIR(group, enable) group##DIR = (enable);
#define SET_PORT_OUT(group, data) group##OUT = (data);

#define BIT(index) (1 << (index))

// SET_BIT(P1, 6, 1)
// SET_BIT_HIGH(P1, 6)
// SET_BIT_LOW(P1, 6)
// SWAP_BIT(P1, 6)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

#define PIN_DRIVE_LOW_(PORT, PIN) {PORT##OUT &= ~(PIN);}
#define PIN_DRIVE_HIGH_(PORT, PIN) {PORT##OUT |= (PIN);}
#define PIN_DRIVE_LOW(PORT, PIN) PIN_DRIVE_LOW_(PORT, PIN)
#define PIN_DRIVE_HIGH(PORT, PIN) PIN_DRIVE_HIGH_(PORT, PIN)

#define PIN_SET_INPUT_(PORT, PIN) {PORT##DIR &= ~(PIN);}
#define PIN_SET_OUTPUT_(PORT, PIN) {PORT##DIR |= (PIN);}
#define PIN_SET_INPUT(PORT, PIN) PIN_SET_INPUT_(PORT, PIN)
#define PIN_SET_OUTPUT(PORT, PIN) PIN_SET_OUTPUT_(PORT, PIN)

extern void expensionboard_io_init();

// MSP430 intrinsics
void __delay_cycles(unsigned long cycles); // NOLINT
unsigned short __bic_SR_register_on_exit(unsigned short mask); // NOLINT
unsigned short __bis_SR_register_on_exit(unsigned short mask); // NOLINT
unsigned short __get_SR_register_on_exit(void); // NOLINT

#endif // __COMMON_H__
