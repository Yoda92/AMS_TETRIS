/*
 * tetris.h
 *
 * Created: 11-04-2021 15:37:25
 *  Author: ander
 */ 


#ifndef TETRIS_H_
#define TETRIS_H_

#define F_CPU 16000000
#define TICK 250
#define MAX_ROWS 20
#define MAX_COLUMNS 15

#include "shapes.h"
#include "display.h"
#include <util/delay.h>

typedef enum {
	INIT,
	WAIT,
	UPDATE_DISPLAY,
	MOVE_DOWN,
	CREATE_NEW_SHAPE,
	GAME_OVER
} TetrisState;

typedef struct TetrisGame {
	Shape shape;
	Vector vector;
	Shape pile;
}TetrisGame;

void RunTetris();

#endif /* TETRIS_H_ */