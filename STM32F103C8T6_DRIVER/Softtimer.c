
#include "Softtimer.h"

volatile unsigned int TimeCountMs;

static Softtimer TIMER[Total_Timer];

void Function_PC13(void)
{
	TogglePin(PORTC,PIN13);
}

void Function_PB5(void)
{
  TogglePin(PORTB,PIN5);
}

void Function_PB6(void)
{
  TogglePin(PORTB,PIN6);
}

void Main_Function(void)
{
  InitClockHSE();
	Enable_Disable_Clock_PortC(Enable);
	Enable_Disable_Clock_PortB(Enable);
	Enable_Disable_Clock_PortA(Enable);
	
	SetPinInput(PORTA,PIN1,InputPullUp_PullDown,PullUp);
	SetPinOutput(PORTC,PIN13,0);
	SetPinOutput(PORTB,PIN5,0);
	SetPinOutput(PORTB,PIN6,0);

	Softtimer_Init();
	
	Softtimer_StartTimer(0,10,ONESHOT,&Function_PC13);
	Softtimer_StartTimer(1,5,CONTINUE,&Function_PB5);
	Softtimer_StartTimer(2,50,CONTINUE,&Function_PB6);

	while(1)
	{
		Softtimer_MainFunction();
	}
}

void Softtimer_Init(void)
{
  TimeCountMs = 0;

  SYSTICK->SYST_RVR = (uint32_t)(7200000u-1u); /* Set reload value */

  SYSTICK->SYST_CVR = (uint32_t)(0u); /* Clear current value */

  SYSTICK->SYST_CSR |= (7u<<0); /* Enable counter & Set processor clock & enable INT */
}

void Softtimer_StartTimer(unsigned int TimerID,unsigned int TimeoutValue,unsigned char Mode,CALLBACK Event)
{
  TIMER[TimerID].TimerID = TimerID;
  TIMER[TimerID].Mode = Mode;
  TIMER[TimerID].TimeoutValue = TimeoutValue;
  TIMER[TimerID].Callback = Event;
  TIMER[TimerID].CurrentTime = TimeCountMs;
}

void Softtimer_StopTimer(unsigned int TimerID)
{
  TIMER[TimerID].TimeoutValue = 0;
}

void Softtimer_MainFunction(void)
{
  int i;
  for(i=0;i<=Total_Timer;i++)
  {
    if(TIMER[i].TimeoutValue != 0)
    {
      if ( (TimeCountMs - TIMER[i].CurrentTime) >= TIMER[i].TimeoutValue )
      {
        if(TIMER[i].Mode==CONTINUE) 
        {
          TIMER[i].Callback();
          TIMER[i].CurrentTime = TimeCountMs;
        } 
        else TIMER[i].Callback();
      }
    }
  }
}

void SysTick_Handler(void)
{
  TimeCountMs++;
}


