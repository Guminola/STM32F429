/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	

#include "stm32F4xx_adc.h"
#include "Init_ADC.h"
#include "Init_Interrupt.h"

/* Private define ------------------------------------------------------------*/
//#define Avg_slope				2.5
//#define ADC_resolution	4096
//#define Vref						3
//#define V25							760
//#define AdjTemp					16

/* Private functions ---------------------------------------------------------*/
void Init_ADC(void){
	
	ADC_CommonInitTypeDef		ADC_Common;
	ADC_InitTypeDef					ADC_InitValue;
	
	RCC_HSICmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_Common.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonStructInit(&ADC_Common);
	
	ADC_InitValue.ADC_Resolution = ADC_Resolution_12b;
	
	ADC_InitValue.ADC_ContinuousConvMode = DISABLE;
	
	ADC_InitValue.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	
	ADC_InitValue.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_InitValue.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitValue);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_144Cycles);
	
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	Init_ADC_Interrupt(); 
	
	ADC_TempSensorVrefintCmd(ENABLE);
	
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}