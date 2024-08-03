#ifndef _BSP_LCD_H
#define _BSP_LCD_H
#define ATK4384 0x4
#include "imx6ul.h"
#define LCD_FRAMEBUF_ADDR 0x89800000
typedef struct lcd_config
{
    unsigned short vspw;
    unsigned short vbpd;
    unsigned short vfpd;
    unsigned short hspw;
    unsigned short hbpd;
    unsigned short hfpd;
    unsigned short height;
    unsigned short width;
    unsigned char pixelsize;
    
    unsigned int framebuffer;
    unsigned int nextframebuffer;

    unsigned int backcolor;
    unsigned int forecolor;

    unsigned int id;
    /* data */
}lcd_config;

extern struct lcd_config lcd_dev;/*全局变量*/
void lcd_init(void);
unsigned short lcd_read_id(void);
void lcdgpio_init(void);
void lcd_reset(void);
void lcd_enable(void);
void lcd_noreset(void);
void lcdclk_init(unsigned char loopDiv, unsigned char prediv, unsigned char div);
void lcd_clear(unsigned int color);
void lcd_drawpoint(unsigned short x, unsigned short y, unsigned int color);
void lcd_readpoint(unsigned short x, unsigned short y, unsigned int *color);

/* 颜色 */
#define LCD_BLUE		  0x000000FF
#define LCD_GREEN		  0x0000FF00
#define LCD_RED 		  0x00FF0000
#define LCD_CYAN		  0x0000FFFF
#define LCD_MAGENTA 	  0x00FF00FF
#define LCD_YELLOW		  0x00FFFF00
#define LCD_LIGHTBLUE	  0x008080FF
#define LCD_LIGHTGREEN	  0x0080FF80
#define LCD_LIGHTRED	  0x00FF8080
#define LCD_LIGHTCYAN	  0x0080FFFF
#define LCD_LIGHTMAGENTA  0x00FF80FF
#define LCD_LIGHTYELLOW   0x00FFFF80
#define LCD_DARKBLUE	  0x00000080
#define LCD_DARKGREEN	  0x00008000
#define LCD_DARKRED 	  0x00800000
#define LCD_DARKCYAN	  0x00008080
#define LCD_DARKMAGENTA   0x00800080
#define LCD_DARKYELLOW	  0x00808000
#define LCD_WHITE		  0x00FFFFFF
#define LCD_LIGHTGRAY	  0x00D3D3D3
#define LCD_GRAY		  0x00808080
#define LCD_DARKGRAY	  0x00404040
#define LCD_BLACK		  0x00000000
#define LCD_BROWN		  0x00A52A2A
#define LCD_ORANGE		  0x00FFA500
#define LCD_TRANSPARENT   0x00000000
#endif