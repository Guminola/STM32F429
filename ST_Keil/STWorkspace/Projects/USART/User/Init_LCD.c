/* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "stm32f4xx.h"

//#include "stm32f429i_discovery.h"
//#include "stm32f429i_discovery_lcd.h"
#include "Init_LCD.h"

/* Private functions ---------------------------------------------------------*/
void Init_LCD(void)
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
	LCD_SetFont(&Font12x12);
}