
#include "ADC.h"

void ADC_MAIN_TEST(void)
{
  InitClockHSE(); /* 72Mhz */
  USART1_Setup_INT_RX();
  Init_TIM2_Delay();

  ADC1_Init_CH1();  

  Enable_Disable_Clock_PortA(Enable);
  SetPinInput(PORTA,PIN0,AnalogMode,No);
  SetPinInput(PORTA,PIN1,AnalogMode,No);

  unsigned short ADC_VAL;

  while (1)
  {
    ADC1->ADC_CR2 |= (1u<<22); /* Start convertion */
    ADC_VAL = ADC1_GetVal();
		
    //USART1_SendData(&ADC_VAL,sizeof(ADC_VAL));
		Delay_TIM2_ms(50);
  }
  
}

// void ADC1_2_IRQHandler(void)
// {
// 	// ADC_VAL = (unsigned short)ADC1->ADC_DR;
// }

void ADC1_Init_CH1(void)
{
  ADC_EnableClock(1,Enable,6); /* ADC1, 72/6= 12Mhz */

  ADC1->ADC_SMPR2 &= ~(7u<<0); /* Clear CH0 */
  ADC1->ADC_SMPR2 |= (2u<<0); /* CH0: Set 13.5 cycles */
  // ADC1->ADC_SMPR2 &= ~(7u<<3); /* Clear CH1 */
  // ADC1->ADC_SMPR2 |= (2u<<3); /* CH1: Set 13.5 cycles */

  // ADC1->ADC_SQR3 &= ~(0x1FUL<<0); /* Clear SQ1 */
  // ADC1->ADC_SQR3 &= ~(0x1FUL<<5); /* Clear SQ2 */
  // ADC1->ADC_SQR3 |= (1u<<5); /* SQ2 Set CH1 */

  // ADC1->ADC_SQR1 &= ~(0xFu<<20); /* Clear L */
  // ADC1->ADC_SQR1 |= (1<<20); /* L = 2 conversion */

  // ADC1->ADC_CR1 &= ~(1u<<8); /* SCAN Disable */
  // ADC1->ADC_CR1 |= (1u<<8); /* SCAN enable */

  // ADC1->ADC_CR1 |= (1u<<5); /* EOCIE Enable */

  // ADC1->ADC_CR2 &= ~(1u<<1); /* Single conversion */
  ADC1->ADC_CR2 |= (1u<<1); /* Continue conversion */

  ADC1->ADC_CR2 &= ~(1u<<11); /* Data Right alignment */
  // ADC1->ADC_CR2 |= (1u<<11); /* Data Left alignment */

  // ADC1->ADC_CR2 |= (7u<<17);
	
  ADC1->ADC_CR2 |= (1u<<0); /* ADC Enable */
  Delay_TIM2_ms(1000);

  // NVIC_SetPriority(ADC1_2_IRQn,0);
  // NVIC_ClearPendingFlag(ADC1_2_IRQn);
  // NVIC_EnableInterrupt(ADC1_2_IRQn);

}

unsigned short ADC1_GetVal(void)
{
  //while( !(ADC1->ADC_SR & (1u<<1)) ); /* Wait EOC flag set */
  return ADC1->ADC_DR;
}






