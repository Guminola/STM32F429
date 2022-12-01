/********************************************************************************
  * @file    main.c 
  * @author  Lenin García Ortiz
  * @version V1.0.0
  * @date    09-March-2022
  * @brief   Main program body
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"	//Archivo encabezado para el acceso a los 
												//dispositivos Periféricos del CMSIS Cortex-M4											
#include "assert.h"												
//#include "delay.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"
#include <stdio.h> 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef	GPIO_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t n;
extern uint8_t Linea;
uint16_t line_num =0;
static TP_STATE* TP_State;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
  	/* Habilitación de reloj del periférico GPIOG */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  /* Configurar PG13 y PG14 como Push Pull*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
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
	
	while(IOE_Config() != IOE_OK){
		LCD_Clear(LCD_COLOR_RED);
		LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)"IOE NO ESTA BIEN");
		LCD_DisplayStringLine(LCD_LINE_7, (uint8_t*)"REINICIE LA TARJETA");
		LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)"INTENTE DE NUEVO");
	}
	
	LCD_Clear(LCD_COLOR_BLACK);	
	LCD_SetTextColor(LCD_COLOR_WHITE);
	
	Linea = 17;
	printf("      LED ROJO\n");
	Linea = 23;
	printf("      LED VERDE\n");
	
	LCD_DrawRect(20, 255, 55, 200);
	LCD_DrawRect(20, 180, 55, 200);

	while(1){
		
		TP_State = IOE_TP_GetState();
		
		if((TP_State -> TouchDetected) && (TP_State ->Y <= 310) && (TP_State ->Y >= 255) && (TP_State ->X <= 200) && (TP_State ->X >= 20)){
			
			GPIOG->BSRRL=GPIO_Pin_13;
			GPIOG->BSRRH=GPIO_Pin_14;
			
			LCD_SetTextColor(LCD_COLOR_GREEN);
			Linea = 23;
			printf("      LED VERDE\n");
			
			LCD_SetTextColor(LCD_COLOR_WHITE);
			LCD_DrawRect(20, 255, 55, 200);
			
			Linea = 17;
			printf("      LED ROJO\n");
			LCD_DrawRect(20, 180, 55, 200);
		}	
		
		if ((TP_State -> TouchDetected) && (TP_State ->Y <= 235) && (TP_State ->Y >= 180) && (TP_State ->X <= 200) && (TP_State ->X >= 20)){
			
			GPIOG->BSRRH=GPIO_Pin_13;
			GPIOG->BSRRL=GPIO_Pin_14;
			
			LCD_SetTextColor(LCD_COLOR_RED);
			Linea = 17;
			printf("      LED ROJO\n");
			
			LCD_SetTextColor(LCD_COLOR_WHITE);
			LCD_DrawRect(20, 180, 55, 200);
			
			Linea = 23;
			printf("      LED VERDE\n");
			LCD_DrawRect(20, 255, 55, 200);
		}
		else {};
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
