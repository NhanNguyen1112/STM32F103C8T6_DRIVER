
#ifndef _I2C_
#define _I2C_

#include "STM32F103C8T6_Register.h"
#include "I2C_Register.h"

void Main_I2C1_Test(void);

void I2C1_Init(void);
void I2C1_Write(unsigned char Data);
void I2C1_WriteMultiData(unsigned char *Data, const unsigned char size);
void I2C_SendData(const unsigned char Address, const unsigned char Data);


#endif


