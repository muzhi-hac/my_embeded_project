#include "bsp_clock.h"
void clock_init(){
    CCM->CCGR0=0xffffffff;
    CCM->CCGR1=0xffffffff;
    CCM->CCGR2=0xffffffff;
    CCM->CCGR3=0xffffffff;
    CCM->CCGR4=0xffffffff;
    CCM->CCGR5=0xffffffff;
    CCM->CCGR6=0xffffffff;

}