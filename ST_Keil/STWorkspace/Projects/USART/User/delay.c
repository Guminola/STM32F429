#include "main.h"
#include "stm32f4xx.h"	

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
extern volatile uint32_t msTicks;
uint32_t curTicks;

/* Private function prototypes -----------------------------------------------*/

void delay_ms(uint32_t nCount){
	
	nCount=nCount/2;
	
	/* Habilitación de reloj del periférico SYSCFG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock/1600)){
		while(1);
	}
	
	curTicks = msTicks;
	while ((msTicks - curTicks)<nCount);
}
