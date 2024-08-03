#include "bsp_lcd.h"
#include "bsp_gpio.h"
#include "stdio.h"
#include "bsp_delay.h"
struct lcd_config lcd_dev;/*全局变量*/
void lcd_init(void)
{
    unsigned short  idx= 0;
    
    idx = (unsigned short)lcd_read_id();
    printf("lcd id is %x\r\n",idx);
    // return;
    lcdgpio_init();
    lcd_reset();
    delayms(100);
    lcd_noreset();
    if (idx == 4)
    {
        printf("lcd is atk4384 yesyesyes\r\n");
	    lcd_dev.height = 480;	
		lcd_dev.width = 800;
		lcd_dev.vspw = 3;
		lcd_dev.vbpd = 32;
		lcd_dev.vfpd = 13;
		lcd_dev.hspw = 48;
		lcd_dev.hbpd = 88;
		lcd_dev.hfpd = 40;
		lcdclk_init(42, 4, 8);	/* 初始化LCD时钟 31MHz */
    }
    else
    {
        printf("lcd is not atk4384\r\n");
    }
    lcd_dev.pixelsize = 4;
    lcd_dev.framebuffer = LCD_FRAMEBUF_ADDR;
    lcd_dev.nextframebuffer = LCD_FRAMEBUF_ADDR;
    lcd_dev.backcolor = LCD_WHITE;
    lcd_dev.forecolor = LCD_BLACK;
    lcd_dev.id = idx;

    /* 初始化ELCDIF的CTRL寄存器
     * bit [31] 0 : 停止复位
     * bit [19] 1 : 旁路计数器模式
     * bit [17] 1 : LCD工作在dotclk模式
     * bit [15:14] 00 : 输入数据不交换
     * bit [13:12] 00 : CSC不交换
     * bit [11:10] 11 : 24位总线宽度
     * bit [9:8]   11 : 24位数据宽度,也就是RGB888
     * bit [5]     1  : elcdif工作在主模式
     * bit [1]     0  : 所有的24位均有效
	 */
    LCDIF->CTRL =0;
	 LCDIF->CTRL |= (1 << 19) | (1 << 17) | (0 << 14) | (0 << 12) |
	 				(3 << 10) | (3 << 8) | (1 << 5) | (0 << 1);
	/*
     * 初始化ELCDIF的寄存器CTRL1
     * bit [19:16]  : 0X7 ARGB模式下，传输24位数据，A通道不用传输
	 */	
     LCDIF->CTRL1 =0;
	 LCDIF->CTRL1 = 0X7 << 16; 

	 /*
      * 初始化ELCDIF的寄存器TRANSFER_COUNT寄存器
      * bit [31:16]  : 高度
      * bit [15:0]   : 宽度
	  */
     LCDIF->TRANSFER_COUNT  =0;
	LCDIF->TRANSFER_COUNT  = ( lcd_dev.height << 16) | ( lcd_dev.width << 0);

	/*
     * 初始化ELCDIF的VDCTRL0寄存器
     * bit [29] 0 : VSYNC输出
     * bit [28] 1 : 使能ENABLE输出
     * bit [27] 0 : VSYNC低电平有效
     * bit [26] 0 : HSYNC低电平有效
     * bit [25] 0 : DOTCLK上升沿有效
     * bit [24] 1 : ENABLE信号高电平有效
     * bit [21] 1 : DOTCLK模式下设置为1
     * bit [20] 1 : DOTCLK模式下设置为1
     * bit [17:0] : vsw参数
	 */
	LCDIF->VDCTRL0 = 0;	//先清零
	// if(lcdid == ATKVGA) {   //VGA需要特殊处理
	// 	LCDIF->VDCTRL0 = (0 << 29) | (1 << 28) | (0 << 27) |
	// 				 (0 << 26) | (1 << 25) | (0 << 24) |
	// 				 (1 << 21) | (1 << 20) | ( lcd_dev.vspw << 0);
	// } else {
    
		LCDIF->VDCTRL0 = (0 << 29) | (1 << 28) | (0 << 27) |
					 (0 << 26) | (0 << 25) | (1 << 24) |
					 (1 << 21) | (1 << 20) | ( lcd_dev.vspw << 0);
	

	/*
	 * 初始化ELCDIF的VDCTRL1寄存器
	 * 设置VSYNC总周期
	 */  
    LCDIF->VDCTRL1 =0;
	LCDIF->VDCTRL1 =  lcd_dev.height +  lcd_dev.vspw + lcd_dev.vfpd + lcd_dev.vbpd;  //VSYNC周期
	 
	 /*
	  * 初始化ELCDIF的VDCTRL2寄存器
	  * 设置HSYNC周期
	  * bit[31:18] ：hsw
	  * bit[17:0]  : HSYNC总周期
	  */ 
     LCDIF->VDCTRL2 =0;
	LCDIF->VDCTRL2 = (lcd_dev.hspw << 18) | (lcd_dev.width + lcd_dev.hspw + lcd_dev.hfpd + lcd_dev.hbpd);

	/*
	 * 初始化ELCDIF的VDCTRL3寄存器
	 * 设置HSYNC周期
	 * bit[27:16] ：水平等待时钟数
	 * bit[15:0]  : 垂直等待时钟数
	 */ 
    LCDIF->VDCTRL3 = 0;
	LCDIF->VDCTRL3 = ((lcd_dev.hbpd + lcd_dev.hspw) << 16) | (lcd_dev.vbpd + lcd_dev.vspw);

	/*
	 * 初始化ELCDIF的VDCTRL4寄存器
	 * 设置HSYNC周期
	 * bit[18] 1 : 当使用VSHYNC、HSYNC、DOTCLK的话此为置1
	 * bit[17:0]  : 宽度
	 */ 
	LCDIF->VDCTRL4 =0;
	LCDIF->VDCTRL4 = (1<<18) | (lcd_dev.width);

	/*
     * 初始化ELCDIF的CUR_BUF和NEXT_BUF寄存器
     * 设置当前显存地址和下一帧的显存地址
	 */
    LCDIF->CUR_BUF =0;
    LCDIF->NEXT_BUF =0;
	LCDIF->CUR_BUF = (unsigned int)lcd_dev.framebuffer;
	LCDIF->NEXT_BUF = (unsigned int)lcd_dev.framebuffer;


	lcd_enable();			/* 使能LCD 	*/
	delayms(10);
	lcd_clear(LCD_WHITE);	/* 清屏 		*/
    
}

