
#include "EXTI.h"

volatile char flag;

void EXTI1_IRQHandler(void)
{
	if(READBIT(EXTI->EXTI_PR,1))
	{		
		flag++;
		if(flag>1) flag=0;
		SETBIT(EXTI->EXTI_PR,1u,1u);
	}
}

void Init_EXTI_PA1(void)
{
	SETBIT(RCC->RCC_CR,1,0); /*HSION enable*/
	SETBIT(RCC->RCC_APB2ENR,1u,0u); /*enable clock AFIO*/

	CLEARBIT(AFIO->AFIO_EXTICR1,0xfu,4u);/*PA1, EXTI1*/
	SETBIT(EXTI->EXTI_IMR,1u,1u); /*Not masked bit 1*/

	CLEARBIT(EXTI->EXTI_RTSR,1u,1u); /*Clear Rising bit 1*/
	SETBIT(EXTI->EXTI_FTSR,1u,1u); /*Set Falling bit 1*/

	SETBIT(NVIC->ISER[0],1u,7u); /*Enable NVIC Port A*/
}

void Demo_Button_Led(void)
{
	if(flag==1)
	{
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,LOW);
	}
	else 
	{
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,HIGH);
	}
}

