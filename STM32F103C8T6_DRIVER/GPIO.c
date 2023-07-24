
#include "GPIO.h"

void Init_Led_PC13(void)
{
	Enable_Disable_Clock_PortC(Enable); /*Enable Clock PORT C*/

	SETBIT(GPIO_C->GPIO_CRH,3u,20); /*Mode output 50Mhz*/
	CLEARBIT(GPIO_C->GPIO_CRH,3u,22); /*CNF Output push pull*/
}

void Init_Button_PA1(void)
{
	Enable_Disable_Clock_PortA(Enable); /*Enable Clock PORT A*/
	
	CLEARBIT(GPIO_A->GPIO_CRL,0xfu,4u); /*Clear MODE and CNF*/
	SETBIT(GPIO_A->GPIO_CRL,0x8u,4u); /*Set Mode Input & CNF pull-up/pull-down*/
	SETBIT(GPIO_A->GPIO_ODR,1u,1); /*Set Pull-up*/
}

/* Blink LED PC13 */
void Blink_LED(void)
{
	Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,LOW);
	Delay(1000);
	Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,HIGH);
	Delay(1000);
}

/* Button PA1 & LED PC13 */
void Button_Led(void)
{
	if(READBIT(GPIO_A->GPIO_IDR,1))
	{
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,HIGH);
	}
	else 
	{
		Set_Pin_GPIO(&GPIO_C->GPIO_ODR,PIN13,LOW);
	}
}

void Set_Pin_GPIO(unsigned int *GPIO_Register, unsigned char Pin, const unsigned char Status)
{
  if(Status==HIGH) SETBIT(*GPIO_Register, 1u, Pin);
  else CLEARBIT(*GPIO_Register, 1u, Pin);
}

unsigned int Get_Pin_GPIO(unsigned int *GPIO_Register, unsigned char Pin)
{
  return READBIT(*GPIO_Register, Pin);
}

void Delay(unsigned int MS)
{
	unsigned int i=0, j=0;
	for(i=0 ;i<=MS;i++)
	{
		for(j=0;j<=1000;j++);
	}
}

