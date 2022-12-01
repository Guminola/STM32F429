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
#include "stm32f4xx_adc.h"
#include "assert.h"												
#include "delay.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "init_GPIO.h"
#include "init_LCD.h"
#include "init_USART.h"
#include "init_Interrupt.h"
#include <stdio.h> 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint32_t n;
extern uint8_t Linea;
uint16_t line_num =0;

extern __IO uint16_t DATA_USART;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
	Init_GPIO();
	Init_LCD();
	Init_USART();
	
	while(1){
		Linea = 3;
		LCD_SetTextColor(LCD_COLOR_WHITE);
		
		printf("USART1= %c\n",DATA_USART);
		
		delay_ms(2000);
	
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		USART_SendData(USART1, 'H');
		while (!(USART1->SR & USART_FLAG_TXE));
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
