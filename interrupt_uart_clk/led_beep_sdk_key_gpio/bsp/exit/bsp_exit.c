#include "bsp_exit.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_beep.h"

void key_int_init(void)
{
    gpio_pin_config key_config;
    key_config.direction=0U;
    key_config.default_logic=1U;
    gpio_init(GPIO1,18,&key_config);	/* 初始化IO18 */
    
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18 ,0);	/* 设置复用 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18 ,0xF080);	/* 设置电气属性 */
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,gpio1_io18_irqhandler,NULL);	

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);			
   gpio_interrupt_enable(GPIO1_Combined_16_31_IRQn,18);	/* 使能GPIO1_IO18中断 */


}
void gpio1_io18_irqhandler(void)
{
    static unsigned char state=0;
    delay(10);
    if (gpio_pin_read(GPIO1,18)==0)
    {
        state=!state;
        beep_switch(BEEP0,state);
    }
    gpio_clear_interrup_flags(GPIO1,18);


} 			/* 中断处理函数 */