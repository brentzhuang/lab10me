// Brent Zhuang, Jeong Woo Park
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "ADC.h"
#include "Game.h"
#include "Button.h"

void SysTick_Init(){
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 2666666;  // maximum reload value
	NVIC_ST_CURRENT_R = 0; 	
	NVIC_ST_CTRL_R |= 0x7;
}
uint32_t button;
uint32_t ADCdata;
void SysTick_Handler(){
	
	button = Button_Data();
	
	
	
	
	ADCdata = ADC_In();
	if(ADCdata <= 1365)
		movePlayerLeft();
	
	else if((ADCdata > 1365) && (ADCdata <=2730)){
		
	}
	
	else if(ADCdata > 2730){
		movePlayerRight();
	}
}
