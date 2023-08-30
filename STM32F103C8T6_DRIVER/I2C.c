
#include "I2C.h"

void Main_I2C1_Test(void)
{
  InitClockHSE(); /* 72Mhz */
  Init_TIM2_Delay();
  I2C1_Init(I2C_STANDARD);

	unsigned char data1[10]= {'H','e','l','l','o'};

  while(1)
  {
		I2C1_SendMultiData(0x27,data1,sizeof(data1));

		// I2C_SendData(0x27,0x1);
		// Delay_TIM2_ms(100);
		// I2C_SendData(0x27,0);
		// Delay_TIM2_ms(100);
  }
}

/* PB6:SCL - PB7:SDA */
static void I2C1_SetPin(void)
{
  Enable_Disable_Clock_PortB(Enable);
	Clock_AFIO(Enable);
  SetPinOutput(PORTB,PIN6,Alternate_OpenDrain);
  SetPinOutput(PORTB,PIN7,Alternate_OpenDrain);

  AFIO->AFIO_MAPR &= ~(1u<<1); /* No remap */
}

void I2C1_Init(I2C_Mode_Type mode)
{
  unsigned int CR1=0; 
	unsigned int CR2=0;

  I2C1_SetPin();
  I2C1_EnableClock(Enable);

  CR1 |= (1u<<15); /* Reset I2C */
  I2C1->CR1 = CR1;
  CR1=0;
  I2C1->CR1 = CR1;

  CR2 |= ((PCLK1_FREQUENCY / 1000000)<<0); /* Set prequency APB1=36Mhz (MAX) */
  I2C1->CR2 = CR2; 

  /* APB1=36Mhz -> T = 1/36 = 27.777ns
  *  CCR= (1000ns+4000ns)/27.777ns = 180 = 0xB4
  *  Hoac tra bang 41 trang 70 trong Datasheet
  */
  if (mode == I2C_STANDARD) 
	{
		I2C1->CCR &= ~(1u<<15);														// 1: Fm mode I2C (Fast mode - 400kHz)
		I2C1->CCR = (PCLK1_FREQUENCY / (100000 * 2));			// CCR[11:0]: Clock control register in Fm/Sm mode (Master mode) 100kHz
		I2C1->TRISE = ((PCLK1_FREQUENCY / 1000000) + 1);	// TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
	} 
	else
	{
		I2C1->CCR |= (1u<<15);										// 1: Fm mode I2C (Fast mode - 400kHz)
		I2C1->CCR = (PCLK1_FREQUENCY / (400000 * 3));					// CCR[11:0]: Clock control register in Fm/Sm mode (Master mode) 400kHz
		I2C1->TRISE = (((PCLK1_FREQUENCY / 1000000 * 300) / 1000) + 1);	// TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
	}

  CR1 |= (1u<<0); /* Enable I2C */
  I2C1->CR1 = CR1;

}

static void I2C1_Start(void)
{
  I2C1->CR1 |= (1u<<8);  /* Start */
  while ( !(I2C1->SR1 & (1u<<0)) ||			/* 0: No Start condition */
					!(I2C1->SR2 & (1u<<0)) ||			/* 0: Slave Mode */
					!(I2C1->SR2 & (1u<<1))				/* 0: No communication on the bus */
	);
}

static void I2C1_Stop(void)
{
  I2C1->CR1 |= (1u<<9); 				/* Stop I2C */
	while((I2C1->SR1 & (1u<<4)));	/* 1: Stop condition detected */
}

static void I2C1_SendAdress(unsigned int Address, I2C_Direction_Type direction)
{
	unsigned int temp=0;
	
	if (direction == I2C_TRANSMITTER) 
	{
		Address &= ~(1u << 0);						// Reset the address bit0 for write
		I2C1->DR = Address;
		while ( !((I2C1->SR1) & (1u<<1)) ); /* wait address send */		
	} 
	else /* Receiver */
	{
		Address |= (1u << 0);						// Set the address bit0 for read
		I2C1->DR = Address;
		while ( !(I2C1->SR1 & (1u<<1)) ); /* wait address send */
	}
	temp = I2C1->SR1;
	temp = I2C1->SR2;
}

