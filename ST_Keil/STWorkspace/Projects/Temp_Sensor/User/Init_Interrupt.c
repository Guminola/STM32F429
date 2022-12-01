/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	

#include "stm32F4xx_adc.h"
#include "Init_Interrupt.h"

/* Private typedef -----------------------------------------------------------*/
EXTI_InitTypeDef EXTI_InitStructure;
extern NVIC_InitTypeDef  NVIC_InitStructure;

/* Private functions ---------------------------------------------------------*/
void Init_ADC_Interrupt(void){
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}