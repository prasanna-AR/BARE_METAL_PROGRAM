#include "headerfile.h"
void usart_tx(char );
char usart_rx();
void rcc();
void gpio();

int main()
{
	char d,data;
        rcc();
        gpio();
	data=usart_rx();
        usart_tx(data);
}
void rcc()
{
        *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);        //IO port A clock enable
        *RCC_APB2ENR = *RCC_APB2ENR | (1<<4);        //USART1 clock enable
}
void gpio()
{

        *GPIOA_MODER   = *GPIOA_MODER   | (1<<19);    //10:Alternate function mode
        *GPIOA_MODER   = *GPIOA_MODER   | (1<<21);    //10:Alternate function mode
        *GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (1<<19);    //GPIO port output speed register fast speed 
        *GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (0<<18);    //GPIO port output speed register fast speed
        *GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (1<<21);    //GPIO port output speed register fast speed 
        *GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (0<<20);    //GPIO port output speed register fast speed
        *GPIOA_AFRH    = *GPIOA_AFRH    | (0x770);    //GPIO alternate function high register usart 1 ->0111 value
}
void usart_tx(char data)
{
        *USART_CR1  =  *USART_CR1 | (1<<3);          //Transmitter enable
        *USART_CR1  =  *USART_CR1 | (0xC0);          //Transmission complete interrupt enable and TXE interrupt enable
        while(!(*USART_SR & (1<<7)));                //untile wait TXE data transfer to the shiftregister (UART_SR)
        *USART_DR   = data;                          //Data register
        while(!(*USART_SR & (1<<6)));                //wait until TC=1
        *USART_SR = *USART_SR & ~(1<<6);             //Status register reset 
}
char usart_rx()
{
	char m;
        *USART_CR1  =  *USART_CR1 & (~1<<12);        //0: 1 Start bit, 8 Data bits, n Stop bit
        *USART_CR1  =  *USART_CR1 | (1<<13);         //USART enable
        *USART_CR2  =  *USART_CR2 | (1<<13);         //10: 2 Stop bits
        *USART_BRR |=  4;                            //fraction part 
        *USART_BRR  =  *USART_BRR | (104<<4);        //mantissa part
	*USART_CR1  =  *USART_CR1 & (~1<<2);
        *USART_CR1  =  *USART_CR1 | (1<<2);          //RE: Receiver enable,1: Receiver is enabled and begins searching for a start bit
	while(!(*USART_SR & (1<<5)));                //wait until RXNE =1, Received data is ready to be read.
	m=*USART_DR;
	*USART_DR = *USART_DR & (~1<<5);             //clear the data register
	return m;
}
