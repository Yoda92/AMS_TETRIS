#include "xpt2046reader.h"
#include "xpt2046ADC.h"
#include "xpt2046tetris.h"
#include "xpt2046Types.h"
#include <avr/interrupt.h>

volatile struct ADC_read raw;
bool actionReady = false;

ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	raw = getRawADCCoordates();
	EIFR |= 0b00010000; // Set interrupt 4 flag
	EIMSK |= 0b00010000; // Enable interrupt 4
    actionReady = true;
}

void initXPT2046Tetris(){
    initReader();
}

PlayerAction readLatestPlayerAction(){
    actionReady = false;
    struct Coordinate coord = coordFromADC(raw);
	return actionFromCoordinate(coord);
}