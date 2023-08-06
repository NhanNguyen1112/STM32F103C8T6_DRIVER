
#ifndef _USART_
#define _USART_

#include "STM32F103C8T6_Register.h"
#include "USART_Register.h"

extern volatile unsigned char ReadData;

void Setup_GPIO_PA9TX_PA10RX(void);
void USART1_Init_CLK(void);
void USART1_SendData(unsigned char *pTxBuffer, unsigned int Len);

/* Polling */
void FunctionMainUSART1(void);
void USART1_Setup(void);
void USART1_ReceiveData(unsigned char *pRxBuffer, unsigned int Len);

/* Use interrupt */
void FunctionMainUSART1_INT(void);
void USART1_Setup_INT_RX(void);
void USART1_IRQHandler(void);

#endif