// put implementations for functions, explain how it works
// Brent Zhuang, Jeong Woo Park
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none


void DAC_Init(void){
//Initialize DAC outputs to PB0-3
	volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay++;
	GPIO_PORTB_DIR_R |= 0xF;
	GPIO_PORTB_DEN_R |= 0xF;
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Input=n is converted to n*3.3V/15
// Output: none
void DAC_Out(uint32_t data){
	//When DAC_Out is called, set Port B Data equal to the current value in the sine wave (0-15)
	GPIO_PORTB_DATA_R = data;
}
