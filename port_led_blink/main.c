//RCC
volatile unsigned int *RCC_CR   = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;

//General-purpose I/Os (GPIO)
volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR   = (volatile unsigned int *)0x40020014;

void rcc();
void general();
void led_blink();

int main()
{
	rcc();
	general();
	while(1)
	{
		led_blink();
	}
}
void rcc()
{
	*RCC_CR = *RCC_CR & (~0x00010000);
	*RCC_CR = *RCC_CR | (1<<16);
	while(*RCC_CR = (*RCC_CR & (1<<17)==0));
	*RCC_CFGR = (*RCC_CFGR & (~0x00000003));
	*RCC_CFGR = (*RCC_CFGR | (1<<0));
	while(!(*RCC_CFGR & (0x00000004))==4);
	*RCC_AHB1ENR =(*RCC_AHB1ENR & (~0x00000001));
	*RCC_AHB1ENR =(*RCC_AHB1ENR | (1<<0));
}
void general()
{
	*GPIOA_MODER = *GPIOA_MODER & (~3<<4);
	*GPIOA_MODER = *GPIOA_MODER | (1<<4);

}
void led_blink()
{
	*GPIOA_ODR   = *GPIOA_ODR  | (1<<2);
}
	
