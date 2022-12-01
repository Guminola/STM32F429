/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"

#include "stm32f4xx_gpio.h"

/* Private define ------------------------------------------------------------*/
#define LED_Green		GPIO_Pin_13		
#define LED_Red			GPIO_Pin_14		

#define USART1_TX		GPIO_Pin_9		
#define USART1_RX		GPIO_Pin_10		

/* Private function prototypes -----------------------------------------------*/
void Init_GPIO(void);