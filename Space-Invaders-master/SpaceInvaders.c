// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 11/20/2018 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018
   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018
 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ADC.h"
#include "Button.h"
#include "Button1.h"
#include "DAC.h"
#include "IntroStory.h"
#include "Menu.h"
#include "Game.h"
#include "PLL.h"
#include "Random.h"
#include "Sound.h"
#include "SysTick.h"
#include "ST7735.h"
#include "Timer0.h"
#include "Timer1.h"

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds

// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
	// Code to initialize PF1, PF2, PF3
	SYSCTL_RCGCGPIO_R &= ~0x20;		// enable port F clock
	SYSCTL_RCGCGPIO_R |= 0x20;
	__nop();											// wait for clock to stabilize
	GPIO_PORTF_DIR_R &= ~0x0E;		// set PF1 - PF3 as output and input
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_AFSEL_R &= ~0x0E;	// disable alternate function for PF1 - PF3
	GPIO_PORTF_DEN_R &= ~0x0E;		// enable GPIO for PF1 - PF3
	GPIO_PORTF_DEN_R |= 0x0E;
}

int main(void){
	// initializations
	PLL_Init(Bus80MHz);       						// Bus clock is 80 MHz 
	PortF_Init();
	Sound_Init();
	ADC_Init();
	EdgeCounter_Init();           // initialize GPIO Port F edge interrupt
	EdgeCounterA_Init();					// initialize GPIO Port A edge interrupt
	SysTick_Init();
	Random_Init(NVIC_ST_CURRENT_R); 			// replace with Random_Init(NVIC_CURRENT_R); for random random seed using systick
	
	int state;														// current state of game
	
	state = 0;														// starts Space Invaders
	Output_Init();												// initialize outputs
	
	DrawMenuScreen();											// draw menu screen
	while(state == 0){
		Menu();															// print menu screen
		state = GetStatus();								// get if game has started running
	}
	
	while(1){
		if(state == 1){													// state = 1, play space invaders
			ST7735_FillScreen(0x0000);            // set screen to black
			SpaceInvader_Init();									// intialize space invaders
			ResetButton0(0);
			ResetButton1(0);
			Timer1_Init(EnemyMovement, 8000004);	// enemy movement at around 10 Hz
			while(state){													// state = 1 infinite loop
				SpaceInvader();											// play space invaders
				state = GetGameStatus();						// get status of game
			}
			
			DrawVictoryScreen();   	// draw victory screen
			while(1){								// infinite loop
			}
		}
  }
}


// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
void Delay100ms(uint32_t count){
	uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
