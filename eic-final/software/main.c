#include <cm3soc/cm3soc.h>
#include "lcd.h"
#include "lcd_canvas.h"
#include <xparameters.h>
#include <xgpio.h>

int value = 1;

XGpio gpio;   /* The driver instance for GPIO Device 0 */

void paint_header() {
    lcd_draw_text_6px(128 - 8 * 6 - 8, 0, "2021F102");
}

int main() {
    int status = lcd_init();
    lcd_clear();
    if (status != XST_SUCCESS) {
        while (1);
    }
    while (1){
      paint_header();
    }
    return 0;
}

