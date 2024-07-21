#include "bsp_clock.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"

int main(void){
    clock_init();
    led_init();
    beep_init();

    while(1){
    led_switch(LED0,OFF);
    beep_switch(BEEP0,OFF);
    delay(500);


    led_switch(LED0,ON);
     beep_switch(BEEP0,OFF);
    delay(500);
    
}
return 0;
//  led_off();
}