
#ifndef __Timer__
#define __Timer__

#include "Timer_Register.h"

#ifndef _CALLBACK_
#define _CALLBACK_
typedef void (*CALLBACK)(void);
#endif

void Init_TIM2(void);
void TIM2_Function(const unsigned int MiliSeconds, CALLBACK Function);
void TIM2_IRQHandler(void);

void Function_Test(void);
void Main_TIM2_BASE(void);

void Main_TIM2_PWM(void);
void Init_TIM2_CH1_PA0(void);

#endif
