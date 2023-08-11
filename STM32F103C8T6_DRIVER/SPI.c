
#include "SPI.h"

/*
 * SPI1
 * NSS : PA4 (General purpose output push-pull)
 * SCK : PA5 (Alternate function push-pull)
 * MISO: PA6 (Input floating / Input pull-up)
 * MOSI: PA7 (Alternate function push-pull)
 */

volatile unsigned char SPI_ReadData;

void SPI_MAINTEST(void)
{

	unsigned char data1[10]= {'H','e','l','l','o'};
	unsigned char data2[10]= {'a','l','o','9','9'};

	//unsigned char ReadData[10]={0};

  InitClockHSE();
  SPI1_Init();
	USART1_Setup_INT_RX();

  Init_TIM2_Delay();

  while (1)
  {
		// SPI1_EnableSlave();
		// SPI1_SendData(&data1,sizeof(data1));
		// SPI1_DisableSlave();
		
		//USART1_SendData(&data1,sizeof(data1));
		//Delay_TIM2_ms(1000);

		//SPI1_EnableSlave();
		//SPI1_ReadData(&SPI_ReadData, sizeof(SPI_ReadData));
		//SPI1_DisableSlave();

		//USART1_SendData(&SPI_ReadData,sizeof(SPI_ReadData));

    // SPI1_EnableSlave();
    // //SPI1_Write(0x34);
		// SPI1_SendData(&data1,sizeof(data1));
    // SPI1_DisableSlave();
    // Delay_TIM2_ms(1000);
		
		// SPI1_EnableSlave();
    // // SPI1_Write(0x99);
		// SPI1_SendData(&data2,sizeof(data2));
    // SPI1_DisableSlave();
		// Delay_TIM2_ms(500);
  }
  
}

void SPI1_Init(void) 
{
  Enable_Disable_Clock_PortA(Enable);
  Clock_AFIO(Enable);
  Clock_SPI1(Enable);

	// NSS
  SetPinOutput(PORTA,PIN4,PushPull);
	// SCK
  SetPinOutput(PORTA,PIN5,Alternate_PushPull);
	// MISO
  SetPinInput(PORTA,PIN6,FloatingInput,PullUp);
	// MOSI
  SetPinOutput(PORTA,PIN7,Alternate_PushPull);

	// SPI1
	SPI1->CR1 = 0; /* Reset */

	/* Master or slave config */
	SPI1->CR1 &= ~(1u<<2);
	#ifdef Master_Config
	SPI1->CR1 |= (1u<<2);			
	#endif

	/* Baudrate config */
	SPI1->CR1 &= ~(7u<<3); 
	#ifndef Baudrate_Div2
	SPI1->CR1 |= Baudrate;
	#endif

	/* Full Duplex or Receive only config */
	SPI1->CR1 &= ~(1u<<10);
	#ifdef Recieve_Only
	SPI1->CR1 |= (1u<<10);
	#endif

	SPI1->CR1 |= (1u<<8);		/* SSI: Internal slave select */
	/* Software slave management config */
	SPI1->CR1 &= ~(1u<<9);
	#ifdef SOFT_SLAVE_ENABLE
	SPI1->CR1 |= (1u<<9);				
	#endif
	
	/* Set 8 or 16 bit Data */
	SPI1->CR1 &= ~(1u<<11);   
  #ifdef SPI1_16_BIT_FORMAT
	SPI1->CR1 |= (1u<<11);		
	#endif

	SPI1->CR2 |= (1u<<6); /* RX interrupt */

	NVIC_SetPriority(SPI1_IRQn,0);
	NVIC_EnableInterrupt(SPI1_IRQn);

	SPI1_Enable();

	SPI1_DisableSlave();
}

void SPI1_Enable(void)
{
  SPI1->CR1 |= (1u<<6);					// 1: Peripheral enabled
}

void SPI1_Disable(void)
{
  SPI1->CR1 &= ~(1u<<6);					// 1: Peripheral Disable
}

void SPI1_EnableSlave(void) 
{
	GPIO_A->GPIO_BRR |= (1u<<4);					// 1: Reset the corresponding ODRx bit
}

void SPI1_DisableSlave(void) 
{
	GPIO_A->GPIO_BSRR |= (1u<<4);				// 1: Set the corresponding ODRx bit
}

void SPI1_SendData(unsigned char *Data, const unsigned int Len)
{
	unsigned int i=0;
	for(i=0;i<Len;i++)
	{
		if(*Data != '\0')
		{
			while ( !(SPI1->SR & (1u<<1)) );			// 0: Tx buffer not empty
			SPI1->DR = *Data;
		}
		else continue;
		Data++;
	}
	while ( !(SPI1->SR & (1u<<1)) );		// 0: Tx buffer not empty
	while ( ((SPI1->SR) & (1u<<7)) );				// 1: SPI (or I2S) is busy in communication or Tx buffer is not empty

	unsigned int Tempread = SPI1->DR;
	Tempread = SPI1->SR;
}

void SPI1_ReadData(unsigned char *Data, const unsigned int Len)
{
	unsigned int i=0;
	for(i=0;i<Len;i++)
	{
		while ( ((SPI1->SR) & (1u<<7)) );
		SPI1->DR = 0;

		while ( !((SPI1->SR) &(1<<0)) );
		*Data = (unsigned char)(SPI1->DR);

		Data++;
	}
}

void SPI1_IRQHandler(void)
{
	SPI_ReadData = (unsigned char)(SPI1->DR);

	SPI1_DisableSlave();

	USART1_SendData(&SPI_ReadData,sizeof(SPI_ReadData));
}




