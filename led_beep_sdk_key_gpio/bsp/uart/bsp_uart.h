#ifndef _BSP_UART_H
#define _BSP_UART_H
#include "imx6ul.h"
void uart_init();
void uart_io_init();

void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_software_reset(UART_Type *base);
void uart_setbaudrate(UART_Type *base,
                    unsigned int baud,
                    unsigned int clock_hz
                        );
void putc(unsigned char c);
void puts(char *str);
unsigned char getc();

#endif