/********************************************************************************
  * @file    main.c 
  * @author  Lenin García Ortiz
  * @version V1.0.0
  * @date    09-March-2022
  * @brief   Main program body
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	

#include "stm32F4xx_adc.h"

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"

#include "Init_GPIO.h"
#include "Init_ADC.h"
#include "Init_Interrupt.h"
#include "delay.h"

#include <stdio.h> 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Avg_slope				2.5
#define ADC_resolution	4095
#define Vref						3
#define V25							760
#define AdjTemp					16

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t Linea;
uint32_t n;

__IO uint16_t ADCdata;
__IO uint16_t Voltaje;
__IO float Temperatura;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
  Init_GPIO();
	
	//Inicializar el LCD
	LCD_Init();
	
	//Habilitar capas
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	
	//Recarga configuraccion LTDC
	LTDC_ReloadConfig(LTDC_IMReload); 
	
	//Habilitar el LCD
	LTDC_Cmd(ENABLE);
	
	//Configuracion del LCD
	LCD_LayerInit();
	//Habilitar display LCD
	LCD_DisplayOn();
	//Set foreground layer
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	//clear LCD
	LCD_Clear(LCD_COLOR_BLACK);
	//LCD back color
	LCD_SetBackColor(LCD_COLOR_BLACK);
	//LCD text color
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12x12);
	
	Init_ADC();
	
	while(1){
		Linea = 3;
		
		LCD_SetTextColor(LCD_COLOR_WHITE);
		
		ADCdata = ADC_GetConversionValue(ADC1);
		
		Voltaje = (ADCdata*1000/ADC_resolution)*Vref;
		
		Temperatura = ((Voltaje-V25/(float)Avg_slope)+25-AdjTemp)/10-20;
		
		printf("ADCdata = %d bits\n",ADCdata); 
		Linea = 5;
		printf("mVolts  = %d mV\n",Voltaje);
		Linea = 7;
		printf("Temp*C  = %2.2f*C\n",Temperatura);

		delay_ms(3000); 
		ADC_SoftwareStartConv(ADC1);
	}
}
    

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reportar del nombre del archivo fuente y el número de línea
  *			donde se "declara o mantiene" algún parámetro con error.
  * @param  file: Apunta al nombre del archivo fuente
  * @param  line: Número de líne que contiene el error.
  * @retval Ninguno
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* El usuario podrá agregar su propia implementación para reportar el nombre
  	 del archivo y el número de línea,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) 
	*/

  /* lazo infinito */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT 2011 Moran Technologies *****END OF FILE****/
