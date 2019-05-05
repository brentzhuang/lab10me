// Button.h
// Header File for Button.c

#ifndef BUTTON_H // do not include more than once
#define BUTTON_H

// EdgeCounter_Init
// Input: none
// Output: none
// Initalizes PF4 to trigger interrupt upon falling edge
void EdgeCounter_Init(void);

/* Button0Press
input: none
output: state of button0
Return state of button attached to PF4
*/
int Button0Press(void);

/* ResetButton0
input: Desired state of Button0
output: none
Set state of Button0
*/
void ResetButton0(int state);

#endif
