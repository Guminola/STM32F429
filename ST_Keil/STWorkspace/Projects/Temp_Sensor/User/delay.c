#include "main.h"
#include "stm32f4xx.h"	

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
extern volatile uint32_t msTicks;

/* Private function prototypes -----------------------------------------------*/

void delay_ms(uint32_t nCount){
	
	/* Habilitación de reloj del periférico SYSCFG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock/1600)){
		while(1);
	}
	
	uint32_t curTicks;
	
	curTicks = msTicks;
	while ((msTicks - curTicks)<nCount);
}
