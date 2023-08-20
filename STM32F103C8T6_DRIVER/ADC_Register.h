
#ifndef _ADC_Register_
#define _ADC_Register_

#include "ADC.h"

typedef struct
{
  volatile unsigned int ADC_SR;
  volatile unsigned int ADC_CR1;
  volatile unsigned int ADC_CR2;
  volatile unsigned int ADC_SMPR1;
  volatile unsigned int ADC_SMPR2;
  volatile unsigned int ADC_JOFR1;
  volatile unsigned int ADC_JOFR2;
  volatile unsigned int ADC_JOFR3;
  volatile unsigned int ADC_JOFR4;
  volatile unsigned int ADC_HTR;
  volatile unsigned int ADC_LTR;
  volatile unsigned int ADC_SQR1;
  volatile unsigned int ADC_SQR2;
  volatile unsigned int ADC_SQR3;
  volatile unsigned int ADC_JSQR;
  volatile unsigned int ADC_JDR1;
  volatile unsigned int ADC_JDR2;
  volatile unsigned int ADC_JDR3;
  volatile unsigned int ADC_JDR4;
  volatile unsigned int ADC_DR;
}ADC_type;

#define ADC1_BASE_ADDRESS 			((unsigned int)0x40012400u)
#define ADC2_BASE_ADDRESS 			((unsigned int)0x40012800u)
#define ADC3_BASE_ADDRESS 			((unsigned int)0x40013C00u)

#define ADC1  ((ADC_type *)ADC1_BASE_ADDRESS)
#define ADC2  ((ADC_type *)ADC2_BASE_ADDRESS)
#define ADC3  ((ADC_type *)ADC3_BASE_ADDRESS)

#endif /* _ADC_Register_ */

