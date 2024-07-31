#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H
#include "imx6ul.h"
typedef enum _gpio_pin_direction
{
    gpio_input_diection=0U,
    gpio_ouput_diection=1U
    

}gpio_pin_direction;

typedef struct _gpio_pin_config
{
    /* data */
    gpio_pin_direction direction;
    int default_logic;
}gpio_pin_config;

void gpio_init(GPIO_Type *base,int pin,gpio_pin_config *config);
int gpio_pin_read(GPIO_Type *base,int pin);
void gpio_pin_wirte(GPIO_Type *base,int pin,int value);
void gpio_interrupt_enable(GPIO_Type *base,int pin);
void gpio_interrupt_disable(GPIO_Type *base,int pin);
void gpio_clear_interrup_flags(GPIO_Type *base,int pin);




#endif