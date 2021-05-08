#ifndef __LCD_CANVAS_H__
#define __LCD_CANVAS_H__

#include "common.h"

void lcd_draw_text_6px(uchar x, uchar y, char* text);

void lcd_draw_text_highlight_6px(uchar x, uchar y, char* text);

void lcd_draw_text_6px_unaligned(uchar x, uchar y, char* text);

void lcd_clear();

void lcd_clear_range(uint start_page, uint end_page, uint start_x, uint end_x);

void lcd_draw_waveform(uchar* samples);

void lcd_draw_point_x(uchar x, uchar y);

void lcd_draw_vertical_line(uchar x, int8_t y1, int8_t y2, uchar min_page, uchar max_page);

#endif //__LCD_CANVAS_H__
