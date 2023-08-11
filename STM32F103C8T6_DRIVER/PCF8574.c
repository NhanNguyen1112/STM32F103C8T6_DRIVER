#include "PCF8574.h"

unsigned char PCF8574T_ADDRESS= 0;

void PCF8574_Init(unsigned char Address)
{
	PCF8574T_ADDRESS = Address;
	PCF8574T_ADDRESS <<= 1;
}

static unsigned char PCF8574T_Read(void) 
{
	unsigned char Data=0xFF;
	Data = I2C1_ReadData(PCF8574T_ADDRESS, I2C_ACK);
	return Data;
}

unsigned char PCF8574T_ReadPin(unsigned char pin) 
{
	unsigned char PCF8574T_Port = 0;

	if(pin!=0) pin = (pin-1);

	PCF8574T_Port = PCF8574T_Read();

	return ((PCF8574T_Port & (1u << pin)) ? 1 : 0);
}

static void PCF8574T_Write(unsigned char data) 
{ 
	I2C1_SendData(PCF8574T_ADDRESS, data);
}

void PCF8574T_WritePin(unsigned char pin, unsigned char state) 
{
	unsigned char PCF8574T_Port = 0;

	if(pin!=0) pin = (pin-1);

	if (state==HIGH) PCF8574T_Port |= (1u << pin);
	else PCF8574T_Port &= ~(1u << pin);

	PCF8574T_Write(PCF8574T_Port);
}

void PCF8574_WriteALL(unsigned char state)
{
	unsigned char PCF8574T_Port = 0;

	if (state==HIGH) PCF8574T_Port = 0xFF;
	else PCF8574T_Port = 0;

	PCF8574T_Write(PCF8574T_Port);
}

void PCF8574_MAIN(void)
{
  InitClockHSE(); /* 72Mhz */
  Init_TIM2_Delay();
	PCF8574_Init(0x27);
  I2C1_Init(I2C_FAST);

	Enable_Disable_Clock_PortC(Enable);
	SetPinOutput(PORTC,PIN13,PushPull);

	volatile unsigned char PIN1=0;

  while(1)
  {
		// PIN1 = PCF8574T_ReadPin(7);
		
		// if(PIN1==0) WritePin(PORTC,PIN13,LOW);
		// else WritePin(PORTC,PIN13,HIGH);
		
		// Delay_TIM2_ms(50);

		// for(int i=0; i<=9; i++)
		// {
		// 	PCF8574T_WritePin(i,HIGH);
		// 	Delay_TIM2_ms(100);
		// }
		// Delay_TIM2_ms(100);
		// for(int j=8; j>=0; j--)
		// {
		// 	PCF8574T_WritePin(j,HIGH);
		// 	Delay_TIM2_ms(100);
		// }

		// PCF8574T_WritePin(1,HIGH);
    // Delay_TIM2_ms(1000);

		// PCF8574T_WritePin(0,HIGH);
    // Delay_TIM2_ms(1000);

		// PCF8574T_WritePin(8,HIGH);
    // Delay_TIM2_ms(1000);

		// PCF8574T_WritePin(0,HIGH);
    // Delay_TIM2_ms(1000);

		// PCF8574_WriteALL(HIGH);
		// Delay_TIM2_ms(1000);
		// PCF8574_WriteALL(LOW);
		// Delay_TIM2_ms(1000);
  }
}




