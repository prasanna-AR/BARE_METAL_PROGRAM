//RCC_CONFIG
volatile unsigned int *RCC_CR 		= (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR 	= (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR      = (volatile unsigned int *)0x40023830;

//General-purpose I/Os (GPIO)
volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR   = (volatile unsigned int *)0x40020014;

//systick_timer
volatile unsigned int *STK_CTRL         = (volatile unsigned int *)0xE000E010;
volatile unsigned int *STK_LOAD         = (volatile unsigned int *)0xE000E014;

void rcc(void);
void port(void);
void led_blink(void);
void delay(void);

int main()
{
	rcc();
	port();
	while(1)
	{
		led_blink();
	}
}
//delay
void delay()
{
	        *STK_CTRL  = *STK_CTRL | (0x05);
		*STK_LOAD  = 249999;
		while(!(*STK_CTRL & (1<<16)));
}
//RCC_CONFIG
void rcc(void)
{
       *RCC_CR = *RCC_CR & (~0x00010000);//clock control register RCC_CR,16 bit select for HCE pin enable, HCE for high speed external set 0
       *RCC_CR = *RCC_CR | (1<<16);                  //16 bit set for 1
       while((*RCC_CR & (1<<17))==0);         //HSE clock ready flag,0: HSE oscillator not, ready status register 
       *RCC_CFGR = *RCC_CFGR & (~0x00000003);	    //system clock source ,select for 1 bit and 2 bit, clock configuration register CFGR
       *RCC_CFGR = *RCC_CFGR | (1<<0);//01:         //HSE oscillator selected as system clock
       while(!(*RCC_CFGR & 0x00000004)==4);	    //control AHB clock division factor
       *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);       //IO port A clock enable pin selected, 1 bit set 1
}
//PORT_CONFIG
void port(void)
{
	*GPIOA_MODER = *GPIOA_MODER & (~3<<0);     //to set 0 in bit 1,bit 2
	*GPIOA_MODER = *GPIOA_MODER | (1<<0);      //to set 1 in bit 1

}  
//LED_BLINK
void led_blink(void)
{
		*GPIOA_ODR   = *GPIOA_ODR  | (1<<0);   //selected A2 pin to input trun on ,set 1
		delay();
		*GPIOA_ODR   = *GPIOA_ODR  & (0<<0);   //selected A2 pin to turn off ,set 0
		delay();
}