void lcdclk_init(unsigned char loopDiv, unsigned char prediv, unsigned char div)
{
	CCM_ANALOG->PLL_VIDEO_NUM = 0;		
	CCM_ANALOG->PLL_VIDEO_DENOM = 0;	

	
	CCM_ANALOG->PLL_VIDEO =  (2 << 19) | (1 << 13) | (loopDiv << 0); 


	CCM_ANALOG->MISC2 &= ~(3 << 30);
	CCM_ANALOG->MISC2 = 0 << 30;

	CCM->CSCDR2 &= ~(7 << 15);  	
	CCM->CSCDR2 |= (2 << 15);			/* 设置LCDIF_PRE_CLK使用PLL5 */

	
	CCM->CSCDR2 &= ~(7 << 12);		
	CCM->CSCDR2 |= (prediv - 1) << 12;	/* 设置分频  */


	CCM->CBCMR &= ~(7 << 23);					
	CCM->CBCMR |= (div - 1) << 23;				

	/* 设置LCD时钟源为LCDIF_PRE时钟 */
	CCM->CSCDR2 &= ~(7 << 9);					/* 清除原来的设置		 	*/
	CCM->CSCDR2 |= (0 << 9);					/* LCDIF_PRE时钟源选择LCDIF_PRE时钟 */
}

unsigned short lcd_read_id(void)
{   
    unsigned char idx=0;
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_GPIO3_IO03,0);
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_GPIO3_IO03,0x10B0);
/*R7(M0) G7(M1) B7(M2)*/
    gpio_pin_config_t lcd_config;
    
    lcd_config.direction = kGPIO_DigitalOutput;
    lcd_config.outputLogic = 1;
    gpio_init(GPIO3,3,&lcd_config);

    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_GPIO3_IO20, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_GPIO3_IO28, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_GPIO3_IO12, 0);

    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_GPIO3_IO20,0xf080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_GPIO3_IO28,0xf080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_GPIO3_IO12,0xf080);
    lcd_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO3,12,&lcd_config);

    gpio_init(GPIO3,20,&lcd_config);
    gpio_init(GPIO3,28,&lcd_config);
    idx |=(unsigned char) gpio_pinread(GPIO3,28);/*M0*/
    idx |= (unsigned char)gpio_pinread(GPIO3,20)<<1;/*M1*/
    idx |=(unsigned char)gpio_pinread(GPIO3,12)<<2; /*M2*/

    if (idx == 4)
    {
        
        printf("LCD is ATK4384\r\n");
    }
    else
    {
        printf("LCD is NO ATK4384\r\n");
    }
    return idx;
};

void lcdgpio_init(void)
{
	gpio_pin_config_t gpio_config;
	


	IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07,0);
	
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15,0);

	IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16,0);
	
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23,0);

	IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0);

	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08,0);			/* 背光BL引脚      */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);
					

	/* 2、配置LCD IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 0 默认22K上拉
	 *bit [13]: 0 pull功能
	 *bit [12]: 0 pull/keeper使能 
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 111 驱动能力为R0/7
	 *bit [0]: 1 高转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23,0xB9);

	IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0xB9);

	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08,0xB9);	/* 背光BL引脚 		*/

	gpio_config.direction = kGPIO_DigitalOutput;			/* 输出 			*/
	gpio_config.outputLogic = 1; 							/* 默认关闭背光 */
	gpio_init(GPIO1, 8, &gpio_config);						/* 背光默认打开 */
	gpio_pinwrite(GPIO1, 8, 1);								/* 打开背光     */
}


void lcd_reset(void)
{
    LCDIF->CTRL |= 1<<31;

}
void lcd_noreset(void)
{

    LCDIF->CTRL &= ~(1<<31);
}
void lcd_enable(void)
{
    LCDIF->CTRL |= 1<<0;
}

void lcd_clear(unsigned int color)
{
    unsigned int i = 0;
    unsigned int *Address=(unsigned int *)lcd_dev.framebuffer;
    unsigned int num=lcd_dev.height*lcd_dev.width;

    for (i = 0; i < num; i++)
    {
        Address[i] = color;
    }
}
void lcd_drawpoint(unsigned short x, unsigned short y, unsigned int color)
{
    unsigned int *Address = (unsigned int *)lcd_dev.framebuffer;
    Address[y * lcd_dev.width + x] = color;

}
void lcd_readpoint(unsigned short x, unsigned short y, unsigned int *color)
{
    unsigned int *Address = (unsigned int *)lcd_dev.framebuffer;
    *color = Address[y * lcd_dev.width + x];
}