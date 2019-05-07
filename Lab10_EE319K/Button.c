#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
void Button_Init(){
	volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R&0x10)==0){}
	GPIO_PORTE_DIR_R &= 0x03;
	GPIO_PORTE_DEN_R |= 0x03;
}
uint32_t data;

uint32_t Button_Data(){
	data = GPIO_PORTE_DATA_R;
	return data;
}
