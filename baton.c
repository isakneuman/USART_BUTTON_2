#include "baton.h"

volatile uint8_t button_state=0;

void check_button(void){
	static uint32_t button_count;
	if( GPIOA->IDR & GPIO_IDR_IDR6 ){
		button_count++;
	}
	else{
			if( (button_count>SHORT_DURATION) && (button_count<LONG_DURATION_LOW) ){
				button_count = 0;
				button_state = 2;
			}
			else if( button_count>LONG_DURATION_LOW ){
				button_count = 0;
				button_state = 3;
			}
			else if( (button_count<SHORT_DURATION) ){
				if( (button_state!=1) )
					button_state = 1;	
				button_count = 0;
			}
	}
}

inline uint8_t get_button_state(void){
	return button_state;
}

/*
		External interrupts, which I did not use for the button.
void EXTI9_5_IRQHandler(void){
	
	if(EXTI->PR & EXTI_PR_PR6){
		static uint32_t last_interrupt;
		uint32_t start_interrupt = ticks_delay;
		if( (start_interrupt - last_interrupt)>200 ){
			toggle_led();
		}
		last_interrupt = start_interrupt;
		EXTI->PR |= EXTI_PR_PR6;
	}
}	
*/

void init_button(void){
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	// IOPAEN: IO port B clock enable
	
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPAEN;
	
	// Port Configuration Register high (GPIOx_CRH) (x=A..G)
	
	GPIOA->CRL &= ~GPIO_CRL_MODE6;
  GPIOA->CRL |= GPIO_CRL_CNF6_0;
  GPIOA->CRL &= ~GPIO_CRL_CNF6_1;
	
/*
	External interrupts, which I did not use for the button.
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	// 1: Interrupt request from Line x is not masked
	EXTI->IMR |= EXTI_IMR_MR6;
	// 1: Rising trigger enabled (for Event and Interrupt) for input line.
	EXTI->RTSR |= EXTI_RTSR_TR6;
	// 1: Falling trigger enabled (for Event and Interrupt) for input line.
	EXTI->FTSR &= ~EXTI_FTSR_TR6;
*/
}
