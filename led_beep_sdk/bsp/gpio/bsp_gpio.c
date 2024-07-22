#include "bsp_gpio.h"
void gpio_init(GPIO_Type *base,int pin,_gpio_pin_config *config)
{

    if (config->direction==1U)
    {
    base->GDIR |= (1<<pin);

    }else if (config->direction==0U)
    {
    base->GDIR &= ~(1<<pin);
    gpio_pin_wirte(base,pin,config->default_logic);
    /*这里相当于原来的默认输出，因为我们不知道默认输出是什么
    比如led 默认输出0时为开，
    beep 默认输出 0 为开
    所以我们需要一个参数来代表默认输出
    只能加上一个config来代表direction和默认输出了*/
    }

}
int gpio_pin_read(GPIO_Type *base,int pin)
{
    return (base->DR>>pin)&(0x1);
}

void gpio_pin_wirte(GPIO_Type *base,int pin,int value)
{
    if (value==0U)
    {
    (base->DR) &= ~(1<<pin);    
    }
    else if (value == 1U)
    {
    (base->DR) |= (1<<pin);
    }

}