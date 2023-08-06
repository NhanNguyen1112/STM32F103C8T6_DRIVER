
#include "I2C.h"

/* PB6:SCL - PB7:SDA */
void I2C1_SetPin(void)
{
  Enable_Disable_Clock_PortB(Enable);
  SetPinOutput(PORTB,PIN6,Alternate_OpenDrain);
  SetPinOutput(PORTB,PIN7,Alternate_OpenDrain);

  AFIO->AFIO_MAPR &= ~(1u<<1); /* No remap */
}

void I2C1_Init(void)
{
  I2C1_EnableClock(Enable);


}
