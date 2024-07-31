#include "bsp_clock.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"
#include "bsp_int.h"
int main(void){
    int_init();
    imx6ul_clock_init();
    clock_init();
    led_init();
    beep_init();
    
    key_init();

    unsigned char LED_STATE =OFF;
    unsigned char BEEP_STATE =OFF;
    while(1){
    if (key_value_get())
    {
        delay(100);
        switch (key_value_get())
        {
            case BUTTON_PRESS_VALUE :
            led_switch(LED0,LED_STATE);
            beep_switch(BEEP0,LED_STATE);
            LED_STATE =!LED_STATE;
            break;
        }

       
    }
   


    }
   
return 0;
    
}
//  led_off();
