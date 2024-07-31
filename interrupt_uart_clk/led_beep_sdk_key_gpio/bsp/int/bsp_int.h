#ifndef _BSP_INT_H
#define _BSP_INT_H
#include "core_ca7.h"
#include "imx6ul.h"
typedef void (*system_irq_handler_t) (unsigned int giccIar, void *param);

typedef struct system_irqhandler
{
    system_irq_handler_t handler;
    void *param;
    /* data */
}system_irqhandler_config;

typedef void (*system_irq_handler_t) (unsigned int giccIar, void *param);
void int_init();
void system_irqtable_init();
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler,void *userparam);
void system_irq_handler(unsigned int gccIar);
void system_default_handler(unsigned int giccIar, void *param);

#endif