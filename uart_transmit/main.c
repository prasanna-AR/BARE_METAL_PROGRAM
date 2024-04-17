//RCC registers
volatile unsigned int *RCC_AHB1ENR   =  (volatile unsigned int *)0x40023830;
volatile unsigned int *RCC_APB2ENR   =  (volatile unsigned int *)0x40023844;

//GPIO registers
volatile unsigned int *GPIOA_MODER      =  (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_OSPEEDR    =  (volatile unsigned int *)0x40020008;
volatile unsigned int *GPIOA_AFRH       =  (volatile unsigned int *)0x40020024;

//USART 
volatile unsigned int *USART_CR1     =  (volatile unsigned int *)0x4001100C;
volatile unsigned int *USART_CR2     =  (volatile unsigned int *)0x40011010;
volatile unsigned int *USART_BRR     =  (volatile unsigned int *)0x40011008;
volatile unsigned int *USART_DR      =  (volatile unsigned int *)0x40011004;
volatile unsigned int *USART_SR      =  (volatile unsigned int *)0x40011000;

void usart();
void rcc();
void gpio();

int main()
{
	rcc();
	gpio();
	usart();
}
void rcc()
{
	*RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);        //IO port A clock enable
	*RCC_APB2ENR = *RCC_APB2ENR | (1<<4);        //USART1 clock enable
} 
void gpio()
{

	*GPIOA_MODER   = *GPIOA_MODER   | (1<<19);    //10:Alternate function mode
	*GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (1<<19);    //GPIO port output speed register fast speed 
	*GPIOA_OSPEEDR = *GPIOA_OSPEEDR | (0<<18);    //GPIO port output speed register fast speed
	*GPIOA_AFRH    = *GPIOA_AFRH    | (0x70);     //GPIO alternate function high register usart 1 ->0111 value
}
void usart()
{
	*USART_CR1  =  *USART_CR1 & (~1<<12);        //0: 1 Start bit, 8 Data bits, n Stop bit
	*USART_CR1  =  *USART_CR1 | (1<<13);         //USART enable
	*USART_CR2  =  *USART_CR2 | (1<<13);         //10: 2 Stop bits
	*USART_BRR |=  4;                            //fraction part 
	*USART_BRR  =  *USART_BRR | (104<<4);        //mantissa part
	*USART_CR1  =  *USART_CR1 | (1<<3);          //Transmitter enable
	*USART_CR1  =  *USART_CR1 | (0xC0);          //Transmission complete interrupt enable and TXE interrupt enable
	while(!(*USART_SR & (1<<7)));                //untile wait TXE data transfer to the shiftregister (UART_SR)
        *USART_DR   = 'T';                           //Data register
	while(!(*USART_SR & (1<<6)));           //wait until TC=1
	*USART_SR = *USART_SR & ~(1<<6);             //Status register reset 
}