static void I2C1_Write(unsigned char Data)
{
  while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */
  I2C1->DR = Data;
  while( !(I2C1->SR1 & (1u<<2)) ); /* Wait byte transfer finish */
}

static unsigned char I2C1_Read(I2C_Acknowledge_Type acknowledge)
{
	if (acknowledge == I2C_ACK) 
	{
		I2C1->CR1 |= (1u<<10);					// 1: Acknowledge returned after a byte is received (matched address or data)
	} 
	else /* NACK */
	{
		I2C1->CR1 &= ~(1u<<10);					// 0: No acknowledge returned
	}

	while ( !(I2C1->SR1 & (1u<<6)) ); /* RX Data not empty */
	return ((unsigned char)I2C1->DR);
}

static void I2C1_WriteMultiData(unsigned char *Data, const unsigned char size)
{
  unsigned char Count=0;

	while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */

  for(Count=0; Count<size; Count++)
  {
    while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */
		
    I2C1->DR = (unsigned int)*Data;

    Data++;
  }
	
  while( !(I2C1->SR1 & (1u<<2)) ); /* Wait byte transfer finish */
}

void I2C1_SendData(const unsigned char Address, const unsigned char Data)
{
  I2C1_Start();
  I2C1_SendAdress(Address,I2C_TRANSMITTER);
  I2C1_Write(Data);
  I2C1_Stop();
}

void I2C1_SendMultiData(const unsigned char Address, unsigned char *Data, unsigned char size)
{
  I2C1_Start();
  I2C1_SendAdress(Address,I2C_TRANSMITTER);
  I2C1_WriteMultiData(Data,size);
  I2C1_Stop();
}

void I2C1_WriteMEM(const unsigned char AddressI2C, const unsigned char AddressMEM, unsigned char *Data, unsigned char size)
{
  I2C1_Start();
  I2C1_SendAdress(AddressI2C,I2C_TRANSMITTER);
	I2C1_Write(AddressMEM);
  I2C1_WriteMultiData(Data,size);
  I2C1_Stop();
}

unsigned char I2C1_ReadData(const unsigned char Address, I2C_Acknowledge_Type acknowledge)
{
	unsigned char DataRead=0;
	I2C1_Start();
	I2C1_SendAdress(Address,I2C_RECEIVER);
	DataRead = I2C1_Read(acknowledge);
	(void)I2C1_Read(I2C_NACK);
	I2C1_Stop();

	return DataRead;
}

void I2C1_ReadMultiData(const unsigned char Address, unsigned char *DataRead, unsigned char size, I2C_Acknowledge_Type acknowledge)
{
	unsigned char i=0;

	I2C1_Start();
	I2C1_SendAdress(Address,I2C_RECEIVER);

	for(i=0; i<size; i++)
	{
		*DataRead = I2C1_Read(acknowledge);
		DataRead++;
	}
	(void)I2C1_Read(I2C_NACK);

	I2C1_Stop();
}

void I2C1_ReadMEM(const unsigned char AddressI2C, const unsigned char AddressMEM, \
									unsigned char *DataRead, unsigned char size, I2C_Acknowledge_Type acknowledge)
{
	unsigned char i=0;

	I2C1_Start();
	I2C1_SendAdress(AddressI2C,I2C_TRANSMITTER);
	I2C1_Write(AddressMEM);
	I2C1_Stop();

	I2C1_Start();
	I2C1_SendAdress(AddressI2C,I2C_RECEIVER);
	for(i=0; i<size; i++)
	{
		*DataRead = I2C1_Read(acknowledge);
		DataRead++;
	}
	i = I2C1_Read(I2C_NACK);
	I2C1_Stop();
}



