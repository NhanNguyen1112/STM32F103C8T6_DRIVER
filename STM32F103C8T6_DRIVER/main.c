
#include "STM32F103C8T6_Register.h"

int main(void)
{

	Init_Led_PC13();

	while(1)
	{
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,LOW);
		SysTickDelay(5);
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,HIGH);
		SysTickDelay(5);
	}
}
