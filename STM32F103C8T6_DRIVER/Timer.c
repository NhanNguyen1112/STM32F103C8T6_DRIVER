
#include "Timer.h"

/*======================================================================================================*/
/*                              TIMER BASE                                                           */
/*======================================================================================================*/
static unsigned int Count=0;

void Function_Test(void)
{
  TogglePin(PORTC,PIN13);
}

void Main_TIM2_BASE(void)
{
  InitClockHSE();

	Enable_Disable_Clock_PortC(Enable);
	SetPinOutput(PORTC,PIN13,0);
	WritePin(PORTC,PIN13,HIGH);

	Init_TIM2();

	while (1)
	{
		TIM2_Function(10000,&Function_Test);
	}
}

void Init_TIM2(void)
{
  unsigned int CR1=0;

  RCC->RCC_APB1ENR |= (1u<<0); /* Enable clock TIM2 */

  TIM2->PSC = 1u; /* Prescaler = (1-1)+1 = 2 -> 72mhz/2=36mhz */

  /* SYSCLK=72Mhz -> 1ms= 36mhz/0.001 */
  TIM2->ARR = (uint16_t)36000u - 1u;

  TIM2->CNT = 0; /* Reset counter */

  TIM2->DIER |= (1<<0); /* UIE: Update interrupt enable */
  TIM2->SR &= ~(1u<<0);  /* UIF: Clear UIF update interrupt flag */

  NVIC->ISER[0] = (1u<<28); /* Enable interupt */

  CR1 &= ~(1u<<4); 	/* DIR set Up counter */
  CR1 |= (1u<<0); 	/* enable counter */
  TIM2->CR1 = CR1;  

  TIM2->EGR = 0x01u; /* UG Re-initialize the counter and generates an update of the registers */
}

void TIM2_Function(const unsigned int MiliSeconds, CALLBACK Function)
{
  if(Count>=MiliSeconds)
	{
		Function();
		Count=0;		
	}
}

void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~(1u<<0);  /* UIF: Clear UIF update interrupt flag */
	Count+=1;
}
/*======================================================================================================*/



/*======================================================================================================*/
/*                              TIMER PWM OUTPUT                                                           */
/*======================================================================================================*/

void Main_TIM2_PWM(void)
{
  InitClockHSE();

  Enable_Disable_Clock_PortA(Enable);
  Init_TIM2_CH1_PA0();

  while(1)
  {
    for( unsigned int i=0; i<=99; i++)
    {
      TIM2->CCR1 = (unsigned int)((i*100u)/100u);
      for( unsigned int d=0; d<=1000; d++);
    }
		
    //TIM2->CCR1 = (unsigned int)((100*100u)/100u);
		// for( unsigned int m=0; m<=500000; m++);
		
    for( unsigned int n=99; n>0; n--)
    {
      TIM2->CCR1 = (unsigned int)((n*100u)/100u);
      for( unsigned int j=0; j<=1000; j++);
    }
    
  }
}

void Init_TIM2_CH1_PA0(void)
{
  unsigned int CR1=0;

  GPIO_A->GPIO_CRL &= ~(0xFu<<0); /* Clear */ 
  GPIO_A->GPIO_CRL |= (3u<<0); 		/* MODE: Output 50Mhz */
  GPIO_A->GPIO_CRL |= (2u<<2); 		/* CNF: ALT PUSH PULL */

  RCC->RCC_APB1ENR |= (1u<<0); /* Enable clock TIM2 */

  TIM2->PSC = 720u - 1u;  					/* Prescaler = 72mhz/72000 = 1.000hz*/
  TIM2->ARR = (uint16_t)100u - 1u; 	/* 10.000Hz */

  TIM2->CNT = 0;

  TIM2->CCMR1 |= (6u<<4); /* OC1M Mode PWM 1 */
  TIM2->CCMR1 |= (1u<<3); /* OC1PE Output preload Disable */

  TIM2->CCR1 = 0;

  TIM2->CCER &= ~(1u<<1); /* CC1P:0 -> OC1 active high */
  TIM2->CCER |= (1u<<0);  /* On - OC1 signal is output on the corresponding output pin */

  CR1 &= ~(1u<<4); 	/* DIR set Up counter */
  CR1 |= (1u<<7);   /* Auto reload enable */
  CR1 |= (1u<<0); 	/* enable counter */
  TIM2->CR1 = CR1;  

  TIM2->EGR = 0x01u; /* UG Re-initialize the counter and generates an update of the registers */
}


/*======================================================================================================*/

