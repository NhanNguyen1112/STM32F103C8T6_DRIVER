
#include "USART.h"

static unsigned int UART1_ReadData(void);

typedef struct
{
  unsigned char a;
  unsigned char b;
  unsigned short c;
  unsigned int d;
}data;

static data sendta;

volatile unsigned char ReadData;
volatile unsigned char count=0;

unsigned char BufferRead[20]={0};
unsigned char SenData1[5] = {'\n','a','b','c','\n'};
unsigned char SenData2[5] = {'\n','1','2','3','\n'};


static void Setup_GPIO_PA9TX_PA10RX(void)
{
  Enable_Disable_Clock_PortA(Enable);

  /* PA9 TX -> OUTPUT, CNF: ALT Push-pull */
  SetPinOutput(PORTA,PIN9,Alternate_PushPull);

  /* PA10 RX -> INPUT, Pull-up */
  SetPinInput(PORTA,PIN10,InputPullUp_PullDown,PullUp);

  AFIO->AFIO_MAPR &= ~(1u<<2); /* USART1 no remap */

}

static void USART1_Init_CLK(void)
{
  RCC->RCC_APB2ENR |= (1u<<14); /* enable clock USART 1 */
}

void USART1_SendData(unsigned char *pTxBuffer, unsigned int Len)
{
  unsigned int count=0;
  for(count=0; count<Len;count++)
  {
    /* If empty -> Data is transferred to the shift register*/
    while ( !(USART1->SR & (1u<<7))); 

    USART1->DR = (unsigned char)(*pTxBuffer & (0xFFu));

    pTxBuffer++;
  }

  while ( !(USART1->SR & (1u<<6)) ); /* Transmission is complete */
}

/*=============================== POLLING ===========================================================*/
void FunctionMainUSART1(void)
{
  InitClockHSE();
  USART1_Setup();

  USART1_SendData(SenData1,sizeof(SenData1));
  USART1_SendData(SenData2,sizeof(SenData2));
  
  while(1)
  {
    USART1_ReceiveData(&ReadData,sizeof(ReadData));
    USART1_SendData(&ReadData,sizeof(ReadData));
  }
}

/* PA9-TX ; PA10-RX ; Baudrate:9600 */
void USART1_Setup(void)
{
  Setup_GPIO_PA9TX_PA10RX();
  USART1_Init_CLK();

  USART1->CR1 |= (1u<<3);   /* enable Transmitter */
  USART1->CR1 |= (1u<<2);   /* enable Receiver */
  USART1->CR1 &= ~(1u<<12); /* M: 1 start bit, 8 data, 1 stop bit */

  /* APB2 CLK= 72Mhz */
  /* Baudrate= 9600 */
  /* OVER8=0 -> sample 16 */
  /* 72.000.000/(16*9600) = 468.75 */
  /* DIV_Mantissa = 468 */
  /* DIV_Fraction = 16*0.75 = 12 */
  USART1->BRR |= (0x1D4u<<4); /* Set  DIV_Mantissa */
  USART1->BRR |= (0xCu<<0);   /* Set  DIV_Fraction */

  USART1->CR1 |= (1u<<13); /* Enable USART1 */
}

void USART1_ReceiveData(unsigned char *pRxBuffer, unsigned int Len)
{
  unsigned int count=0;
  for(count=0; count<Len;count++)
  {
    while ( !(USART1->SR & (1u<<5)) ); /* wait read all data */

    *pRxBuffer = (unsigned char)(USART1->DR & (0xFFu<<0));

    pRxBuffer++;
  }
}
/*==================================================================================================*/

/*=============================== INTERRUPT ========================================================*/
void FunctionMainUSART1_INT(void)
{
  InitClockHSE();
  Init_TIM2_Delay();
  USART1_Setup_INT_RX();

  // USART1_SendData(SenData1,sizeof(SenData1));
  // USART1_SendData(SenData2,sizeof(SenData2));

  // sendta.a = 2;
  // sendta.b = 34;
  // sendta.c = 345;
  // sendta.d = 6745;
	// sprintf(&BufferRead,"%d-%d-%d-%d", sendta.a, sendta.b, sendta.c, sendta.d);
  // USART1_SendData(BufferRead,sizeof(BufferRead));
  
  while(1)
  {
    if(count != 0)
    {
      USART1_SendData(SenData1,sizeof(SenData1));
      USART1_SendData(BufferRead,sizeof(BufferRead));
      USART1_SendData(SenData2,sizeof(SenData2));
      count=0;
    }

    // USART1_SendData(BufferRead,sizeof(BufferRead));
    // Delay_TIM2_ms(1000);
  }
}

