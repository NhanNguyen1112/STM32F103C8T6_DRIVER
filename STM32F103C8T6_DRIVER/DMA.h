
#ifndef _DMA_
#define _DMA_

#include "STM32F103C8T6_Register.h"
#include "DMA_Register.h"

extern unsigned char DMA_Buffer[50];
extern volatile unsigned char DMA1_CH5_Transfer_Complete_Flag;

void DMA_MAIN_TEST(void);

void DMA1_CH1_Init(void);
void DMA1_CH5_UART1_RX_Init(void);
void DMA1_CH1(unsigned int *StartAddress, unsigned int *Destination, unsigned short SizeData);
void DMA1_CH5(unsigned int *StartAddress, unsigned int *Destination, unsigned short SizeData);

#endif /* _DMA_ */

