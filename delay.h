#ifndef _DELAY
#define _DELAY

#define SYSCLOCK 					72000000U

#include "baton.h"
#include "stm32f10x.h"
#include "led.h"
extern volatile uint32_t ticks_delay;

inline uint32_t get_ms(void);
void delay_ms(uint32_t ms);
void SysTick_Handler(void);
void init_systick(void);

#endif
