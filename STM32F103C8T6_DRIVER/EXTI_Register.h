
#ifndef _EXTI_Register_
#define _EXTI_Register_

#include "EXTI.h"

typedef struct
{
	volatile unsigned int EXTI_IMR;
	volatile unsigned int EXTI_EMR;
	volatile unsigned int EXTI_RTSR;
	volatile unsigned int EXTI_FTSR;
	volatile unsigned int EXTI_SWIER;
	volatile unsigned int EXTI_PR;
}EXTI_typedef;

#define EXTI_BASE_ADDRESS 	((unsigned int)0x40010400u)
#define EXTI 		            ((EXTI_typedef*)EXTI_BASE_ADDRESS)

#endif
