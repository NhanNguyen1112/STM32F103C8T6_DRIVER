
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
