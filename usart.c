#include "usart.h"

char data1[] = "IDLE\n";
char data2[] = "CLICK\n";
char data3[] = "HOLD\n";
volatile char* current_data_ptr = data1;
volatile char* start_data_ptr = data1;

// Here we select the desired text
// depending on the button state flag
void select_output_data(void){
	switch(button_state){
		case 1:
			start_data_ptr = data1;
			break;
		case 2:
			start_data_ptr = data2;
			break;	
		case 3:
			start_data_ptr = data3;
			break;
		default:
			start_data_ptr = data1;
			break;
	}
}

void USART1_IRQHandler(void){
	
	// Bit 5 RXNE: Read data register not empty
	// 1: Received data is ready to be read.
	
	// USART1->CR1 |= USART_CR1_RXNEIE
	if(USART1->SR & USART_SR_RXNE)
	{
		// Contains the Received or Transmitted data character,
		// depending on whether it is read from or written to.
		toggle_led();
		// RXNE is cleared by a read to the USART_DR register.
		(void)USART1->DR;
	}
	if(USART1->SR & USART_SR_ORE)
	{
		toggle_led();
		(void)USART1->DR;
	}
	
	select_output_data();
	if(USART1->SR & USART_SR_TXE)
	{
		// if it is the end then transfer to the beginning
		if(*current_data_ptr == '\0')
		{
			current_data_ptr = start_data_ptr;
		}
		// if not the end then continue to output moving along the byte pointer
		else
		{
			USART1->DR = *(current_data_ptr++);
		}
	}
}


void USART_get_push(void){
	// Bit 5 RXNE: Read data register not empty
	// 1: Received data is ready to be read.
	if(USART1->SR & USART_SR_RXNE){
		// Contains the Received or Transmitted data character,
		// depending on whether it is read from or written to.
		(void)USART1->DR;
		uint16_t buff = USART1->DR;
		USART1->DR = buff;
		
		// Bit 6 TC: Transmission complete
		while(!(USART1->SR & USART_SR_TC));
	}
}

void init_USART_with_interrupt(void){
	// Alternate function I/O and debug configuration (AFIO)
	// USART1 remapping -> USART1_REMAP = 0; default; TX = PA9, RX = PA10;
	
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	// Because USART1 and GPIOA are located in APB2 that work in (HCLK 72 MHz max)
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Port configuration register high (GPIOx_CRH)
	// TX~PA9 -> 11: Output mode, max speed 50 MHz.
	// TX~PA9 -> 10: Alternate function output Push-pull
	GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	
	// RX~PA10 -> set to input &FLOATING
	
	// for BAUD 9600
	// USARTDIV is 468.75
	// 468 = 0x1D4, 0.75*16=0xC
	USART1->BRR = 0x1D4C;//(uint16_t)SystemCoreClock/9600;
	
	/* Bit 7 TXEIE: TXE interrupt enable
	   TX buffer (data register) is empty
	   1: A USART interrupt is generated whenever TXE=1 in the USART_SR register
	   
		 Bit 5 RXNEIE: RXNE interrupt enable
		 When we have received data
		 1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register
		 
		 Bit 6 TCIE: Transmission complete interrupt enable
		 1: A USART interrupt is generated whenever TC=1 in the USART_SR register
		 This bit is set by hardware if the
		 transmission of a frame containing data is complete and if
		 TXE is set.
	*/
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;// USART_CR1_TCIE;
	
		
	// Nested vectored interrupt controller (NVIC)
	// USART1 global Interrupt enable
	// Use the same exact interrupt handler for: TXEIE, RXNEIE, TCIE
	NVIC_EnableIRQ(USART1_IRQn);
	
	/* 
	   UART enable is the last thing you do.
	   Datasheet states for a lot of peripherals
	   that they must not be enabled until configured.
									RX enable      TX enable     UART enable
	*/
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

void init_USART(void){
	
	// Alternate function I/O and debug configuration (AFIO)
	// USART1 remapping -> USART1_REMAP = 0; default; TX = PA9, RX = PA10;
	
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	// Because USART1 and GPIOA are located in APB2 that work in (HCLK 72 MHz max)
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
	
	// Port configuration register high (GPIOx_CRH)
	// TX~PA9 -> 11: Output mode, max speed 50 MHz.
	// TX~PA9 -> 10: Alternate function output Push-pull
	GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	
	// RX~PA10 -> set to input &FLOATING
	
	// for BAUD 9600
	// USARTDIV is 468.75
	// 468 = 0x1D4, 0.75*16=0xC
	USART1->BRR = 0x1D4C;
	
	/* 
	   UART enable is the last thing you do.
	   Datasheet states for a lot of peripherals
	   that they must not be enabled until configured.
									RX enable      TX enable     UART enable	
	*/
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}
