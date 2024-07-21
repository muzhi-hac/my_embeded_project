#include "bsp_beep.h"

void beep_init(void){
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO05_GPIO1_IO05,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO05_GPIO1_IO05,0x10B0);
    GPIO5->GDIR |=(1<<5);
    GPIO5->DR &=~(1<<5);
}
void beep_switch(int BEEP,int status){
    switch (BEEP)
    {
    case BEEP0:
        if (status==ON)
        {
        GPIO5->DR &=~(1<<5);
        }
        else if (status==OFF)
        {
        GPIO5->DR |=(1<<5);

        }

        
        break;
    
    default:
        break;
    }

}
void beep_on()
{
    GPIO5->DR &=~(1<<5);
}
void beep_off()
{
    GPIO5->DR |=(1<<5);
}