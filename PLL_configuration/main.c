/* --------------------------------------------------
  | AUTHOR      :R.PRASANNA 		             |
  | DATE        :06-03-2024	                     |
  | FILE NAME   :PLL configuration 	             |
   -------------------------------------------------- */
//RCC_CR
volatile unsigned int *RCC_CR       =  (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_PLLCFGR  =  (volatile unsigned int *)0x40023804;
volatile unsigned int *RCC_AHB1ENR  =  (volatile unsigned int *)0x40023830;

//GPIO registers
volatile unsigned int *GPIOA_MODER  =  (volatile unsigned int *)0x40020000;
volatile unsigned int *GPIOA_ODR    =  (volatile unsigned int *)0x40020014;

void rcc(void);
void gpio(void);
void led_blink(void);
int main()
{
	rcc();
	gpio();
	while(1)
	{
		led_blink();
	}
}

//RCC_CONFIG
void rcc(void)
{
       *RCC_CR = *RCC_CR & (~1<<24);		     //Main PLL (PLL) enable,pin set 0
       *RCC_CR = *RCC_CR | (1<<24);                  // Main PLL (PLL) enable
         while((*RCC_CR & (1<<25)==0));              //Main PLL enable pin is ready are not check

       *RCC_PLLCFGR = *RCC_PLLCFGR | (1<<0);         //set of pll M value
       *RCC_PLLCFGR = *RCC_PLLCFGR | (1<<2);         //set of pll M value
       *RCC_PLLCFGR = *RCC_PLLCFGR | (1<<9);         //set of pll N value 
       *RCC_PLLCFGR = *RCC_PLLCFGR | (0<<16);        //set of pll P value
       *RCC_PLLCFGR = *RCC_PLLCFGR | (0<<17);        //set of pll P value

       //*RCC_AHB1ENR = *RCC_AHB1ENR & (0<<0);         //RCC AHB1 peripheral clock enable register ,0 bit to set 0
       *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);         //IO port A clock enable pin selected,0 bit set 1
}
//GPIO general_purpose_input_output_mode
void gpio(void)
{
	*GPIOA_MODER = *GPIOA_MODER | (1<<0);        //General purpose input output mode selected,because mod_0-pin we using for general purpose
}
//LED_BLINK
void led_blink(void)
{
	*GPIOA_ODR = *GPIOA_ODR | (1<<0);    //set 1 to PORTA_0-pin to blink led
}
