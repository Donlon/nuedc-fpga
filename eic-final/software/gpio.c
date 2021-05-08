
#include <cm3soc/cm3soc.h>

#include <xparameters.h>
#include <xgpio.h>
#include "common.h"
#include "gpio.h"
extern void pin_drive_high(XGpio *xGpio, u16 mask){
    XGpio_DiscreteSet(xGpio,1, mask);
}
extern void pin_drive_low(XGpio *xGpio, u16 mask){
    XGpio_DiscreteClear(xGpio,1, mask);
}