#include "bsp_clock.h"
void clock_init(){
    CCM->CCGR0=0xffffffff;
    CCM->CCGR1=0xffffffff;
    CCM->CCGR2=0xffffffff;
    CCM->CCGR3=0xffffffff;
    CCM->CCGR4=0xffffffff;
    CCM->CCGR5=0xffffffff;
    CCM->CCGR6=0xffffffff;

}
void imx6ul_clock_init(void)
{
     if (((CCM->CCSR>>2)& 0x1)==0)
    {
    CCM->CCSR &= ~(1<<8); /*step_sel*/

    CCM->CCSR |= (1<<2);/*pll1_sw_clk_sel*/
    }
    CCM_ANALOG->PLL_ARM  |=((1<<13)|(88<<0));
    

    CCM->CCSR &= ~(1<<2);/*pll1_sw_clk_sel*/
    CCM->CACRR |= (1<<0);

    /*PFD     NXP 推荐频率值
    PLL2_PFD0 352MHz
    PLL2_PFD1 594MHz
    PLL2_PFD2 400MHz(实际为 396MHz)
    PLL2_PFD3 297MHz
    PLL3_PFD0 720MHz
    PLL3_PFD1 540MHz
    PLL3_PFD2 508.2MHz
    PLL3_PFD3 454.7MHz*/
    unsigned int reg=0;
    reg = CCM_ANALOG->PFD_528;
	reg &= ~(0X3F3F3F3F);		

    reg |= 32<<24;   /* PLL2_PFD3=528*18/32=297Mhz */
    reg |= 24<<16;   /* PLL2_PFD2=528*18/24=396Mhz */
    reg |= 16<<8;    /* PLL2_PFD1=528*18/16=594Mhz */
    reg |= 27<<0;    /* PLL2_PFD0=528*18/27=352Mhz */
	CCM_ANALOG->PFD_528=reg;	

    reg = CCM_ANALOG->PFD_480;
	reg |= 19<<24;				/* PLL3_PFD3=480*18/19=454.74Mhz 	*/
	reg |= 17<<16;				/* PLL3_PFD2=480*18/17=508.24Mhz 	*/
	reg |= 16<<8;				/* PLL3_PFD1=480*18/16=540Mhz		*/
	reg |= 12<<0;				/* PLL3_PFD0=480*18/12=720Mhz	 	*/
	CCM_ANALOG->PFD_480=reg;


    CCM->CBCMR &=~(3<<18);
    CCM->CBCMR |=(1<<18);
    
    CCM->CBCDR &= ~(1<<25); 
    while ((CCM->CDHIPR)&(1<<5));

#if 0
	/* 要先关闭AHB_ROOT_CLK输出，否则时钟设置会出错 */
	CCM->CBCDR &= ~(7 << 10);	/* CBCDR的AHB_PODF清零 */
	CCM->CBCDR |= 2 << 10;		/* AHB_PODF 3分频，AHB_CLK_ROOT=132MHz */
	while(CCM->CDHIPR & (1 << 1));/
* 等待握手完成 */
#endif

	/* 5、设置IPG_CLK_ROOT最小3Mhz，最大66Mhz (boot rom自动设置好了可以不用设置)*/
	CCM->CBCDR &= ~(3 << 8);	/* CBCDR的IPG_PODF清零 */
	CCM->CBCDR |= 1 << 8;		/* IPG_PODF 2分频，IPG_CLK_ROOT=66MHz */
	
	/* 6、设置PERCLK_CLK_ROOT时钟 */
	CCM->CSCMR1 &= ~(1 << 6);	/* PERCLK_CLK_ROOT时钟源为IPG */
	CCM->CSCMR1 &= ~(7 << 0);	/* PERCLK_PODF位清零，即1分频 */
    


}