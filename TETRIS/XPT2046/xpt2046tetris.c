#include "xpt2046reader.h"
#include "xpt2046ADC.h"
#include "xpt2046tetris.h"
#include "xpt2046Types.h"
#include <avr/interrupt.h>

volatile struct ADC_read raw;
bool actionReady = false;
#define CPU_CLOCK 16000000
#define TIMER_MAX 65535



void initXPT2046Tetris(){
    initReader();
}

PlayerAction readLatestPlayerAction(){
    actionReady = false;
    struct Coordinate coord = coordFromADC(raw);
	return actionFromCoordinate(coord);
}

void startDebounceTimer(){
	TCCR3A=0b00000000; // Normal mode
	TCCR3B=0b00000100; // Prescaler 256
	TCNT3=((TIMER_MAX + 1)-((0.2 * CPU_CLOCK)/256)); // Count
	TIMSK3=0b00000001;	
}

void stopDebouceTimer(){
	TCCR3B = 0b00000000; // Stop timer
	TIFR3 |= 0b00000001; // Set overflow flag
}


void reEnableTouch(){
	EIFR |= 0b00010000; // Set interrupt 4 flag
	EIMSK |= 0b00010000; // Enable interrupt 4
}


ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	raw = getRawADCCoordates();
	startDebounceTimer();
    actionReady = true;
}

ISR(TIMER3_OVF_vect){
	stopDebouceTimer();
	reEnableTouch();
}