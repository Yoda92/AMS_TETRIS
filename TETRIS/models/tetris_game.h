/*
 * tetris_game.h
 *
 * Created: 29-04-2021 08:38:44
 *  Author: ander
 */ 


#ifndef TETRIS_GAME_H_
#define TETRIS_GAME_H_

#include "shape.h"
#include "vector.h"

typedef struct TetrisGame {
	Shape shape;
	Vector vector;
	Shape pile;
	size_t score;
}TetrisGame;

#endif /* TETRIS_GAME_H_ */