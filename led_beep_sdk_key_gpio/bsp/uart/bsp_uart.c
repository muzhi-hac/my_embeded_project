#include "bsp_uart.h"
void uart_init()
{
    uart_io_init();
    /*uart_UCR1
    ADBR(bit 14) :Enables automatic detection of the baud rate.
    UARTEN(bit 0): enable uart
    config the regitser URXD and the UTXD
*/    
    uart_disable(UART1);
    uart_software_reset(UART1);

    UART1->UCR1=0;
    UART1->UCR1&=((1<<14));
    /*
    IRTS(bit14): When it is 0, use the RTS pin function, when it is 1, ignore the RTS pin.
    PREN (bit8): Parity check enable bit, when it is 0, parity check is turned off, when it is 1, parity check is enabled.
    PROE (bit7): Parity check mode bit. After turning on parity check, if this bit is 0, even parity will be used.
    After verification, if this bit is 1, odd verification can be performed.
    STOP (bit6): The number of stop bits. When it is 0, it is 1 stop bit, and when it is 1, it is 2 stop bits.
    WS(bit5): Data bit length, when it is 0, 7-bit data bits are selected, and when it is 1, 8-bit data bits are selected.
    TXEN (bit2): Transmit enable bit. When it is 0, it turns off the UART transmission function. When it is 1, it turns on the UART.
    sending function.
    RXEN (bit1): Receive enable bit. When it is 0, it turns off the UART receiving function. When it is 1, it turns on the UART.
    receiving function.
    SRST (bit0): software reset. When it is 0, the software resets the UART. When it is 1, it means the reset is completed. reset
    After completion, this bit will be automatically set to 1, indicating that the reset is completed. This bit can only be written to 0, writing 1 will be ignored.
    */
    UART1->UCR2 |=((1<<15)|(1<<5)|(1<<1)|(0<<1));
    UART1->UCR3 |=((1<<2));

/*UARTx_UFCR(UART FIFO Control Register) 
UARTx_UBIR(UART BRM Incremental Register)
UARTx_UBMR(UART BRM Modulator Register)
When enabeling the automatic baud rate detection feature, these registers can config the baud rate.
UCFR (bit 9-7 RFDIV)
Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
UBMR = 3124
 UBIR = 71
 因此波特率= 80000000/(16 * (3124+1)/(71+1))
 = 80000000/(16 * 3125/72)
 = (80000000*72) / (16*3125)
 = 115200
*/
UART1->UFCR =5<<7;
UART1->UBMR=3124;
UART1->UBIR=71;
//快速设置波特率
#if 0
uart_setbaudrate(UART1, 115200, 80000000); /* 设置波特率 */
 #endif

uart_enable(UART1);
    
}
void uart_io_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX,0x10B0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX,0x10B0);

    
}

void uart_disable(UART_Type *base)
{
    base->UCR1 &=~(1<<0);
}
void uart_enable(UART_Type *base)
{
    base->UCR1 |=(1<<0);

}
void uart_software_reset(UART_Type *base)
{
    base->UCR2 &=~(1<<0);
    while (( base->UCR2 &=0x1)==0);

}
void uart_setbaudrate(UART_Type *base,
                    unsigned int baud,
                    unsigned int clock_hz
                        );
void putc(unsigned char c);
void puts(char *str);
unsigned char getc();