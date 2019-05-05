// Menu.c
// This file runs the selection menu
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Button.h"
#include "Button1.h"
#include "ST7735.h"

int startFlag = 0;													// indicates if game has started


/* DrawMenuScreen
input: none
output: none
Draws menu screen
*/
void DrawMenuScreen(void){
	ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Red Ted Redemption");
  ST7735_SetCursor(1, 4);
  ST7735_OutString("Press A to start");
  ST7735_SetCursor(1, 6);
  ST7735_OutString("Press B for");
	ST7735_SetCursor(1, 7);
	ST7735_OutString("controls");
}

/* DrawControlsScreen
input: none
output: none
Draws controls screen
*/
void DrawControlsScreen(void){
	ST7735_FillScreen(0x0000);            // set screen to black
	ST7735_SetCursor(1, 2);
  ST7735_OutString("CONTROLS: ");
  ST7735_SetCursor(1, 4);
  ST7735_OutString("Use the joystick to");
  ST7735_SetCursor(1, 5);
  ST7735_OutString("move around");
  ST7735_SetCursor(1, 7);
  ST7735_OutString("Press A to fire");
	ST7735_SetCursor(1, 9);
	ST7735_OutString("Press B to pause");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("the game");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("Press B to go back");
}

/* GetStatus
input: none
output: int
Checks if game is running
*/
int GetStatus(void){
	return startFlag;
}

/* Menu
input: none
output: none
Menu handler.
*/
void Menu(void){

	int controlsFlag;									// flag for game controls screen
	controlsFlag = Button1Press();		// checks if controls button was pressed
	if(controlsFlag){
		DrawControlsScreen();
		ResetButton0(0);
	}
	while(controlsFlag){
		controlsFlag = Button1Press(); 	// polls controls button state while in controls
		ResetButton0(0);
		if(!controlsFlag){
			DrawMenuScreen();
			ResetButton0(0);
		}
	}

	if(Button0Press()){
		startFlag = 1;
	}
}

