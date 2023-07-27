
#include "CLOCK.h"

void InitClockHSE(void)
{
	RCC->RCC_CFGR &= ~(3u<<0);    /* SW Select HSI */

  RCC->RCC_AHBENR &= ~(1u<<12); /* OTGFSEN Disable */
	RCC->RCC_CR &= ~(1u<<24);     /* Disable PLL */
	
	RCC->RCC_CR |= (1<<16);                 /* Enable HSE 8Mhz */
  while( (RCC->RCC_CR & (1<<17)) == 0 );  /* Wait HSERD */
  
  RCC->RCC_CFGR2 &= ~(1u<<16u); /* FREDIV1SRC Set HSE clock */

  RCC->RCC_CFGR2 &= ~(0xFu<<0); /* FREDIV1 not divided = 8Mhz*/
  #ifdef FREDIV1_DIV2
  RCC->RCC_CFGR2 |= (1u<<0);    /* FREDIV1 /2 */
  #endif

  RCC->RCC_CFGR  |= (1<<16);    /* PLLSRC set FREDIV1 */
  
  RCC->RCC_CFGR  &= ~(0xFu<<18);  /* PLLMUL set not divided */
  #ifdef PLLMUL_X4
  RCC->RCC_CFGR  |= (2u<<18);   /* PLLMUL X4 */
  #endif
  #ifdef PLLMUL_X8
  RCC->RCC_CFGR  |= (6u<<18);   /* PLLMUL X8 */
  #endif
  #ifdef PLLMUL_X9
	RCC->RCC_CFGR  |= (7u<<18);     /* PLLMUL X9 */
  #endif
  
  RCC->RCC_CFGR &= ~(1u<<10u);  /* PPRE2 APB1 not divided */
  RCC->RCC_CFGR &= ~(1u<<13u);  /* PPRE2 APB2 not divided */
  RCC->RCC_CFGR &= ~(0xFu<<4u); /* HPRE AHB prescaler not divided */
	
	RCC->RCC_CFGR |= (1u<<0);   /* SW Select HSE */
  RCC->RCC_CR &= ~(1u << 0);  /* Disable HSI */
  
  RCC->RCC_CR |= (1u<<24);    /* Enable PLL */

  RCC->RCC_CFGR &= ~(0xFu<<24u);  /* MCO ALL clear */
  #ifdef MCO_SYSCLK
  RCC->RCC_CFGR |= (4u<<24u);     /* MCO Check SYSCLK */
  #endif
  #ifdef MCO_HSI
  RCC->RCC_CFGR |= (5u<<24u);   /* MCO Check HSI */
  #endif
  #ifdef MCO_HSE
  RCC->RCC_CFGR |= (6u<<24u);   /* MCO Check HSE */
  #endif
  #ifdef MCO_PLL_DIV2
  RCC->RCC_CFGR |= (7u<<24u);   /* MCO Check PLL/2 */
  #endif

  RCC->RCC_CFGR &= ~(1u<<0);  /* SW Clear */
	RCC->RCC_CFGR |= (2u<<0);   /* SW Select PLLCLK */

  while (!(RCC->RCC_CFGR & (1u << 3)));

  #ifdef PA8_MCO
  Init_PA8_MCO(); /* PA8 output clock */
  #endif

}

void Enable_Disable_Clock_PortA(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,2);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,2);
}

void Enable_Disable_Clock_PortB(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,3);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,3);
}

void Enable_Disable_Clock_PortC(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,4);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,4);
}

void Enable_Disable_Clock_PortD(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,5);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,5);
}

void Enable_Disable_Clock_PortE(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,6);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,6);
}

void Enable_Disable_Clock_PortF(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,7);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,7);
}

void Enable_Disable_Clock_PortG(const unsigned char Status)
{
  if(Status==Enable) SETBIT(RCC->RCC_APB2ENR,1u,8);
  else CLEARBIT(RCC->RCC_APB2ENR,1u,8);
}
