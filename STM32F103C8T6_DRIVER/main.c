
#include "STM32F103C8T6_Register.h"

int main(void)
{

	Init_Led_PC13();
	Init_Button_PA1();

	SETBIT(RCC->RCC_CR,1,0); /*HSION enable*/
	SETBIT(RCC->RCC_APB2ENR,1u,0u); /*enable clock AFIO*/

	CLEARBIT(AFIO->AFIO_EXTICR1,0xfu,4u);/*PA1, EXTI1*/
	SETBIT(EXTI->EXTI_IMR,1u,1u); /*Not masked bit 1*/

	CLEARBIT(EXTI->EXTI_RTSR,1u,1u); /*Clear Rising bit 1*/
	SETBIT(EXTI->EXTI_FTSR,1u,1u); /*Set Falling bit 1*/

	SETBIT(NVIC->ISER[0],1u,7u); /*Enable NVIC Port A*/

	while(1)
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
}
