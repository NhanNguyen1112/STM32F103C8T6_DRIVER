
#ifndef __GPIO__
#define __GPIO__

#include "STM32F103C8T6_Register.h"
#include "Gpio_Register.h"

void Init_PA8_MCO(void);
void SetPinInput(const unsigned char PORT, const unsigned char Pin, const unsigned char ModeInput, const unsigned char UpDown);
void SetPinOutput(const unsigned char PORT, const unsigned char Pin, const unsigned char ModeOutput);
void WritePin(const unsigned char PORT, const unsigned char Pin, const unsigned char Status);
unsigned int ReadPin(const unsigned char PORT, const unsigned char Pin);
void TogglePin(const unsigned char PORT, const unsigned char Pin);

void Blink_LED(void);
void Button_Led(void);
void Delay(unsigned int MS);

#endif

