#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
volatile int delay;
void Button_Init(){
	SYSCTL_RCGCGPIO_R |= 0x10;
	delay++;
	GPIO_PORTE_DIR_R &= 0x0;
	GPIO_PORTE_DEN_R |= 0x3;
}
uint32_t data;

uint32_t Button_Data(){
	data = GPIO_PORTE_DATA_R;
	return data;
}
