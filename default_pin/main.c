// RCC_CONFIG
volatile unsigned int *RCC_CR 		= (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR 	= (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR      = (volatile unsigned int *)0x40023830;

//PORT_CONFIG
volatile unsigned int *GPIOC_MODER      = (volatile unsigned int *)0x40020800;
volatile unsigned int *GPIOC_ODR        = (volatile unsigned int *)0x40020814;

void rcc(void);
void port(void);
void led_blink(void);

int main()
{
	rcc();
	port();
	while(1)
	{
		led_blink();
	}
}

//RCC_CONFIG
void rcc(void)
{
       *RCC_CR = *RCC_CR & (~1<<16);		     //clock control register RCC_CR,16 bit select for HCE pin enable, HCE for high speed external set 0
       *RCC_CR = *RCC_CR | (1<<16);                  //16 bit set for 1
       while((*RCC_CR = *RCC_CR & (1<<17)==0));      //HSE clock ready flag,0: HSE oscillator not, ready status register 
       *RCC_CFGR = *RCC_CFGR & (~0x00000003);	    //system clock source ,select for 1 bit and 2 bit, clock configuration register CFGR
       *RCC_CFGR = *RCC_CFGR | (1<<0);//01:         //HSE oscillator selected as system clock
       while((*RCC_CFGR & 0x00000004)==4);	    //control AHB clock division factor
       *RCC_AHB1ENR = *RCC_AHB1ENR & (~0x00000004);//RCC AHB1 peripheral clock enable register ,3 bit to set 0
       *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<2);       //IO port C clock enable pin selected,3 bit set 1
}
//PORT_CONFIG
void port(void)
{
	*GPIOC_MODER = *GPIOC_MODER | (1<<26);    //General purpose input output mode selected,because c13 pin we using for general purpose
}  
//LED_BLINK
void led_blink(void)
{
		*GPIOC_ODR = *GPIOC_ODR & ~(1<<13); //clear the c13 pin to blink led
}
