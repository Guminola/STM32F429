/* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_adc.h"

#include "init_Interrupt.h"

EXTI_InitTypeDef	EXTI_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;

void Init_ADC_Interrupt(void){
	// Habilita y configura en el NVIC la interrupcion del ADC1
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Init_USART_Interrupt(void){
	// Habilita y configura en el NVIC la interrupcion del ADC1
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}