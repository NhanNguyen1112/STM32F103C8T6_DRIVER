
#ifndef _USART_
#define _USART_

#include "STM32F103C8T6_Register.h"
#include "USART_Register.h"

extern unsigned char BufferRead[20];
extern volatile unsigned char ReadData;

void USART1_SendData(unsigned char *pTxBuffer, unsigned int Len);

/* Polling */
void FunctionMainUSART1(void);
void USART1_Setup(void);
void USART1_ReceiveData(unsigned char *pRxBuffer, unsigned int Len);

/* Use interrupt */
void FunctionMainUSART1_INT(void);
void USART1_Setup_INT_RX(void);
void USART1_IRQHandler(void);

/* Use DMA */
void MAIN_UART1_DMA(void);
void UART1_DMA_Init(void);

#endif


