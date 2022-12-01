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
#include "math.h"												
#include "stdio.h"
#include "stdlib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PI 3.1415926

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t n;
uint8_t Y;
float RAD;

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
		//Dibujo del margen
		LCD_DrawLine(1, 1, 238, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(120, 1, 318, LCD_DIR_VERTICAL);
		
		for(n=0;n<200;n++){
			RAD=((n*2.3*PI)*(PI/180)); //Conversion grados a radianes
			Y=((RAD*sin(RAD))*PI)+120; //y=x*sin(x), ajuste para pantalla
			
			LCD_DrawLine(Y,n+1,1,LCD_DIR_VERTICAL);
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
