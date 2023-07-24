
#ifndef __GPIO__
#define __GPIO__

#include "STM32F103C8T6_Register.h"

void Blink_LED(void);
void Button_Led(void);
void Init_Led_PC13(void);
void Init_Button_PA1(void);
void Set_Pin_GPIO(unsigned int *GPIO_Register, unsigned char Pin, const unsigned char Status);
unsigned int Get_Pin_GPIO(unsigned int *GPIO_Register, unsigned char Pin);
void Delay(unsigned int MS);

#endif

