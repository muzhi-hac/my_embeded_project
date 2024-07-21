#include "main.h"
#include "bsp_clock.h"
#include "bsp_led.h"
#include "bsp_delay.h"


int main(){
    clock_init();
    led_init();
while(1)
{
    delay(500);
    led_on();

    delay(500);
    led_off();
}


}