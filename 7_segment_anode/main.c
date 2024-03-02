//RCC registers
volatile unsigned int *RCC_CR 	    = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR	    = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR  = (volatile unsigned int *)0x40023830;

//General-purpose I/Os (GPIO)
volatile unsigned int *GPIOA_MODER  = (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR    = (volatile unsigned int *)0x40020014;

//systick_timer
volatile unsigned int *STK_CTRL     = (volatile unsigned int *)0xE000E010;
volatile unsigned int *STK_LOAD     = (volatile unsigned int *)0xE000E014;

void rcc(void);
void port(void);
void segment_anode(void);
void delay(void);

int main()
{
	rcc();
	port();
	while(1)
	{
		segment_anode();
	}
}
void delay()
{
	  
	*STK_CTRL  = *STK_CTRL | (0x05);              //Counter enable and Clock source selection
	*STK_LOAD  = 10999999;                   	      //SysTick reload value register
	while(!(*STK_CTRL & (1<<16)));                //check the reload value comes 0,using countflag=1
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
}
void port()
{      
	for(int i=0;i<8;i++)
	{
	   int j=i+i;                               
	  *GPIOA_MODER = *GPIOA_MODER | (1<<j);      //01:General purpose output mode
	}
}
void segment_anode()
{
	// 0 
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000C0);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000ff);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//1
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000F9);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//2
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000A4);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//3	
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000B0);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//4
	*GPIOA_ODR  = *GPIOA_ODR  | (0x00000099);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//5
	*GPIOA_ODR  = *GPIOA_ODR  | (0x00000092);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//6
	*GPIOA_ODR  = *GPIOA_ODR  | (0x00000082);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//7	
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000F8);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//8
	*GPIOA_ODR  = *GPIOA_ODR  | (0x00000080);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	//9	
	*GPIOA_ODR  = *GPIOA_ODR  | (0x00000090);
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
	*GPIOA_ODR  = *GPIOA_ODR  | (0x000000FF);      //port a to set 1
	delay();
	*GPIOA_ODR  = *GPIOA_ODR  & (0x00000000);      //port a to set 0
}







