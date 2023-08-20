
#include "DMA.h"

#define DMA_Buffer_Size 20
unsigned char DMA_Buffer[50]={0};
static unsigned char Index=0;

void DMA1_Channel5_IRQHandler(void);

#define Size_buffer 5

unsigned char Buffer_1[Size_buffer]={ 'A','B','C','D','\n' };
unsigned char Buffer_2[Size_buffer]={ 'H','E','L','O','\n' };
unsigned char Buffer_3[Size_buffer]={0};

volatile unsigned char DMA1_CH5_Transfer_Complete_Flag=0;

void DMA_MAIN_TEST(void)
{
  InitClockHSE(); /* 72Mhz */
  USART1_Setup_INT_RX();
  Init_TIM2_Delay();
  USART1_Setup_INT_RX();

  DMA1_CH1_Init();

  // DMA1_CH1((unsigned int *)Buffer_1,(unsigned int *)Buffer_3,sizeof(Buffer_3));
  // USART1_SendData(Buffer_3,sizeof(Buffer_3));
  // Delay_TIM2_ms(3000);

  // DMA1_CH1((unsigned int *)Buffer_2,(unsigned int *)Buffer_3,sizeof(Buffer_3));
  // USART1_SendData(Buffer_3,sizeof(Buffer_3));
  // Delay_TIM2_ms(3000);
	
  while(1)
  {


  }
}

void DMA1_CH1_Init(void)
{
  DMA1_EnableClock(Enable);

  // DMA1->CCR1 &= ~(1u<<14); /* Mem to mem Disable */
  DMA1->CCR1 |= (1u<<14); /* Mem to mem enable */

  /* Priority level 
    00: low
    01: Medium
    10: High
    11: very high
  */
  DMA1->CCR1 &= ~(3u<<12);
  DMA1->CCR1 |= (3u<<12); 

  /* Memory size
    00: 8bit
    01: 16bit
    10: 32bit
  */
  DMA1->CCR1 &= ~(3u<<10);
  DMA1->CCR1 |= (2u<<10); 

  /* Peripheral size
    00: 8bit
    01: 16bit
    10: 32bit
  */
  DMA1->CCR1 &= ~(3u<<8);
  DMA1->CCR1 |= (2u<<8);

  /* Circular mode */
  // DMA1->CCR1 &= ~(1u<<5); /* disable */
  DMA1->CCR1 |= (1u<<5);  /* enable */

  /* Data transfer direction */
  // DMA1->CCR1 &= ~(1u<<4); /* Read from peripheral */
  DMA1->CCR1 |= (1u<<4);  /* Read from memory */

  /* Transfer complete interrupt */
  DMA1->CCR1 &= ~(1u<<1); /* Disable */
  // DMA1->CCR1 |= (1u<<1);  /* Enable */
}

void DMA1_CH5_UART1_RX_Init(void)
{
  DMA1_EnableClock(Enable);

  DMA1->CCR5 &= ~(1u<<14); /* Mem to mem Disable */
  // DMA1->CCR5 |= (1u<<14); /* Mem to mem enable */

  /* Priority level 
    00: low
    01: Medium
    10: High
    11: very high
  */
  DMA1->CCR5 &= ~(3u<<12);
  // DMA1->CCR5 |= (3u<<12); 

  /* Memory size
    00: 8bit
    01: 16bit
    10: 32bit
  */
  DMA1->CCR5 &= ~(3u<<10);
  // DMA1->CCR5 |= (2u<<10); 

  /* Peripheral size
    00: 8bit
    01: 16bit
    10: 32bit
  */
  DMA1->CCR5 &= ~(3u<<8);
  // DMA1->CCR5 |= (2u<<8);

  /* MINC - Memory increment mode */
  //DMA1->CCR5 &= ~(1u<<7); /* Disable */
  DMA1->CCR5 |= (1u<<7);  /* Enable */

  /* PINC - Peripheral increment mode */
  DMA1->CCR5 &= ~(1u<<6); /* Disable */
  // DMA1->CCR5 |= (1u<<6);  /* Enable */  

  /* Circular mode */
  // DMA1->CCR5 &= ~(1u<<5); /* disable */
  DMA1->CCR5 |= (1u<<5);  /* enable */

  /* Data transfer direction */
  DMA1->CCR5 &= ~(1u<<4); /* Read from peripheral */
  // DMA1->CCR5 |= (1u<<4);  /* Read from memory */

  /* TEIE: Transfer error interrupt enable */
  // DMA1->CCR5 &= ~(1u<<3); /* Disable */
  DMA1->CCR5 |= (1u<<3);  /* Enable */ 

  /* HTIE: Half transfer interrupt enable */
  // DMA1->CCR5 &= ~(1u<<2); /* Disable */
  //DMA1->CCR5 |= (1u<<2);  /* Enable */     

  /* TCIE: Transfer complete interrupt enable */
  // DMA1->CCR5 &= ~(1u<<1); /* Disable */
  DMA1->CCR5 |= (1u<<1);  /* Enable */    

  NVIC_SetPriority(DMA1_Channel5_IRQn,0);
  NVIC_ClearPendingFlag(DMA1_Channel5_IRQn);
  NVIC_EnableInterrupt(DMA1_Channel5_IRQn);

}

void DMA1_CH1(unsigned int *StartAddress, unsigned int *Destination, unsigned short SizeData)
{

  DMA1->CPAR1 = (unsigned int)StartAddress;

  DMA1->CMAR1 = (unsigned int)Destination;

  DMA1->CNDTR1 = SizeData;

  DMA1->CCR1 |= (1u<<0); /* Enable Channel */

}

void DMA1_CH5(unsigned int *StartAddress, unsigned int *Destination, unsigned short SizeData)
{

  DMA1->CPAR5 = (unsigned int)StartAddress;

  DMA1->CMAR5 = (unsigned int)Destination;

  DMA1->CNDTR5 = SizeData;

  DMA1->CCR5 |= (1u<<0); /* Enable Channel */

}

void DMA1_Channel5_IRQHandler(void)
{

  // if( (DMA1->ISR & (1u<<18)) == 1) /* Half transfer */
  // {
  //   DMA1_CH5_Transfer_Complete_Flag=1;
  //   str_cpy( DMA_Buffer, BufferRead, (DMA_Buffer_Size/2) );
  //   DMA1->IFCR |= (1u<<18);
  // }

  if( (DMA1->ISR & (1u<<17)) == 1) /* transfer complete */
  {
    DMA1_CH5_Transfer_Complete_Flag=1;
    DMA1->IFCR |= (1u<<17);
  }

  NVIC_ClearPendingFlag(DMA1_Channel5_IRQn);
}





