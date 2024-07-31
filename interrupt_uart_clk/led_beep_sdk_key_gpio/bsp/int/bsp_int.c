#include "bsp_int.h"
#include "core_ca7.h"

void int_init()
{
   GIC_init();

   _set_

}
void system_irqtable_init();
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler,void *userparam);
void system_irq_handler(unsigned int gccIar);