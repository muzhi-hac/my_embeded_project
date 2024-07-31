#include "bsp_key.h"
#include "bsp_delay.h"
void key_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18 ,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18 ,0xF080);
    
    gpio_pin_config key_config;
    key_config.direction=0U; 
    
    gpio_init(GPIO1,18,&key_config);
}
int key_value_get()
{
    int press_button =1;/*默认为松开*/
    int button_value=0;
    if ((press_button==1)&&(gpio_pin_read(GPIO1,18)==0))
    {
        delay(100);/*按键消抖*/
        press_button=0;
        if (gpio_pin_read(GPIO1,18)==0)
        {
            press_button=0;
            button_value=1;

        }
    }
    else if (gpio_pin_read(GPIO1,18)==1)
    {
        press_button=1;
        button_value=0;
    }

        return button_value;

}
