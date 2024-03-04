/* --------------------------------------------------
  | AUTHOR      :R.PRASANNA 		             |
  | DATE        :01-03-2024	                     |
  | FILE NAME   :LED_MATRIX	                     |                                                 
   -------------------------------------------------- */
//RCC
volatile unsigned int *RCC_CR   = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;

//General-purpose I/Os (GPIO)
volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;
volatile unsigned int *GPIOA_ODR   = (volatile unsigned int *)0x40020014;
volatile unsigned int *GPIOB_ODR   = (volatile unsigned int *)0x40020414;

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
	*RCC_AHB1ENR =(*RCC_AHB1ENR & (~0x00000002));
	*RCC_AHB1ENR =(*RCC_AHB1ENR | (1<<1));
}
void general()
{      
	for(int i=0;i<20;i++)
	{
	   int j=i+i;
	  *GPIOA_MODER = *GPIOA_MODER | (1<<j);
	  *GPIOB_MODER = *GPIOB_MODER | (1<<j);
	}
}
void led_blink()
{
	
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);        // set the PORT A is 0
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);        // set the PORT B is 0
	for(int i=0;i<9;i++)
	{	
		*GPIOA_ODR   = *GPIOA_ODR  | (1<<0);
		*GPIOB_ODR   = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=0;i<8;i++)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<9);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=8;i>0;i--)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<7);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=7;i>0;i--)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<0);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=1;i<8;i++)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<1);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}
	
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=1;i<6;i++)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<8);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=8;i>1;i--)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<6);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=6;i>1;i--)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<1);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}


	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=1;i<7;i++)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<2);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}


	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=2;i<5;i++)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<7);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}


	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=7;i>2;i--)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<5);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}


	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=5;i>3;i--)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<2);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}


	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=2;i<6;i++)
	{
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<3);
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

       	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);     
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);
	for(int i=3;i<5;i++)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<6);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);  
	*GPIOB_ODR  = *GPIOB_ODR  & (0x00000000);     
	for(int i=4;i<5;i++)
	{
		*GPIOB_ODR  = *GPIOB_ODR  | (1<<5);
		*GPIOA_ODR  = *GPIOA_ODR  | (1<<i);
		for(int j=0;j<300000;j++);
	}

}

