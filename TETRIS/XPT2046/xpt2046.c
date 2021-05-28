#include "xpt2046reader.h"
#include "xpt2046ADC.h"
#include "xpt2046.h"
#include <avr/interrupt.h>

volatile ADC_read raw;
volatile bool actionReady = false;
#define CPU_CLOCK 16000000
#define TIMER_MAX 65535

void InitXPT2046(){
    InitReader();
}

Coordinate ReadLatestCoordinate(){
    actionReady = false;
    return CoordFromADC(raw);
}

void StartDebounceTimer(){
	TCCR3A=0b00000000; // Normal mode
	TCCR3B=0b00000100; // Prescaler 256
	TCNT3=((TIMER_MAX + 1)-((0.2 * CPU_CLOCK)/256)); // Count
	TIMSK3=0b00000001;	
}

void StopDebouceTimer(){
	TCCR3B = 0b00000000; // Stop timer
	TIFR3 |= 0b00000001; // Set overflow flag
}

void ReEnableTouch(){
	EIFR |= 0b00010000; // Set interrupt 4 flag
	EIMSK |= 0b00010000; // Enable interrupt 4
}

ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	raw = GetRawADCCoordates();
	StartDebounceTimer();
	actionReady = true;
}

ISR(TIMER3_OVF_vect){
	StopDebouceTimer();
	ReEnableTouch();
}