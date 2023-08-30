
#ifndef __STM32F103C8T6__ 
#define __STM32F103C8T6__

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "GPIO.h"
#include "CLOCK.h"
#include "EXTI.h"
#include "SYSTICK.h"
#include "Softtimer.h"
#include "Timer.h"
#include "USART.h"
#include "NVIC.h"
#include "I2C.h"
#include "PCF8574.h"
#include "SPI.h"
#include "ADC.h"
#include "DMA.h"
#include "String.h"

#include "UART_V2.h"

/*================================================================================================*/

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/
#define SETBIT(REG,VALUE,BIT) ((REG) |= (VALUE<<BIT))
#define CLEARBIT(REG,VALUE,BIT) ((REG) &= ~(VALUE<<BIT))
#define READBIT(REG,BIT) ((REG) & (1<<BIT))
#define SETALL(REG) ((REG) |= (0xFFFFFFFF))
#define CLEARALL(REG) ((REG) &= (0x00000000))

/*================================================================================================*/

/*==================================================================================================
*                                        STRUCTURES AND TYPEDEF
==================================================================================================*/

typedef unsigned int 		uint32_t;
typedef unsigned short 	uint16_t;
typedef unsigned char 	uint8_t;

/*================================================================================================*/

/*==================================================================================================
*                                        ENUMS
==================================================================================================*/
typedef enum 
{
	LOW,
	HIGH
}DigitalState_enum;

typedef enum
{
	Disable,
	Enable
}SetClear_enum;

typedef enum 
{
	PushPull,
	OpenDrain,
	Alternate_PushPull,
	Alternate_OpenDrain
}OutputMode_enum;

typedef enum 
{
	AnalogMode,
	FloatingInput,
	InputPullUp_PullDown
}InputMode_enum;

typedef enum 
{
	No,
	PullUp,
	PullDown
}UpDown_enum;

typedef enum 
{
	OUTPUT,
	INPUT
}PinMode_enum;

typedef enum 
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG
}PORT_enum;

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PortPin_enum;

/*================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/*================================================================================================*/

/*==================================================================================================
*                                        FUNCTION PROTOTYPES
==================================================================================================*/
/*================================================================================================*/

/*==================================================================================================
*                                        BASE ADDRESS
==================================================================================================*/

/*================================================================================================*/

/*==================================================================================================
*                                        PERIPHERAL ADDRESS
==================================================================================================*/
/*================================================================================================*/

/*==================================================================================================
*                                        CORE ADDRESS
==================================================================================================*/

/*================================================================================================*/

#endif

