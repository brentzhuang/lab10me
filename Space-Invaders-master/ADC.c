// put implementations for functions, explain how it works
// put your names here, date
#include "../inc/tm4c123gh6pm.h"

// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/14/2018
// Student names: Adit Jain, Edie Zhou
// Last modification date: 11/26/18

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){
 // --UUU-- Complete this(copy from Lab8)
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R &= ~0x08;			// enable port D clock
	SYSCTL_RCGCGPIO_R |= 0x08;
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize       
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  GPIO_PORTD_DIR_R &= ~0x04;      // make PD2 input
	GPIO_PORTD_DEN_R &= ~0x04;      // disable digital I/O on PD2
	GPIO_PORTD_AFSEL_R |= 0x04;     // enable alternate function on PD2
	GPIO_PORTD_AMSEL_R |= 0x04;     // enable analog function on PD2
	SYSCTL_RCGCADC_R |= 0x01;  			// enable ADC clock
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize       
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  ADC0_PC_R = 0x01;               // configure for 125kHz 
  ADC0_SSPRI_R = 0x0123;          // Seq 3 is highest priority
  ADC0_ACTSS_R &= ~0x08;        	// disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // seq3 is software trigger
  ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+5;  // Ain5 (PD2)
  ADC0_SSCTL3_R = 0x0006;         // no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;           // disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;         // enable sample sequencer
	ADC0_SAC_R = 0x06; 							// SAC reg oversamples by 2^n times hard ware sampling, in this case 64 (hardware solution)
																	// slows down sample rate by a magnitude of 64
																	// now sampling at 1.9kHz
}

// your function to convert ADC sample to distance (0.001cm)
uint32_t Convert(uint32_t input){
	uint32_t result = 0; 								// min value is 0, max value is 2000
	result = (428*input) / 1000 + 136;	// convert ADC result to centimeters based on linreg
  return result;
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
  uint32_t out = 0;
	ADC0_PSSI_R = 0x08;           			// write 0x8 (Bit 3 for SS3) to PSSI reg ( requesting event for SS3)
	while((ADC0_RIS_R & 0x08) == 0x00){	// busy - wait will last around 8us, RIS & 0x8 done
	}															  		// wait for conversion to finish
	out = ADC0_SSFIFO3_R & 0x0FFF;  	 	// read from fifo data = ss fifo &0xFFF, ADC is only 12 bits
	ADC0_ISC_R = 0x08;            			// write 0x08 to ISC reg to finish
	return out;
}



