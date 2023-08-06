
#ifndef __Timer__
#define __Timer__

#include "Timer_Register.h"

#ifndef _CALLBACK_
#define _CALLBACK_
typedef void (*CALLBACK)(void);
#endif

/*======================================================================================================*/
/*                              TIMER BASE                                                           */
/*======================================================================================================*/

#define PSC_TIM2_BASE 1u
#define ARR_TIM2_BASE 36000u

void Init_TIM2_Delay(void);
void Delay_TIM2_ms(const unsigned int MiliSeconds);
void Delay_TIM2_us(const unsigned int MicroSeconds);
void TIM2_IRQHandler(void);
void Function_Test(void);
void Main_TIM2_BASE(void);
/*======================================================================================================*/


/*======================================================================================================*/
/*                              TIMER PWM OUTPUT                                                         */
/*======================================================================================================*/

#define PSC_TIM2_PWM 720u
#define ARR_TIM2_PWM 100u

void Main_TIM2_PWM(void);
void Init_TIM2_PWM_CH1_PA0(void);
void TIM2_PWM_OUTPUT(const unsigned int Value);
/*======================================================================================================*/

#endif
