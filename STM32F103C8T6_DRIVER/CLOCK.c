
#include "CLOCK.h"

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
