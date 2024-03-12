/* --------------------------------------------------
  | AUTHOR      :R.PRASANNA 		             |
  | DATE        :12-03-2024	                     |
  | FILE NAME   :TIMER_10                            |                                                 
   -------------------------------------------------- */
//RCC_register
volatile unsigned int *RCC_CR      =  (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR    =  (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR =  (volatile unsigned int *)0x40023830;
volatile unsigned int *RCC_APB2ENR =  (volatile unsigned int *)0x40023844;

//General-purpose I/Os (GPIO)
volatile unsigned int *GPIOA_MODER =  (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR   =  (volatile unsigned int *)0x40020014;

//timer_10
volatile unsigned int *TIM10_CR1   =  (volatile unsigned int *)0x40014400;
volatile unsigned int *TIM10_ARR   =  (volatile unsigned int *)0x4001442c;
volatile unsigned int *TIM10_SR    =  (volatile unsigned int *)0x40014410;
volatile unsigned int *TIM10_CNT   =  (volatile unsigned int *)0x40014424;
volatile unsigned int *TIM10_PSC   =  (volatile unsigned int *)0x40014428;

void rcc();
void gpio();
void led();
void timer_10();
 
int main()
{
	rcc();
	gpio();
	while(1)
	{
		led();
	}
}

void rcc()
{
        *RCC_CR = *RCC_CR & (~0x00010000);            //enable of 16-bit set 0
	*RCC_CR = *RCC_CR | (1<<16);                  //enable of 16-bit set 1
	while((*RCC_CR & (1<<17)==0));                //check whether the enable bit is set or not
	*RCC_CFGR = (*RCC_CFGR & (~0x00000003));      //HSE oscillator system clock bit set 0
	*RCC_CFGR = (*RCC_CFGR | (1<<0));             //HSE oscillator selected as system clock
	while(!(*RCC_CFGR & (0x00000004))==4);        //check whether the system clock is set or not
	*RCC_AHB1ENR =(*RCC_AHB1ENR & (~0x00000001)); //IO port A clock enable 1-bit set 0 
	*RCC_AHB1ENR =(*RCC_AHB1ENR | (1<<0));        //IO port A clock enable 1-bit set 1
	*RCC_APB2ENR = *RCC_APB2ENR | (1<<17);        //TIM10 clock enable
}

void gpio()
{
	*GPIOA_MODER = *GPIOA_MODER | (1<<0);         //01:General purpose output mode
}

void led()
{
	*GPIOA_ODR   = *GPIOA_ODR | (1<<0);           //PORT_A select 0bit
	timer_10();                                   //delay
	*GPIOA_ODR   = *GPIOA_ODR & (0<<0);           //PORT_A set 0 in 0bit
	timer_10();                                   //delay
}

void timer_10()
{
	*TIM10_CR1  = *TIM10_CR1 & (0<<0);           //timer_10 counter disable
	*TIM10_CR1  = *TIM10_CR1 | (1<<1);           //enable update disable
	*TIM10_CR1  = *TIM10_CR1 & (0<<2);           //disable the Update request source
	*TIM10_CR1  = *TIM10_CR1 | (1<<7);           //Auto-reload preload enable
	*TIM10_CNT  = 0;                             //counter value upto 1 its count
        *TIM10_PSC  = 1000;                          //prescaler value set 0
	*TIM10_ARR  = 2499;                          //reload value
	*TIM10_CR1  = *TIM10_CR1 | (0x01);           //counter enable
	while(!(*TIM10_SR & (1<<0)==1));             //wait timer status register bit set 1
	*TIM10_SR   = *TIM10_SR & (0<<0);            //reset the update flag bit 0
}
