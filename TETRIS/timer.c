#include "timer.h"

bool IsTimerComplete = false;

ISR(TIMER5_OVF_vect)
{
	TCCR5B = 0b00000000; // Stop timer
	TIFR5 |= 0b00000001; // Set overflow flag
	IsTimerComplete = true;
}

/****************************************************************************************************/
/***************************************** Public Methods ******************************************/
/****************************************************************************************************/

void StartTimer(double duration) {
	IsTimerComplete = false;
	TCCR5A=0b00000000; // Normal mode
	TCCR5B=0b00000100; // Prescaler 256
	TCNT5=((TIMER_MAX + 1)-((duration * F_CPU)/256)); // Count
	TIMSK5=0b00000001;	
}

