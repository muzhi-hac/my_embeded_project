#include "bsp_clock.h"
#include "bsp_led.h"
#include "bsp_delay.h"


int main(void){
    clock_init();
    led_init();
    
    while(1){
    led_switch(LED0,OFF);

    delay(500);


    led_switch(LED0,ON);
    delay(500);
    
}
return 0;

}