// SysTick.c

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Game.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Init(void){
	DisableInterrupts();
	NVIC_ST_CTRL_R = 0;					// disable SysTick for init
	NVIC_ST_RELOAD_R = 1333334;	// 60 Hz on 80MHz clock
	NVIC_ST_CURRENT_R = 0;			// clear CURRENT
	NVIC_ST_CTRL_R = 0x07;
	EnableInterrupts();
}

void SysTick_Handler(void){ 
}
