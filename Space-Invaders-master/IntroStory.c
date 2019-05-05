// IntroStory.c
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Button.h"
#include "Button1.h"
#include "ST7735.h"

/* DrawIntroScreen
input: none
output: none
This function prints the introduction to the story.
*/
void DrawIntroScreen(void){
	ST7735_FillScreen(0x0000);            // set screen to black
  ST7735_SetCursor(1, 2);
  ST7735_OutString("You are a plucky");
  ST7735_SetCursor(1, 4);
  ST7735_OutString("politician, hand picked");
  ST7735_SetCursor(1, 6);
  ST7735_OutString("to run against the");
	ST7735_SetCursor(1, 8);
	ST7735_OutString("dreaded powerhouse");
	ST7735_SetCursor(1, 10);
	ST7735_OutString("known to many as");
	ST7735_SetCursor(1, 12);
	ST7735_OutString("Ted Cruz");
	ST7735_SetCursor(1, 14);
	ST7735_OutString("Press A to continue");
}

/* IntroScreen
input: none
output: none
This function handles the introduction to the story
*/
void IntroScreen(void){
	int continueFlag;									// flag for continuing the story
	continueFlag = Button0Press();		// checks if continue button was pressed
	if(continueFlag){
		DrawIntroScreen();
		ResetButton1(0);
	}
	while(continueFlag){
		continueFlag = Button0Press(); 	// polls controls button state while in controls
		ResetButton1(0);
		if(!continueFlag){
			DrawIntroScreen();
			ResetButton1(0);
		}
	}
}

