#ifndef _BUTTON
#define _BUTTON
#include "stm32f10x.h"

#define SHORT_DURATION 		100
#define LONG_DURATION_LOW	1000
#define LONG_DURATION_HIGH	3000

extern volatile uint8_t button_state;
void check_button(void);
inline uint8_t get_button_state(void);
void init_button(void);

#endif
