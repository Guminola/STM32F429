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
typedef struct{
	uint16_t x;
	uint16_t y;
}ponit;

/* Private define ------------------------------------------------------------*/
#define PI 		3.141592

#define X0 		5
#define Y0 		5

#define NODES 24
#define SIDE	10

#define STEP 	1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct{
	int x;
	int y;
}point;	

ponit edge[NODES], prev; 

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{	
	uint8_t i, j, x, y, z;
	float xf, yf, zf, sf;
	uint16_t px, py;
	uint8_t xoff, scale;
	
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
	
	xoff=120;
	scale=20;
	
	while(1){
		
		LCD_Clear(LCD_COLOR_BLACK);
		
		LCD_DrawUniLine(10, X0, 10, X0);
		LCD_DrawUniLine(Y0, X0-5, Y0, LCD_PIXEL_WIDTH);	
		LCD_DrawUniLine(Y0-2, X0-2, Y0+120, X0+120);				
		
		for (j=0;j<NODES;j++){
			edge[j].x = X0+j*SIDE/2;
			edge[j].y = Y0+j*SIDE/2;
		}
		
		for(i=0;i<NODES;i++){
			x = i*SIDE;
			xf = (6*PI/200)*(float)(x-xoff);
			prev.y = Y0;
			prev.x = X0+x;
		
			for(j=0;j<NODES;j++){
				y=j*SIDE;
				yf=(6*PI/200)*(float)(y-100);
			
				sf=sqrt(xf*xf + yf*yf);
				zf=(cos(sf)+2)*sin(sf/4);
				
				z=zf*scale;
				
				px = X0+x+y/2;
				py = Y0+z+y/2;
				
				LCD_DrawLine(py, px, 1, LCD_DIR_HORIZONTAL);
				
				LCD_DrawUniLine(py,px,prev.y,prev.x);
				LCD_DrawUniLine(py,px,edge[j].y,edge[j].x);
				
				prev.x = px;
				prev.y = py;
				edge[j].x = px;
				edge[j].y = py;
			}
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
