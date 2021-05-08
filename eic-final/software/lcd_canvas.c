#include "lcd_canvas.h"
#include "lcd.h"
#include "char_data.h"

void lcd_draw_text_6px(uchar x, uchar pageY, char* text) {
    if (!*text) {
        return;
    }
    lcd_select_address(pageY, x);

    char *pText = text;
    while (*pText) {
        for (int i = 0; i < 6; i++) {
            lcd_write_data(CHAR_DATA_6x8[*pText * 6 + i]);
        }
        pText++;
    }
}

void lcd_draw_text_highlight_6px(uchar x, uchar pageY, char* text) {
    if (!*text) {
        return;
    }
    lcd_select_address(pageY, x);

    char *pText = text;
    while (*pText) {
        for (int i = 0; i < 6; i++) {
            lcd_write_data(~CHAR_DATA_6x8[*pText * 6 + i]);
        }
        pText++;
    }
}

void lcd_draw_text_6px_unaligned(uchar x, uchar y, char* text) {
    if (!*text) {
        return;
    }
    uchar y_offset = y % 8;
    if (y_offset != 0) {
        lcd_select_address(y / 8, x);
        char *pText = text;
        while (*pText) {
            for (int i = 0; i < 6; i++) {
                lcd_write_data(CHAR_DATA_6x8[*pText * 6 + i] << (8 - y_offset));
            }
            pText++;
        }
    }

    lcd_select_address(y / 8 + 1, x);

    char *pText = text;
    while (*pText) {
        for (int i = 0; i < 6; i++) {
            lcd_write_data(CHAR_DATA_6x8[*pText * 6 + i] >>  y_offset);
        }
        pText++;
    }
}

void lcd_clear() {
    lcd_clear_range(0, 8, 0, 128);
}

void lcd_clear_range(uint start_page, uint end_page, uint start_x, uint end_x) {
    for (uint i = start_page; i < end_page; i++) {
        lcd_select_address(i, 0);
        for (uint j = start_x; j < end_x; j++) {
            lcd_write_data(0x00);
        }
    }
}

//inline void lcd_draw_point_x(uchar x, uchar y) {
//    if (y >= 64 || x >= 128) {
//        _NOP();
//        return;
//    }
//    uchar block = y / 8;
//    uchar offset = (y % 8);
//    for (int i = 1; i < 8; i++) {
//        lcd_select_address(i, x);
//        lcd_write_data(i == block ? 1 << offset : 0);
//    }
//}

#define SATURATE_TRUNCATE(val) (val < 0 ? 0 : (val > 63 ? 63 : val))

void lcd_draw_vertical_line(uchar x, int8_t y1, int8_t y2, uchar min_page, uchar max_page) {
    y1 = SATURATE_TRUNCATE(y1);
    y2 = SATURATE_TRUNCATE(y2);

    int y1_off = y1 % 8;
    int y2_off = y2 % 8;
    int y1_page = y1 / 8;
    int y2_page = y2 / 8;

    if (y1_page == y2_page) {
        for (int i = min_page; i < y1_page; i++) {
            lcd_select_address(i, x);
            lcd_write_data(0x00);
        }

        lcd_select_address(y1_page, x);
        lcd_write_data((1 << y2_off) - (1 << y1_off));

        for (int i = y2_page + 1; i <= max_page; i++) {
            lcd_select_address(i, x);
            lcd_write_data(0x00);
        }
        return;
    }

    for (int i = min_page; i < y1_page; i++) {
        lcd_select_address(i, x);
        lcd_write_data(0x00);
    }

    lcd_select_address(y1_page, x);
    lcd_write_data(0x100 - (1 << y1_off));

    for (int i = y1_page + 1; i < y2_page; i++) {
        lcd_select_address(i, x);
        lcd_write_data(0xff);
    }

    lcd_select_address(y2_page, x);
    lcd_write_data((1 << y2_off) - 1);

    for (int i = y2_page + 1; i <= max_page; i++) {
        lcd_select_address(i, x);
        lcd_write_data(0x00);
    }
}
