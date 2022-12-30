#include "delay.h"
#include <stdbool.h>

volatile uint32_t counter_ms = 0;
extern volatile bool EVENT_1HZ;
extern volatile bool EVENT_10HZ;
extern volatile bool EVENT_100HZ;
extern volatile bool EVENT_1000HZ;

void SysTick_Handler(void)
{
	counter_ms++;
	if (counter_ms % 1000 == 0) {
		EVENT_1HZ = true;
	}
	if (counter_ms % 100 == 0) {
		EVENT_10HZ = true;
	}
	if (counter_ms % 10 == 0) {
		EVENT_100HZ = true;
	}
	EVENT_1000HZ = true;
}

void stk_init(void)
{
	/* SysTick config for 1kHz freq (1ms delay) */
	SysTick->LOAD  = (uint32_t) (F_CPU/1000 - 1);
	SysTick->VAL   = 0UL;
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	
	/* Enable SysTick interrupts */
  NVIC_EnableIRQ(SysTick_IRQn);
	
	/* Enable DWT */
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
}

void delay_ms(uint32_t ms)
{
	uint32_t end = counter_ms + ms;
	while (end > counter_ms);
}

void delay_us(volatile uint32_t us)
{
	uint32_t startTick  = DWT->CYCCNT;
	uint32_t targetTick = startTick + us * (F_CPU/1000000);

	if (targetTick > startTick) {
		while (DWT->CYCCNT < targetTick);
	} else {
		while (DWT->CYCCNT > startTick || DWT->CYCCNT < targetTick);
	}
}
