// Button1.h


#ifndef BUTTON1_H // do not include more than once
#define BUTTON1_H

// EdgeCounter_Init
// Input: none
// Output: none
// Initalizes PF4 to trigger interrupt upon falling edge
void EdgeCounterA_Init(void);

/* Button1Press
input: none
output: state of button1
Return state of button attached to PA4
*/
int Button1Press(void);

/* ResetButton1
input: Desired state of Button1
output: none
Set state of Button1
*/
void ResetButton1(int state);

#endif
