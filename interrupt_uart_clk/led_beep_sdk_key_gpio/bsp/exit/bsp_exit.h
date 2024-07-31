#ifndef _BSP_EXIT_H
#define _BSP_EXIT_H
#include "imx6ul.h"

void key_int_init(void);
void gpio1_io18_irqhandler(void); 			/* 中断处理函数 */



#endif