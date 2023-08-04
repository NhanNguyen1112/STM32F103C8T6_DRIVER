
#ifndef __Softtimer__
#define __Softtimer__

#include "STM32F103C8T6_Register.h"

#define Total_Timer 5

#ifndef _CALLBACK_
#define _CALLBACK_
typedef void (*CALLBACK)(void);
#endif

typedef enum 
{
  ONESHOT,
  CONTINUE
}Mode_typedef;

typedef struct Softtimer
{
  unsigned int TimerID;
  unsigned char Mode;
  unsigned int TimeoutValue;
  unsigned int CurrentTime;
  CALLBACK Callback;
} Softtimer;

extern volatile unsigned int TimeCountMs;

void Function_PC13(void);
void Function_PB5(void);
void Function_PB6(void);
void Main_Function(void);

void Softtimer_Init(void);
void Softtimer_StartTimer(unsigned int TimerID,unsigned int TimeoutValue,unsigned char Mode,CALLBACK callback);
void Softtimer_StopTimer(unsigned int TimerID);
void Softtimer_MainFunction(void);
void SysTick_Handler(void);

#endif
