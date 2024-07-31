#include "bsp_int.h"
#include "core_ca7.h"
static system_irqhandler_config irqTable[NUMBER_OF_INT_VECTORS];
unsigned int system_irqhandler_counter = 0;
void int_init()
{
   GIC_Init();

   system_irqtable_init();
   __set_VBAR((uint32_t)0x87800000);

   

}
void system_irqtable_init()
{
   for (int i = 0; i < NUMBER_OF_INT_VECTORS; i++)
   {
      system_register_irqhandler(i, system_default_handler, NULL);
      /* code */
   }
   


   
}
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler,void *userparam)
{

   irqTable[irq].handler = handler;
   irqTable[irq].param = userparam;
}
void system_irq_handler(unsigned int gccIar)
{

   unsigned int intNum = gccIar & 0x3FF;
    if ((intNum == 1023) || (intNum >= NUMBER_OF_INT_VECTORS))
   {
	 	return;
   }
 
   system_irqhandler_counter++;
   irqTable[intNum].handler(gccIar, irqTable[intNum].param);
   system_irqhandler_counter--;




}
void system_default_handler(unsigned int gccIar, void *param)
{
   while(1)
   {

   }


}