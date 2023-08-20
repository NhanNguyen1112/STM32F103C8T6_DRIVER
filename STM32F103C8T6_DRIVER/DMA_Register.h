
#ifndef _DMA_Register_
#define _DMA_Register_

#include "DMA.h"

typedef struct 
{
  volatile unsigned int ISR;
  volatile unsigned int IFCR;

  volatile unsigned int CCR1;
  volatile unsigned int CNDTR1;
  volatile unsigned int CPAR1;
  volatile unsigned int CMAR1;
  unsigned int dummy;

  volatile unsigned int CCR2;
  volatile unsigned int CNDTR2;
  volatile unsigned int CPAR2;
  volatile unsigned int CMAR2;
  unsigned int dummy1;

  volatile unsigned int CCR3;
  volatile unsigned int CNDTR3;
  volatile unsigned int CPAR3;
  volatile unsigned int CMAR3;
  unsigned int dummy2;

  volatile unsigned int CCR4;
  volatile unsigned int CNDTR4;
  volatile unsigned int CPAR4;
  volatile unsigned int CMAR4;
  unsigned int dummy3;

  volatile unsigned int CCR5;
  volatile unsigned int CNDTR5;
  volatile unsigned int CPAR5;
  volatile unsigned int CMAR5;
  unsigned int dummy4;

  volatile unsigned int CCR6;
  volatile unsigned int CNDTR6;
  volatile unsigned int CPAR6;
  volatile unsigned int CMAR6;
  unsigned int dummy5;

  volatile unsigned int CCR7;
  volatile unsigned int CNDTR7;
  volatile unsigned int CPAR7;
  volatile unsigned int CMAR7;
  unsigned int dummy6;

}DMA_Typedef;

#define DMA1_BASE_ADDRESS 			((unsigned int)0x40020000UL)
#define DMA2_BASE_ADDRESS 			((unsigned int)0x40020400UL)

#define DMA1  ((DMA_Typedef *)DMA1_BASE_ADDRESS)
#define DMA2  ((DMA_Typedef *)DMA2_BASE_ADDRESS)

#endif /* _DMA_Register_ */




