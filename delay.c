#include "delay.h"

volatile uint32_t ticks_delay = 0;

inline uint32_t get_ms(void){
	return ticks_delay;
}

void SysTick_Handler(void){
	ticks_delay++;
	check_button();
}

void delay_ms(const uint32_t ms){
	// saving the entry time
	uint32_t start = ticks_delay;
	// wait until the time we need passes from the moment of entry
	while((ticks_delay - start) < ms);
}

void init_systick(void){
	
	/* It is configured inside
	SysTick->LOAD  = (uint32_t)(ticks - 1UL);                          set reload register 
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);  set Priority for Systick Interrupt 
  SysTick->VAL   = 0UL;                                              Load the SysTick Counter Value 
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                          Enable SysTick IRQ and SysTick Timer 
	*/ 
	SysTick_Config(SystemCoreClock/1000); // Time for 1 ms
	
}
