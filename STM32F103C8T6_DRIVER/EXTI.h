
#ifndef __EXTI__ 
#define __EXTI__ 

#include "STM32F103C8T6_Register.h"

void EXTI1_IRQHandler(void);
void Init_EXTI_PA1(void);
void Demo_Button_Led(void);

extern volatile char flag;

#endif
