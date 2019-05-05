// Menu.h
// Header file for Menu.c

#ifndef MENU_H // do not include more than once
#define MENU_H

/* DrawMenuScreen
	 Draws Menu Screen
*/
void DrawMenuScreen(void);

/* DrawControlsScreen
input: none
output: none
Draws controls screen
*/
void DrawControlsScreen(void);

/* GetStatus
input: none
output: int
Checks if game is running
*/
int GetStatus(void);

/* Menu
input: none
output: none
Menu handler.
*/
void Menu(void);

#endif
