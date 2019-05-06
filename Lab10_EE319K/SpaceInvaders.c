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
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "ADC.h"
#include "Images.h"
#include "Sound.h"
#include "Timer0.h"
#include "Timer1.h"
#include "DAC.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 seconds

struct enemy{
	unsigned long enemyX;
	unsigned long enemyY;
	const unsigned short *image;
	long life;	// 0 means dead 1 means alive
};

typedef struct enemy enemy_t;
enemy_t Enemy[5];

struct player{
	uint16_t playerX;
	uint16_t playerY;
	uint8_t lives;
	uint8_t dead;
	const unsigned short *image;
};

typedef struct player player_t;
player_t Player;

void Init(void){			//initializing enemy's position
	
 for(int i = 0; i<5; i++){
		Enemy[i].enemyX = 20*i;
		Enemy[i].enemyY = 10;
		Enemy[i].image = SmallEnemy20pointA;
		Enemy[i].life = 1;
 }
	
 Player.playerX = 64;
 Player.playerY = 145;
 Player.lives = 3;
 Player.dead = 0;
 Player.image = PlayerShip0;
}

int flag = 0; 

void SysTick_Init(){
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = 2666666;  // maximum reload value
	NVIC_ST_CURRENT_R = 0; 	
	NVIC_ST_CTRL_R |= 0x7;
	EnableInterrupts();
}

void movePlayerLeft(){
	Player.playerX -= 2;
}

void movePlayerRight(){
	Player.playerX += 2;
}

void SysTick_Handler(){
	uint32_t ADCdata = ADC_In();
	if(ADCdata <= 1365)
		movePlayerLeft();
	else if((ADCdata > 1365) && (ADCdata <=2730)){
		
	}
	
	else if(ADCdata > 2730){
		movePlayerRight();
	}
}

void Move(void){

	for(int j = 0; j<5; j++){
		if(Enemy[j].enemyX <= 110){
			Enemy[j].enemyX += 2;
		}

		
		

	}
}
	//else{
	//Enemy[j].life = 0;
	//}
//void MoveBack(void){

//}

	
void Draw(void){	//called inside main loop 30Hz
int i;
	ST7735_FillScreen(0x0000);
	for(i=0;i<5;i++){
		if(Enemy[i].life>0){
		ST7735_DrawBitmap(Enemy[i].enemyX,Enemy[i].enemyY,Enemy[i].image,16,10);
		}
	}
}

void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}


int main(void){
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  Random_Init(1);
	ADC_Init();
	SysTick_Init();
	Sound_Init();
  Output_Init();
  ST7735_FillScreen(0x0000);            // set screen to black
	Init();
	Draw();
	while(1){

		
	Move();
		Draw();
			Delay100ms(2);
		
	}
}
  /*
	
  ST7735_DrawBitmap(52, 159, ns, 18,8); // player ship middle bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);

  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
  ST7735_DrawBitmap(100, 9, SmallEnemy30pointB, 16,10);

  Delay100ms(50);              // delay 5 sec at 80 MHz

  ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  LCD_OutDec(1234);
  while(1){
  }

}



// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays
*/





// You can't use this timer, it is here for starter code only 
// you must use interrupts to perform delays


	


