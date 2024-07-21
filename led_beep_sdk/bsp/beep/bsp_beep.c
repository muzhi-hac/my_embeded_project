#include "bsp_beep.h"

void beep_init(void){
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10B0);
    GPIO5->GDIR |=(1<<1);
    GPIO5->DR &=~(1<<1);
}
void beep_switch(int BEEP,int status){
    switch (BEEP)
    {
    case BEEP0:
        if (status==ON)
        {
             GPIO5->DR &=~(1<<1);
        }
        else if (status==OFF)
        {
            GPIO5->DR |=(1<<1);

        }

        
        break;
    
    
    }

}
void beep_on()
{
    GPIO5->DR &=~(1<<1);
}
void beep_off()
{
    GPIO5->DR |=(1<<1);
}