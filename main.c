#include "main.h"


int main(){
	
	//init_USART();
	
	init_led2();
	init_led();
	init_systick();
	init_USART_with_interrupt();
	init_button();
	
	while(1){
		toggle_led2();
	}
}
