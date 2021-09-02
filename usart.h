#ifndef _USART
#define _USART
#include "stm32f10x.h"
#include "led.h"
#include "baton.h"


extern char data1[];
extern char data2[];
extern char data3[];

extern volatile char* current_data_ptr;
extern volatile char* start_data_ptr;
void select_output_data(void);
void USART_get_push(void);
void init_USART(void);
void init_USART_with_interrupt(void);
void USART1_IRQHandler(void);

#endif
