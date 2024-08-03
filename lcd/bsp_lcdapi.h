#ifndef _BSP_LCDAPI_H
#define _BSP_LCDAPI_H
#include "imx6ul.h"
#include "bsp_lcd.h"    
void lcd_fill(unsigned short sx,unsigned short sy,unsigned short ex,unsigned short ey,unsigned int color);
void lcd_draw_hline(unsigned short x1, unsigned short x2, unsigned short y, unsigned int color);
void lcd_draw_vline(unsigned short x, unsigned short y1, unsigned short y2, unsigned int color);
void lcd_draw_rectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned int color);
void lcd_draw_circle(unsigned short x, unsigned short y, unsigned short r, unsigned int color);
void lcd_showchar(unsigned     short x,unsigned short y,unsigned char num,unsigned char size, unsigned char mode);
unsigned int lcd_pow(unsigned char m,unsigned char n);
void lcd_shownum(unsigned short x, unsigned short y, unsigned int num, unsigned char len,unsigned char size);
void lcd_showxnum(unsigned short x, unsigned short y, unsigned int num, unsigned char len, unsigned char size, unsigned char mode);
void lcd_show_string(unsigned short x,unsigned short y,
unsigned short width, unsigned short height, unsigned char size,char *p);
#endif