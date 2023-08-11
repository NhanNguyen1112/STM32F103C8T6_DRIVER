#ifndef PCF8574T_H_
#define PCF8574T_H_

#include "STM32F103C8T6_Register.h"
#include "I2C.h"

extern unsigned char PCF8574T_ADDRESS;

void PCF8574_Init(unsigned char Address);

unsigned char PCF8574T_ReadPin(unsigned char pin);
void PCF8574T_WritePin(unsigned char pin, unsigned char state);
void PCF8574_WriteALL(unsigned char state);

void PCF8574_MAIN(void);

#endif /* PCF8574T_H_ */