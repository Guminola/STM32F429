/* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "stm32f4xx.h"

//#include "stm32f4xx_usart.h"		

#include "init_USART.h"

/* Private macro -------------------------------------------------------------*/
USART_InitTypeDef USART_InitStruct;

/* Private functions ---------------------------------------------------------*/
void Init_USART(void)
{
	//Habilitacion el reloj para el USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//Configuacion del USART
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	
	USART_Cmd(USART1, ENABLE);
	
	// Habilitar interrupcion de recepcion
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	// Habilita y configura en el NVIC la interrupcion del USART 
	Init_USART_Interrupt();
}
