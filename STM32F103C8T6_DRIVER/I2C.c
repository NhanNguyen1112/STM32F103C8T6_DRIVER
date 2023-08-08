
#include "I2C.h"

static void I2Cdelay(void)
{
	unsigned int i=0;
	for(i=0; i<=100; i++);
}

void Main_I2C1_Test(void)
{
  InitClockHSE(); /* 72Mhz */

  Init_TIM2_Delay();
  

  I2C1_Init();

  while(1)
  {
		I2C_SendData(0x20,0x1);
		for(int i=0; i<=1000000; i++);
		I2C_SendData(0x20,0);
		for(int j=0; j<=1000000; j++);
  }
}

/* PB6:SCL - PB7:SDA */
static void I2C1_SetPin(void)
{
  Enable_Disable_Clock_PortB(Enable);
  SetPinOutput(PORTB,PIN6,Alternate_OpenDrain);
  SetPinOutput(PORTB,PIN7,Alternate_OpenDrain);

  AFIO->AFIO_MAPR &= ~(1u<<1); /* No remap */
}

void I2C1_Init(void)
{
  unsigned int CR1=0; 
	unsigned int CR2=0;
  unsigned int CCR=0;

  I2C1_SetPin();

  I2C1_EnableClock(Enable);

  CR1 |= (1u<<15); /* Reset I2C */
  I2C1->CR1 = CR1;
  CR1=0;
  I2C1->CR1 = CR1;

  CR2 |= (36u<<0); /* Set prequency APB1=36Mhz (MAX) */
  I2C1->CR2 = CR2; 

  CCR |= (1u<<15); /* Fast mode I2C */ 
  CCR |= (1u<<14); /* DUTY cycle */

  /* APB1=36Mhz -> T = 1/36 = 27.777ns
  *  CCR= (1000ns+4000ns)/27.777ns = 180 = 0xB4
  *  Hoac tra bang 41 trang 70 trong Datasheet
  */
  CCR |= (0x801E<<0);
  I2C1->CCR = CCR;

  I2C1->TRISE = 12u; /* 36mhz + 1 */

  CR1 |= (1u<<0); /* Enable I2C */
  I2C1->CR1 = CR1;

}

static void I2C1_Start(void)
{
  I2C1->CR1 |= (1u<<10); /* Enable ACk */
  I2C1->CR1 |= 0x100;  /* Start */
	Delay_TIM2_us(4);
  while ( !(I2C1->SR1 & (1u<<0)) ); /* Wait SB set */
  
}

static void I2C1_Stop(void)
{
  I2C1->CR1 |= (1u<<9); /* Stop I2C */
}

static void I2C1_SendAdress(unsigned char Address)
{
	volatile unsigned int temp=0;
  I2C1->DR = (volatile unsigned int)Address;
	//I2Cdelay();
	Delay_TIM2_us(4);
  while ( !(I2C1->SR1 & (1u<<1)) ); /* wait address send */
  temp = (I2C1->SR1 | I2C1->SR2);
}

void I2C1_Write(unsigned char Data)
{
	I2Cdelay();
  //while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */
  I2C1->DR = (volatile unsigned int)Data;
	I2Cdelay();
  //while( !(I2C1->SR1 & (1u<<2)) ); /* Wait byte transfer finish */
}

void I2C1_WriteMultiData(unsigned char *Data, const unsigned char size)
{
  unsigned char Count=0;

  //while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */
	I2Cdelay();

  for(Count=0; Count<size; Count++)
  {
    //while( !(I2C1->SR1 & (1u<<7)) ); /* wait TxE set 1 -> DR empty */
    I2Cdelay();
		
    I2C1->DR = (volatile unsigned int)*Data;

    Data++;
  }
	
	I2Cdelay();
  //while( !(I2C1->SR1 & (1u<<2)) ); /* Wait byte transfer finish */
}

void I2C_SendData(const unsigned char Address, const unsigned char Data)
{
  I2C1_Start();
  I2C1_SendAdress(Address);
  I2C1_Write(Data);
  I2C1_Stop();
}


