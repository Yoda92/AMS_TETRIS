#ifndef TETRIS_H_
#define TETRIS_H_

#define F_CPU 16000000
#define TICK 250
#define MAX_ROWS 18
#define MAX_COLUMNS 16

#include "shapes.h"
#include "graphics.h"
#include "timer.h"
#include "models/tetris_game.h"
#include "models/direction.h"
#include "XPT2046/xpt2046reader.h"
#include "XPT2046/xpt2046ADC.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void RunTetris();

#endif /* TETRIS_H_ */