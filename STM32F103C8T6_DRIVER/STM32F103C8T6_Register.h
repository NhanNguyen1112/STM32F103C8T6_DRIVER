
#ifndef __STM32F103C8T6__ 
#define __STM32F103C8T6__

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "GPIO.h"
#include "CLOCK.h"
#include "EXTI.h"
#include "SYSTICK.h"
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

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef struct
{
	uint32_t RCC_CR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_AHBENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
}rcc_typedef;

typedef struct 
{
	uint32_t GPIO_CRL;
	uint32_t GPIO_CRH;
	uint32_t GPIO_IDR;
	uint32_t GPIO_ODR;
	uint32_t GPIO_BSRR;
	uint32_t GPIO_BRR;
	uint32_t GPIO_LCKR;
}GPIO_typedef;

typedef struct
{
	uint32_t AFIO_EVCR;
	uint32_t AFIO_MAPR;
	uint32_t AFIO_EXTICR1;
	uint32_t AFIO_EXTICR2;
	uint32_t AFIO_EXTICR3;
	uint32_t AFIO_EXTICR4;
	uint32_t AFIO_MAPR2;
}AFIO_typedef;

typedef struct
{
	uint32_t EXTI_IMR;
	uint32_t EXTI_EMR;
	uint32_t EXTI_RTSR;
	uint32_t EXTI_FTSR;
	uint32_t EXTI_SWIER;
	uint32_t EXTI_PR;
}EXTI_typedef;

typedef struct 
{
  volatile unsigned int ISER[8u];        
	unsigned int RESERVED_0[24];
  volatile unsigned int ICER[8u];       
  unsigned int RESERVED_1[24];
  volatile unsigned int ISPR[8u];       
  unsigned int RESERVED_2[24];
  volatile unsigned int ICPR[8u];       
  unsigned int RESERVED_3[24];
  volatile unsigned int IABR[8u];       
  unsigned char RESERVED_4[224];
  volatile unsigned char IP[240u];      
  unsigned char RESERVED_5[2576];
  volatile  unsigned int STIR;          
} NVIC_Typedef;

typedef struct
{
	uint32_t SYST_CSR;
	uint32_t SYST_RVR;
	uint32_t SYST_CVR;
	uint32_t SYST_CALIB;
}Systick_typedef;


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
	OpenDrain
}OutputMode_enum;

typedef enum 
{
	AnalogMode,
	FloatingInput,
	InputPullUp_PullDown
}InputMode_enum;

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
#define RCC_BASE_ADDRESS 				((uint32_t)0x40021000u)
#define DMA1_BASE_ADDRESS 			((uint32_t)0x40020000u)
#define DMA2_BASE_ADDRESS 			((uint32_t)0x40020400u)
#define ADC1_BASE_ADDRESS 			((uint32_t)0x40022400u)
#define ADC2_BASE_ADDRESS 			((uint32_t)0x40022800u)
#define ADC3_BASE_ADDRESS 			((uint32_t)0x40023C00u)
#define TIM1_BASE_ADDRESS 			((uint32_t)0x40022C00u)
#define TIM2_BASE_ADDRESS 			((uint32_t)0x40000000u)
#define TIM3_BASE_ADDRESS 			((uint32_t)0x40000400u)
#define TIM4_BASE_ADDRESS 			((uint32_t)0x40000800u)
#define TIM5_BASE_ADDRESS 			((uint32_t)0x40000C00u)
#define TIM6_BASE_ADDRESS 			((uint32_t)0x40001000u)
#define TIM7_BASE_ADDRESS 			((uint32_t)0x40001400u)
#define TIM8_BASE_ADDRESS 			((uint32_t)0x40013400u)
#define TIM9_BASE_ADDRESS 			((uint32_t)0x40014C00u)
#define TIM10_BASE_ADDRESS 			((uint32_t)0x40015000u)
#define TIM11_BASE_ADDRESS 			((uint32_t)0x40015400u)
#define TIM12_BASE_ADDRESS 			((uint32_t)0x40001800u)
#define TIM13_BASE_ADDRESS 			((uint32_t)0x40001C00u)
#define TIM14_BASE_ADDRESS 			((uint32_t)0x40002000u)
#define USART1_BASE_ADDRESS 		((uint32_t)0x40013800u)
#define USART2_BASE_ADDRESS 		((uint32_t)0x40004400u)
#define USART3_BASE_ADDRESS 		((uint32_t)0x40004800u)
#define UART4_BASE_ADDRESS 			((uint32_t)0x40004C00u)
#define UART5_BASE_ADDRESS 			((uint32_t)0x40005000u)
#define I2C1_BASE_ADDRESS 			((uint32_t)0x40005400u)
#define I2C2_BASE_ADDRESS 			((uint32_t)0x40005800u)
#define SPI1_BASE_ADDRESS 			((uint32_t)0x40013000u)
#define SPI2_I2S_BASE_ADDRESS 	((uint32_t)0x40003800u)
#define SPI3_I2S_BASE_ADDRESS 	((uint32_t)0x40003C00u)
#define GPIOA_BASE_ADDRESS 			((uint32_t)0x40010800u)
#define GPIOB_BASE_ADDRESS 			((uint32_t)0x40010C00u)
#define GPIOC_BASE_ADDRESS 			((uint32_t)0x40011000u)
#define GPIOD_BASE_ADDRESS 			((uint32_t)0x40011400u)
#define GPIOE_BASE_ADDRESS 			((uint32_t)0x40011800u)
#define GPIOF_BASE_ADDRESS 			((uint32_t)0x40011C00u)
#define GPIOG_BASE_ADDRESS 			((uint32_t)0x40012000u)
#define EXTI_BASE_ADDRESS 			((uint32_t)0x40010400u)
#define AFIO_BASE_ADDRESS 			((uint32_t)0x40010000u)
#define NVIC_BASE_ADDRESS       ((uint32_t)0xE000E100u)
#define SYSTICK_BASE_ADDRESS    ((uint32_t)0xE000E010u)
/*================================================================================================*/

/*==================================================================================================
*                                        PERIPHERAL ADDRESS
==================================================================================================*/
#define RCC 		((rcc_typedef*)RCC_BASE_ADDRESS)
#define AFIO 		((AFIO_typedef*)AFIO_BASE_ADDRESS)
#define EXTI 		((EXTI_typedef*)EXTI_BASE_ADDRESS)
#define GPIO_A 	((GPIO_typedef*)GPIOA_BASE_ADDRESS)
#define GPIO_B 	((GPIO_typedef*)GPIOB_BASE_ADDRESS)
#define GPIO_C 	((GPIO_typedef*)GPIOC_BASE_ADDRESS)
#define GPIO_D 	((GPIO_typedef*)GPIOD_BASE_ADDRESS)
#define GPIO_E 	((GPIO_typedef*)GPIOE_BASE_ADDRESS)
#define GPIO_F 	((GPIO_typedef*)GPIOF_BASE_ADDRESS)
#define GPIO_G 	((GPIO_typedef*)GPIOG_BASE_ADDRESS)

/*================================================================================================*/

/*==================================================================================================
*                                        CORE ADDRESS
==================================================================================================*/
#define NVIC 				((NVIC_Typedef*)NVIC_BASE_ADDRESS)
#define SYSTICK 		((Systick_typedef*)SYSTICK_BASE_ADDRESS)
/*================================================================================================*/

#endif

