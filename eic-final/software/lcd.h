#ifndef __LCD_H__
#define __LCD_H__

#include "common.h"

extern int lcd_init();

extern void lcd_write_command(uchar cmd);

extern void lcd_write_data(uchar data);

extern void lcd_select_address(uchar page, uchar column);

#endif // __LCD_H__
