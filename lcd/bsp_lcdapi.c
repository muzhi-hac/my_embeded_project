#include "bsp_lcdapi.h"
// #include "bsp_lcd.h"
#include "font.h" 
void lcd_draw_hline(unsigned short x1, unsigned short x2, unsigned short y, unsigned int color)
{
    unsigned short x = 0;
    unsigned int *Address = (unsigned int *)lcd_dev.framebuffer;
    for (x = x1; x <= x2; x++)
    {
        Address[y * lcd_dev.width + x] = color;
    }
};
void lcd_draw_vline(unsigned short x, unsigned short y1, unsigned short y2, unsigned int color)
{
    unsigned short y = 0;
    unsigned int *Address = (unsigned int *)lcd_dev.framebuffer;
    for (y = y1; y <= y2; y++)
    {
        Address[y * lcd_dev.width + x] = color;
    }
};
void lcd_draw_rectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned int color)
{
    lcd_draw_hline(x1, x2, y1, color);
    lcd_draw_hline(x1, x2, y2, color);
    lcd_draw_vline(x1, y1, y2, color);
    lcd_draw_vline(x2, y1, y2, color);
};
void lcd_draw_circle(unsigned short x, unsigned short y, unsigned short r, unsigned int color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);
    while (a <= b)
    {
        lcd_drawpoint(x - b, y - a, color);
        lcd_drawpoint(x + b, y - a, color);
        lcd_drawpoint(x - a, y + b, color);
        lcd_drawpoint(x - b, y + a, color);
        lcd_drawpoint(x + a, y - b, color);
        lcd_drawpoint(x + b, y + a, color);
        lcd_drawpoint(x + a, y + b, color);
        lcd_drawpoint(x - a, y - b, color);
        a++;
        if (di < 0)
        {
            di += 4 * a + 6;
        }
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}


void lcd_fill(unsigned short sx,unsigned short sy,unsigned short ex,unsigned short ey,unsigned int color)
{
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned int *Address = (unsigned int *)lcd_dev.framebuffer;
    for (y = sy; y <= ey; y++)
    {
        for (x = sx; x <= ex; x++)
        {
            Address[y * lcd_dev.width + x] = color;
        }
    }
};

void lcd_showchar(unsigned     short x, unsigned short y,
				      unsigned char num, unsigned char size, 
				      unsigned char mode)
{  							  
    unsigned char  temp, t1, t;
	unsigned short y0 = y;
	unsigned char csize = (size / 8+ ((size % 8) ? 1 : 0)) * (size / 2);	/* 得到字体一个字符对应点阵集所占的字节数	 */	
 	num = num - ' ';  	/*得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）  */
	for(t = 0; t < csize; t++)
	{   
		if(size == 12) temp = asc2_1206[num][t]; 		/* 调用1206字体 */
		else if(size == 16)temp = asc2_1608[num][t];	/* 调用1608字体 */
		else if(size == 24)temp = asc2_2412[num][t];	/* 调用2412字体 */
		else if(size == 32)temp = asc2_3216[num][t];	/* 调用3216字体 */
		else return;									/* 没有的字库 		*/
		for(t1 = 0; t1 < 8; t1++)
		{			    
			if(temp & 0x80)lcd_drawpoint(x, y,   lcd_dev.forecolor);
			else if(mode==0)lcd_drawpoint(x, y,   lcd_dev.backcolor);
			temp <<= 1;
			y++;
			if(y >=   lcd_dev.height) return;			/* 超区域了 */	
			if((y - y0) == size)
			{
				y = y0;
				x++;
				if(x >=   lcd_dev.width) return;		/* 超区域了 */
				break;
			}
		}  	 
	}  		    	   	 	  
} 

/*
 * @description	: 计算m的n次方
 * @param - m	: 要计算的值
 * @param - n	: n次方
 * @return 		: m^n次方.
 */
unsigned int lcd_pow(unsigned char m,unsigned char n)
{
	unsigned int result = 1;	 
	while(n--) result *= m;    
	return result;
}

/*
 * @description	: 显示指定的数字，高位为0的话不显示
 * @param - x	: 起始坐标点X轴。
 * @param - y	: 起始坐标点Y轴。
 * @param - num	: 数值(0~999999999)。
 * @param - len : 数字位数。
 * @param - size: 字体大小
 * @return 		: 无
 */
void lcd_shownum(unsigned     short x, 
					 unsigned short y, 
					 unsigned int num, 
					 unsigned char len,
					 unsigned char size)
{         	
	unsigned char  t, temp;
	unsigned char  enshow = 0;						   
	for(t = 0; t < len; t++)
	{
		temp = (num / lcd_pow(10, len - t - 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			if(temp == 0)
			{
				lcd_showchar(x + (size / 2) * t, y, ' ', size, 0);
				continue;
			}else enshow = 1; 	 
		}
	 	lcd_showchar(x + (size / 2) * t, y, temp + '0', size, 0); 
	}
} 

/*
 * @description		: 显示指定的数字，高位为0,还是显示
 * @param - x	 	: 起始坐标点X轴。
 * @param - y	 	: 起始坐标点Y轴。
 * @param - num		: 数值(0~999999999)。
 * @param - len 	: 数字位数。
 * @param - size	: 字体大小
 * @param - mode	: [7]:0,不填充;1,填充0.
 * 					  [6:1]:保留
 *					  [0]:0,非叠加显示;1,叠加显示.
 * @return 	 		: 无
 */
void lcd_showxnum(unsigned     short x, unsigned short y, 
					  unsigned int num, unsigned char len, 
					  unsigned char size, unsigned char mode)
{  
	unsigned char t, temp;
	unsigned char enshow = 0;						   
	for(t = 0; t < len; t++)
	{
		temp = (num / lcd_pow(10, len - t- 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			if(temp == 0)
			{
				if(mode & 0X80) lcd_showchar(x + (size / 2) * t, y, '0', size, mode & 0X01);  
				else  lcd_showchar(x + (size / 2) * t, y , ' ', size, mode & 0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	lcd_showchar( x + (size / 2) * t, y, temp + '0' , size , mode & 0X01); 
	}
} 

/*
 * @description		: 显示一串字符串
 * @param - x		: 起始坐标点X轴。
 * @param - y		: 起始坐标点Y轴。
 * @param - width 	: 字符串显示区域长度
 * @param - height	: 字符串显示区域高度
 * @param - size	: 字体大小
 * @param - p		: 要显示的字符串首地址
 * @return 			: 无
 */
void lcd_show_string(unsigned short x,unsigned short y,
						  unsigned short width,unsigned short height,
						  unsigned char size,char *p)
{         
	unsigned char x0 = x;
	width += x;
	height += y;
    while((*p <= '~') &&(*p >= ' '))		/* 判断是不是非法字符! */ 
    {       
        if(x >= width) {x = x0; y += size;}
        if(y >= height) break;				/* 退出 */
        lcd_showchar(x, y, *p , size, 0);
        x += size / 2;
        p++;
    }  
}


