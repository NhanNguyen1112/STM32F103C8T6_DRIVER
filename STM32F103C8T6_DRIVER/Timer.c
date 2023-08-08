
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
	SetPinOutput(PORTC,PIN13,PushPull);
	WritePin(PORTC,PIN13,LOW);

	Init_TIM2_Delay();

	while (1)
	{
    Function_Test();
    Delay_TIM2_us(5);
    //Delay_TIM2_ms(5000);
	}
}

void Init_TIM2_Delay(void)
{
  unsigned int CR1=0;

  RCC->RCC_APB1ENR |= (1u<<0); /* Enable clock TIM2 */

  TIM2->PSC = 0u; /* Prescaler = (0-1)+1 = 0 -> 72mhz/0 = 72mhz */

  /* SYSCLK=72Mhz -> ARR=1us -> 72.000.000*0,000001= 72 tick */
  TIM2->ARR = 72u;

  TIM2->CNT = 0; /* Reset counter */

  TIM2->DIER |= (1<<0);  /* UIE: Update interrupt enable */
  TIM2->SR &= ~(1u<<0);  /* UIF: Clear UIF update interrupt flag */

  NVIC_ClearPendingFlag(TIM2_IRQn); /* Clear Pending */
  NVIC_EnableInterrupt(TIM2_IRQn); 	/* Enable interupt */

  CR1 &= ~(1u<<4); 	/* DIR set Up counter */
  CR1 |= (1u<<0); 	/* enable counter */
  TIM2->CR1 = CR1;  

  TIM2->EGR = 0x01u; /* UG Re-initialize the counter and generates an update of the registers */
}

void Delay_TIM2_ms(const unsigned int MiliSeconds)
{
  unsigned int MicroSeconds = MiliSeconds*1000;
  while(Count<=MicroSeconds);
  Count=0;
}

void Delay_TIM2_us(const unsigned int MicroSeconds)
{
  while(Count<=(MicroSeconds-1));
  Count=0;
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
  SetPinOutput(PORTA,PIN0,Alternate_PushPull);
	
  Init_TIM2_PWM_CH1_PA0();

  while(1)
  {
    for( unsigned int i=0; i<=99; i++)
    {
      TIM2_PWM_OUTPUT(i);
      for( unsigned int d=0; d<=100000; d++);
    }
		
    for( unsigned int n=99; n>0; n--)
    {
      TIM2_PWM_OUTPUT(n);
      for( unsigned int j=0; j<=100000; j++);
    }
    
  }
}

void Init_TIM2_PWM_CH1_PA0(void)
{
  unsigned int CR1=0;

  RCC->RCC_APB1ENR |= (1u<<0); /* Enable clock TIM2 */

  TIM2->PSC = PSC_TIM2_PWM - 1u;  					/* Prescaler = (72.000.000hz/1000hz)/100 = 720hz*/
  TIM2->ARR = (uint16_t)(ARR_TIM2_PWM - 1u); 	/* 1000Hz */

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

void TIM2_PWM_OUTPUT(const unsigned int Value)
{
  TIM2->CCR1 = (unsigned int)((Value*ARR_TIM2_PWM)/100u);
}


/*======================================================================================================*/

