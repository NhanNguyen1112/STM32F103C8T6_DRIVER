
#include "DS3231.h"

static unsigned char DS3231_ADDRESS=0;

DS3231_TIME TIME;

void DS3231_MAIN_TEST(void)
{
  InitClockHSE(); /* 72Mhz */
  USART1_Setup_INT_RX();
  Init_TIM2_Delay();
  I2C1_Init(I2C_FAST);

  DS3231_Init(0xD0);
	
	// DS3231_SetTime(2,13,8,23,9,27,23);

  unsigned char databuffer[50]={0};

  while(1)
  {
    DS3231_GetTime(&TIME);
    sprintf(&databuffer,"D: %d/%d/%d/%d - T: %d:%d:%d \n", TIME.Day, TIME.Date, TIME.Month, TIME.Year, TIME.Hour, TIME.Min, TIME.Seconds);
    USART1_SendData(databuffer,sizeof(databuffer));
		Delay_TIM2_ms(1000);
  }
}

void DS3231_Init(unsigned char Address)
{
  DS3231_ADDRESS=Address;
}

static unsigned char DECtoBCD(unsigned char val)
{
  return (unsigned char)( (val/10*16) + (val%10) );
}

static unsigned char BCDtoDEC(unsigned char val)
{
  return (unsigned char)( (val/16*10) + (val%16) );
}

void DS3231_SetTime(unsigned char Day, unsigned char Date, unsigned char Month, unsigned char Year, unsigned char Hour, unsigned char Min, unsigned char Seconds)
{
  unsigned int i=0;
  unsigned char TimeBuffer[7];
  TimeBuffer[0] = DECtoBCD(Seconds);
  TimeBuffer[1] = DECtoBCD(Min);
  TimeBuffer[2] = DECtoBCD(Hour);

  TimeBuffer[3] = DECtoBCD(Day);
  TimeBuffer[4] = DECtoBCD(Date);
  TimeBuffer[5] = DECtoBCD(Month);
  TimeBuffer[6] = DECtoBCD(Year);

  for(i=0;i<=500000;i++);
  I2C1_WriteMEM(DS3231_ADDRESS,0x00,TimeBuffer,sizeof(TimeBuffer));
  for(i=0;i<=500000;i++);
}

void DS3231_GetTime(DS3231_TIME *GetTime)
{
  unsigned char TimeBuffer[7];
  I2C1_ReadMEM(DS3231_ADDRESS,0x00,TimeBuffer,sizeof(TimeBuffer),I2C_ACK);

  GetTime->Day = BCDtoDEC(TimeBuffer[3]);
  GetTime->Date = BCDtoDEC(TimeBuffer[4]);
  GetTime->Month = BCDtoDEC(TimeBuffer[5]);
  GetTime->Year = BCDtoDEC(TimeBuffer[6]);

  GetTime->Hour = BCDtoDEC(TimeBuffer[2]);
  GetTime->Min = BCDtoDEC(TimeBuffer[1]);
  GetTime->Seconds = BCDtoDEC(TimeBuffer[0]);
}


