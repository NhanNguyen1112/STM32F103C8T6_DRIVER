
#ifndef __DS3231__
#define __DS3231__

#include "STM32F103C8T6_Register.h"
#include "I2C.h"

typedef struct 
{
  unsigned char Day;
  unsigned char Date;
  unsigned char Month;
  unsigned char Year;
  
  unsigned char Hour;
  unsigned char Min;
  unsigned char Seconds;
}DS3231_TIME;

extern DS3231_TIME TIME;

void DS3231_MAIN_TEST(void);

void DS3231_Init(unsigned char Address);
void DS3231_SetTime(unsigned char Day, unsigned char Date, unsigned char Month, unsigned char Year, \
                    unsigned char Hour, unsigned char Min, unsigned char Seconds);
void DS3231_GetTime(DS3231_TIME *GetTime);

#endif
