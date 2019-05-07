// Brent Zhuang, Jeong Woo Park
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "ADC.h"
#include "Game.h"
#include "Button.h"

void SysTick_Init(){
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 800000;  // maximum reload value
	NVIC_ST_CURRENT_R = 0; 	
	NVIC_ST_CTRL_R |= 0x7;
}

uint32_t ADCdata;
uint32_t button;
uint16_t LaserY;
uint16_t LaserX;

uint16_t EnemyX;
uint16_t EnemyY;
uint8_t LaserW = 2;
uint8_t LaserH = 10;
uint8_t EnemyW = 16;
uint8_t EnemyH = 10;

void SysTick_Handler(){
	
	button = Button_Data();
	if(button == 1 && getLaser() == 0){
		laserInit();
	}
	
	while(button == 2){
		button = Button_Data();
	}
	
	if(getLaser() == 1){
		moveLaser();
	}
	
	
	ADCdata = ADC_In();
	if(ADCdata <= 1365 && getPlayerX() > 1)
		movePlayerLeft();
	
	else if((ADCdata > 1365) && (ADCdata <=2730)){
		noMove();
	}
	
	
	else if(ADCdata > 2730 && getPlayerX() < 111){
		movePlayerRight();
	}
}
