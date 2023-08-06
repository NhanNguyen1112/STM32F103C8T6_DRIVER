
#include "EXTI.h"

static volatile char flag;

void MainTestEXTI(void)
{
	InitClockHSE();
	Enable_Disable_Clock_PortA(Enable);
	Enable_Disable_Clock_PortC(Enable);

	SetPinInput(PORTA,PIN1,InputPullUp_PullDown,PullUp);
	SetPinOutput(PORTC,PIN13,PushPull);

	Init_EXTI_PA1();

	while(1)
	{
		Demo_Button_Led();
	}
}

void EXTI1_IRQHandler(void)
{
	if(READBIT(EXTI->EXTI_PR,1))
	{		
		NVIC_ClearPendingFlag(EXTI1_IRQn);
		SETBIT(EXTI->EXTI_PR,1u,1u);

		if(flag==0) flag=1;
		else flag=0;
		
	}
}

void Init_EXTI_PA1(void)
{
	SETBIT(RCC->RCC_APB2ENR,1u,0u); /*enable clock AFIO*/

	CLEARBIT(AFIO->AFIO_EXTICR1,0xfu,4u);/*PA1, EXTI1*/
	SETBIT(EXTI->EXTI_IMR,1u,1u); /*Not masked bit 1*/

	CLEARBIT(EXTI->EXTI_RTSR,1u,1u); 	/*Clear Rising bit 1*/
	SETBIT(EXTI->EXTI_FTSR,1u,1u); 		/*Set Falling bit 1*/

	NVIC_SetPriority(EXTI1_IRQn,0);		/* Set priority = 0 */
	NVIC_ClearPendingFlag(EXTI1_IRQn);
	NVIC_EnableInterrupt(EXTI1_IRQn); /*Enable NVIC Port A*/
}

void Demo_Button_Led(void)
{
	if(flag==1)
	{
		WritePin(PORTC,PIN13,LOW);
	}
	else 
	{
		WritePin(PORTC,PIN13,HIGH);
	}
}

