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
												
#include "stdio.h"
#include "stdlib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t n;
uint8_t linea;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
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
	
	while(1){
		//Dibuja margen
		LCD_DrawLine(5, 5, LCD_PIXEL_WIDTH-10, LCD_DIR_HORIZONTAL); 
		LCD_DrawLine(5, 315, LCD_PIXEL_WIDTH-10, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(5, 5, LCD_PIXEL_HEIGHT-10, LCD_DIR_VERTICAL);
		LCD_DrawLine(235, 5, LCD_PIXEL_HEIGHT-10, LCD_DIR_VERTICAL);
		
		//dibuja random lines
		for(n=0;n<100;n++){
			//funcion random con rango -> rand()% (MAX_R + 1 - MIN_R) - MIN_R
			LCD_DrawUniLine(rand()%(LCD_PIXEL_WIDTH-10+1)+5, rand()%(LCD_PIXEL_HEIGHT-10+1)+5, rand()%(LCD_PIXEL_WIDTH-10+1)+5, rand()%(LCD_PIXEL_HEIGHT-10+1)+5);
		}
		while(1);
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
