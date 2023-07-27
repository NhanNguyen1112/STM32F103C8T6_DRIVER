
#ifndef __CLOCK__
#define __CLOCK__ 

#include "STM32F103C8T6_Register.h"

/*================== CONFIG CLOCK ==========================*/

/*#define FREDIV1_DIV2*/

/*#define PLLMUL_X4*/
/*#define PLLMUL_X8*/
#define PLLMUL_X9


//#define PA8_MCO
//#define MCO_SYSCLK
//#define MCO_HSI
//#define MCO_HSE
//#define MCO_PLL_DIV2


/*===========================================================*/

void InitClockHSE(void);
void Enable_Disable_Clock_PortA(const unsigned char Status);
void Enable_Disable_Clock_PortB(const unsigned char Status);
void Enable_Disable_Clock_PortC(const unsigned char Status);
void Enable_Disable_Clock_PortD(const unsigned char Status);
void Enable_Disable_Clock_PortE(const unsigned char Status);
void Enable_Disable_Clock_PortF(const unsigned char Status);
void Enable_Disable_Clock_PortG(const unsigned char Status);

#endif

