
#ifndef __Timer_Register__
#define __Timer_Register__

#include "STM32F103C8T6_Register.h"

typedef struct
{
  volatile unsigned int CR1;
  volatile unsigned int CR2;
  volatile unsigned int SMCR;
  volatile unsigned int DIER;
  volatile unsigned int SR;
  volatile unsigned int EGR;
  volatile unsigned int CCMR1;
  volatile unsigned int CCMR2;
  volatile unsigned int CCER;
  volatile unsigned int CNT;
  volatile unsigned int PSC;
  volatile unsigned int ARR;
  char dummy[4];
  volatile unsigned int CCR1;
  volatile unsigned int CRR2;
  volatile unsigned int CCR3;
  volatile unsigned int CCR4;
  char dummy1[4];
  volatile unsigned int DCR;
  volatile unsigned int DMAR;
}TIM2to5_typedef;

#define TIM2 ((TIM2to5_typedef *)TIM2_BASE_ADDRESS)
#define TIM3 ((TIM2to5_typedef *)TIM3_BASE_ADDRESS)
#define TIM4 ((TIM2to5_typedef *)TIM4_BASE_ADDRESS)
#define TIM5 ((TIM2to5_typedef *)TIM5_BASE_ADDRESS)

#endif
