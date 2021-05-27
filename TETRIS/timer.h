#ifndef TIMER_H_
#define TIMER_H_

#define CPU_CLOCK 16000000
#define TIMER_MAX 65535

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdlib.h>

void StartTimer(double duration);

extern bool IsTimerComplete;

#endif /* TIMER_H_ */