/* PA9-TX ; PA10-RX ; Baudrate:9600 */
void USART1_Setup_INT_RX(void)
{
  Setup_GPIO_PA9TX_PA10RX();
  USART1_Init_CLK();

  USART1->CR1 |= (1u<<3);   /* enable Transmitter */
  USART1->CR1 |= (1u<<2);   /* enable Receiver */
  USART1->CR1 &= ~(1u<<12); /* M: 1 start bit, 8 data, 1 stop bit */
  USART1->CR1 |= (1u<<5);   /* RXNEIE: RX interrupt enable */

  /* APB2 CLK= 72Mhz */
  /* Baudrate= 9600 */
  /* OVER8=0 -> sample 16 */
  /* 72.000.000/(16*9600) = 468.75 */
  /* DIV_Mantissa = 468 */
  /* DIV_Fraction = 16*0.75 = 12 */
  USART1->BRR |= (0x1D4u<<4); /* Set  DIV_Mantissa */
  USART1->BRR |= (0xCu<<0);   /* Set  DIV_Fraction */

  USART1->CR1 |= (1u<<13); /* Enable USART1 */

  NVIC_SetPriority(USART1_IRQn,1);    /* Set priority */
  NVIC_ClearPendingFlag(USART1_IRQn); /* interrupt clear pending USART1 */
  NVIC_EnableInterrupt(USART1_IRQn);  /* enable interrupt USART1 */

}

void USART1_IRQHandler(void)
{
  BufferRead[count] = (unsigned char)(USART1->DR & (0xFFu<<0));
  count++;

  /* Test sau khi read thi gui lai Data vua read len TX */
  //ReadData = (unsigned char)(USART1->DR & (0xFFu<<0));
  //USART1_SendData(&ReadData,sizeof(ReadData));

  NVIC_ClearPendingFlag(USART1_IRQn); /* interrupt clear pending USART1 */
}

/*==================================================================================================*/


/*=============================== UART With DMA ========================================================*/

static unsigned int UART1_Read = 0;

void MAIN_UART1_DMA(void)
{
  InitClockHSE();
  //Init_TIM2_Delay();

  UART1_DMA_Init();

  DMA1_CH5_UART1_RX_Init();

  //UART1_Read = UART1_ReadData();
	DMA1_CH5(&USART1->DR, (unsigned int*) BufferRead, sizeof(BufferRead));
	
  while (1)
  {
    if(BufferRead[1] != 0)
    {
      USART1_SendData( BufferRead, sizeof(BufferRead) );
			BufferClear( BufferRead, sizeof(BufferRead) );
      DMA1_CH5_Transfer_Complete_Flag=0;
    }
    
  }
  
}

/* PA9-TX ; PA10-RX ; Baudrate:9600 */
void UART1_DMA_Init(void)
{
  Setup_GPIO_PA9TX_PA10RX();
  USART1_Init_CLK();

  USART1->CR1 |= (1u<<3);   /* enable Transmitter */
  USART1->CR1 |= (1u<<2);   /* enable Receiver */

  /* DMA Receiver */
  // USART1->CR3 &= ~(1u<<6); /* Disable */
  USART1->CR3 |= (1u<<6); /* Enable */

  /* DMA Transmitter */
  USART1->CR3 &= ~(1u<<7); /* Disable */
  // USART1->CR3 |= (1u<<7); /* Enable */

  USART1->CR1 &= ~(1u<<12); /* M: 1 start bit, 8 data, 1 stop bit */

  // USART1->CR1 |= (1u<<5);   /* RXNEIE: RX interrupt enable */

  /* APB2 CLK= 72Mhz */
  /* Baudrate= 9600 */
  /* OVER8=0 -> sample 16 */
  /* 72.000.000/(16*9600) = 468.75 */
  /* DIV_Mantissa = 468 */
  /* DIV_Fraction = 16*0.75 = 12 */
  USART1->BRR |= (0x1D4u<<4); /* Set  DIV_Mantissa */
  USART1->BRR |= (0xCu<<0);   /* Set  DIV_Fraction */

  USART1->CR1 |= (1u<<13); /* Enable USART1 */
}

static unsigned int UART1_ReadData(void)
{
  return USART1->DR;
}

/*==================================================================================================*/



