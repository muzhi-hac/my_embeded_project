#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "imx6ul.h"
#include "bsp_gpio.h"
#define BUTTON_PRESS_VALUE 1 
#define BUTTON_UNPRESS_VALUE 0
void key_init();
int key_value_get();


#endif