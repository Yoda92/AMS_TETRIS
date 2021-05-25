/*
 * tetris.h
 *
 * Created: 11-04-2021 15:37:25
 *  Author: ander
 */ 


#ifndef TETRIS_H_
#define TETRIS_H_

#define TICK 250
#define MAX_ROWS 18
#define MAX_COLUMNS 16

#include "shapes.h"
#include "graphics.h"
#include "models/tetris_game.h"
#include "models/direction.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "XPT2046/xpt2046reader.h"
#include "XPT2046/xpt2046ADC.h"

volatile bool inputEnabled;
volatile bool inputReceived;
volatile Direction nextMove;

typedef enum {
	INIT,
	READY_FOR_INPUT,
	UPDATE_DISPLAY,
	TRY_PUSH_DOWN,
	CREATE_NEW_SHAPE,
	GAME_OVER
} TetrisState;

void RunTetris();

#endif /* TETRIS_H_ */