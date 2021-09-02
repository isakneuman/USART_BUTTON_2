#include "led.h"

void toggle_led(void){
	// Port output data register (GPIOx_ODR) (x=A..G)
	GPIOB->ODR	^=	GPIO_ODR_ODR12;
}
void toggle_led2(void){
	// Port output data register (GPIOx_ODR) (x=A..G)
	GPIOC->ODR	^=	GPIO_ODR_ODR13;
	delay_ms(200);
}

void init_led2(void){
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	// IOPCEN: IO port C clock enable
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;
	
	// Port Configuration Register high (GPIOx_CRH) (x=A..G)
	
	// MODEy[1:0]: Port x mode bits (y= 8 .. 15) 
	GPIOC->CRH	|=	GPIO_CRH_MODE13_0;
	GPIOC->CRH	&=	~GPIO_CRH_MODE13_1;
	// CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	GPIOC->CRH	&=	~GPIO_CRH_CNF13;
}

void init_led(void){
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	// IOPCEN: IO port C clock enable
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
	
	// Port Configuration Register high (GPIOx_CRH) (x=A..G)
	
	// MODEy[1:0]: Port x mode bits (y= 8 .. 15) 
	GPIOB->CRH	|=	GPIO_CRH_MODE12_0;
	GPIOB->CRH	&=	~GPIO_CRH_MODE12_1;
	// CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	GPIOB->CRH	&=	~GPIO_CRH_CNF12;
}
