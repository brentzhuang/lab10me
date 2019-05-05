// Button.c
// Uses edge triggered interrupt to detect button press

// EdgeInterrupt.c
// Runs on LM4F120 or TM4C123
// Request an interrupt on the falling edge of PF4 (when the user
// button is pressed) and increment a counter in the interrupt.  Note
// that button bouncing is not addressed.
// Daniel Valvano
// May 3, 2015

// user button connected to PF4
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Game.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int pressed0 = 0;

void EdgeCounter_Init(void){    
	DisableInterrupts();
  SYSCTL_RCGCGPIO_R |= 0x00000020; 	// activate clock for port F
	__nop();
	__nop();
  GPIO_PORTF_DIR_R &= ~0x10;    		// make PF4 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x10;  		// disable alt funct on PF4
  GPIO_PORTF_DEN_R |= 0x10;     		// enable digital I/O on PF4 
  GPIO_PORTF_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
  GPIO_PORTF_AMSEL_R = 0;       		// disable analog functionality on PF4
  GPIO_PORTF_PUR_R |= 0x10;     		// enable weak pull-up on PF4
  GPIO_PORTF_IS_R &= ~0x10;     		// PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x10;    		// PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x10;    		// PF4 falling edge event
  GPIO_PORTF_ICR_R = 0x10;      		// clear flag for PF4
  GPIO_PORTF_IM_R |= 0x10;      		// arm interrupt on PF4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // priority 5
  NVIC_EN0_R = 0x40000000;      		// enable interrupt 30 in NVIC
  EnableInterrupts();           		// Clears the I bit
}

void GPIOPortF_Handler(void){
  GPIO_PORTF_ICR_R = 0x10;     			// acknowledge flag for PF4
	PlayerFire();											// fires at falling edge of button press
	pressed0 ^= 1;
}
/* Button0Press
input: none
output: state of button0
Return state of button attached to PF4
*/
int Button0Press(void){
	return pressed0;
}

/* ResetButton0
input: Desired state of Button0
output: none
Set state of Button0
*/
void ResetButton0(int state){
	pressed0 = state;
}
