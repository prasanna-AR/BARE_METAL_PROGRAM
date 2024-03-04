/* --------------------------------------------------
  | AUTHOR      :R.PRASANNA 		             |
  | DATE        :04-03-2024	                     |
  | FILE NAME   :STEPPER_MOTOR 	                     |
  | DESCRIPTION :TO_ROTATE_STEPPER_MOTOR 	     |                                                 
   -------------------------------------------------- */
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

unsigned int value[] = {0x07,0x03,0x0b,0x09,0x0d,0x0c,0x0e,0x06};  //stepper motor rotate value

void rcc(void);
void port(void);
void stepper_motor(void);
void delay(void);

int main()
{
	rcc();
	port();
	while(1)
	{
		stepper_motor();
	}
}

void delay()
{

    *STK_CTRL  = *STK_CTRL | (0x05);       //Counter enable and Clock source selection
    *STK_LOAD  = 174999;                 //SysTick reload value register
    while(!(*STK_CTRL & (1<<16)));         //check the reload value comes 0,using countflag=1
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
	for(int i=0;i<4;i++)
	{
	   int j=i+i;
	  *GPIOA_MODER = *GPIOA_MODER | (1<<j);      //01:General purpose output mode
	}
}
void stepper_motor()
{
	for(int i=0;i<50;i++)
	{
		for(int j=0;j<7;j++)
		{
			*GPIOA_ODR  = *GPIOA_ODR | (value[j]);   //stepper motor rotate
			delay();                                 //delay
			*GPIOA_ODR  = *GPIOA_ODR & (0x00000000); //set 0 to port A
			delay();
		}
	}
}
