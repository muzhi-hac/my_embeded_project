#include "bsp_clock.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_gpio.h"
#include "bsp_key.h"

int main(void){
    clock_init();
    led_init();
    beep_init();
    
    key_init();

    unsigned char LED_STATE =OFF;
    unsigned char BEEP_STATE =OFF;
    while(1){
    if (key_value_get()==BUTTON_PRESS_VALUE)
    {
        LED_STATE!=LED_STATE;
        led_switch(LED0,LED_STATE);
        beep_switch(BEEP0,LED_STATE);
    }
   


    }
   
return 0;
    
}
//  led_off();
