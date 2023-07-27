
#include "STM32F103C8T6_Register.h"

int main(void)
{
	InitClockHSE();
	Enable_Disable_Clock_PortC(Enable);
	Enable_Disable_Clock_PortB(Enable);
	Enable_Disable_Clock_PortA(Enable);
	
	SetPinInput(PORTA,PIN1,InputPullUp_PullDown,PullUp);
	SetPinOutput(PORTC,PIN13,0);
	SetPinOutput(PORTB,PIN5,0);
	SetPinOutput(PORTB,PIN6,0);

	while (1)
	{
		TogglePin(PORTC,PIN13);
		Delay(1000);
	}
	
	
	// Init_Button_PA1();
	// Init_Led_PC13();
	// InitLed_B5B6();

	// Softtimer_Init();
	
	// Softtimer_StartTimer(0,10,ONESHOT,&Function_PC13);
	// Softtimer_StartTimer(1,5,CONTINUE,&Function_PB5);
	// Softtimer_StartTimer(2,50,CONTINUE,&Function_PB6);

	// while(1)
	// {
	// 	Softtimer_MainFunction();

	// 	if(READBIT(GPIO_A->GPIO_IDR,1)==0)
	// 	{
	// 		Softtimer_StopTimer(1);
	// 	}
	// }
}

