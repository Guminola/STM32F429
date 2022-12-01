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

//#include "assert.h"												
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"
//#include <stdio.h> 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TP_Config(void);

/* Private functions ---------------------------------------------------------*/
int main(void){
	uint16_t linenum = 0;				//Numero de linea
	static TP_STATE* TP_State;	//Informacion touch panel
	
	/*Configuracion del LCD*/
	LCD_Init();
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	
	/*Configuracion del Touch_Pad)*/
	TP_Config();
	
	while(1){
		TP_State = IOE_TP_GetState();
		
		if((TP_State -> TouchDetected) && ((TP_State->Y < 237) && (TP_State->Y >= 3))){
			if((TP_State->X >= 237) || (TP_State->X < 3)){}	
			else LCD_DrawFullCircle(TP_State->X, TP_State->Y, 3);
		}
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 250) && (TP_State->Y <= 280) && (TP_State->X >= 5) && (TP_State->X <= 35))
			LCD_SetTextColor(LCD_COLOR_BLUE2);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 250) && (TP_State->Y <= 280) && (TP_State->X >= 40) && (TP_State->X <= 70))
			LCD_SetTextColor(LCD_COLOR_CYAN);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 250) && (TP_State->Y <= 280) && (TP_State->X >= 75) && (TP_State->X <= 105))
			LCD_SetTextColor(LCD_COLOR_YELLOW);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 285) && (TP_State->Y <= 315) && (TP_State->X >= 5) && (TP_State->X <= 35))
			LCD_SetTextColor(LCD_COLOR_RED);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 285) && (TP_State->Y <= 315) && (TP_State->X >= 40) && (TP_State->X <= 70))
			LCD_SetTextColor(LCD_COLOR_BLUE);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 285) && (TP_State->Y <= 315) && (TP_State->X >= 75) && (TP_State->X <= 105))
			LCD_SetTextColor(LCD_COLOR_GREEN);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 285) && (TP_State->Y <= 315) && (TP_State->X >= 110) && (TP_State->X <= 140))
			LCD_SetTextColor(LCD_COLOR_MAGENTA);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 285) && (TP_State->Y <= 315) && (TP_State->X >= 145) && (TP_State->X <= 175))
			LCD_SetTextColor(LCD_COLOR_BLACK);
		
		else if ((TP_State -> TouchDetected) && (TP_State->Y >= 272) && (TP_State->Y <= 317) && (TP_State->X >= 178) && (TP_State->X <= 237)){
			LCD_SetFont(&Font8x8);
			for(linenum = 0; linenum < 30; linenum++){
				LCD_ClearLine(LINE(linenum)); 
			}
		}
	}	
}
    
static void TP_Config(void){
	LCD_Clear(LCD_COLOR_WHITE);
	
	if(IOE_Config() == IOE_OK){ //Comprueba que el IO Expander tiene comunicacion
		LCD_SetFont(&Font8x8);
		
		LCD_DisplayStringLine(LINE(32),(uint8_t*)"                Touch Panel");
		LCD_DisplayStringLine(LINE(33),(uint8_t*)"                Paint");
		
		/*Recuadros de colores*/
		LCD_SetTextColor(LCD_COLOR_BLUE2);
		LCD_DrawFullRect(5,250,30,30);
		
		LCD_SetTextColor(LCD_COLOR_CYAN);
		LCD_DrawFullRect(40,250,30,30);
		
		LCD_SetTextColor(LCD_COLOR_YELLOW);
		LCD_DrawFullRect(75,250,30,30);
		
		LCD_SetTextColor(LCD_COLOR_RED);
		LCD_DrawFullRect(5,285,30,30);
		
		LCD_SetTextColor(LCD_COLOR_BLUE);
		LCD_DrawFullRect(40,285,30,30);
		
		LCD_SetTextColor(LCD_COLOR_GREEN);
		LCD_DrawFullRect(75,285,30,30);
		
		LCD_SetTextColor(LCD_COLOR_MAGENTA);
		LCD_DrawFullRect(110,285,30,30);
		
		LCD_SetTextColor(LCD_COLOR_BLACK);
		LCD_DrawFullRect(145,285,30,30);
		
		/*Boton Clear*/
		LCD_DrawRect(178,272,45,59);
		
		/*Marco panel de colores*/
		LCD_DrawRect(2,247,70,235);
		
		LCD_SetFont(&Font16x24);
		LCD_DisplayChar(LCD_LINE_12, 199, 0x43); //C
	
		LCD_DrawLine(3,282,175,LCD_DIR_HORIZONTAL);
		LCD_DrawLine(37,247,70,LCD_DIR_VERTICAL);
		LCD_DrawLine(72,247,70,LCD_DIR_VERTICAL);
		LCD_DrawLine(107,247,70,LCD_DIR_VERTICAL);
		LCD_DrawLine(142,282,35,LCD_DIR_VERTICAL);
	}
	
	else{
		/*Pantalla de error de comunicacion*/
		LCD_SetFont(&Font12x12);
		LCD_Clear(LCD_COLOR_RED);
		LCD_SetTextColor(LCD_COLOR_BLACK);
		
		LCD_DisplayStringLine(LCD_LINE_6,(uint8_t*)"  IOE NO ESTA BIEN ");
		LCD_DisplayStringLine(LCD_LINE_7,(uint8_t*)" REINICIE LA TARJETA ");
		LCD_DisplayStringLine(LCD_LINE_8,(uint8_t*)"  INTENTE DE NUEVO ");
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
