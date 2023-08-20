
#ifndef __ADC__
#define __ADC__ 

#include "STM32F103C8T6_Register.h"
#include "ADC_Register.h"

/*
PA0 -> ADC12_IN0
PA1 -> ADC12_IN1
PA2 -> ADC12_IN2
PA3 -> ADC12_IN3
PA4 -> ADC12_IN4
PA5 -> ADC12_IN5
PA6 -> ADC12_IN6
PA7 -> ADC12_IN7

PB0 -> ADC12_IN8
PB1 -> ADC12_IN9

PC0 -> ADC12_IN10
PC1 -> ADC12_IN11
PC2 -> ADC12_IN12
PC3 -> ADC12_IN13
PC4 -> ADC12_IN14
PC5 -> ADC12_IN15
*/

void ADC_MAIN_TEST(void);

void ADC1_Init_CH1(void);
void ADC1_2_IRQHandler(void);
unsigned short ADC1_GetVal(void);

#endif /* __ADC__ */


