
#ifndef ADC_H
#define ADC_H
#include <stdint.h>


// ADC.h
// Header file for ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0

// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void);

// Converts ADC data to linear data based on linera regression
// Minimum value is 0, Maximum value is 2000
uint32_t Convert(uint32_t input);

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void);
#endif
