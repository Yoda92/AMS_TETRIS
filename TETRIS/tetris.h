/*
 * tetris.h
 *
 * Created: 11-04-2021 15:37:25
 *  Author: ander
 */ 


#ifndef TETRIS_H_
#define TETRIS_H_

#define F_CPU 16000000
#define TICK 750

#include "shapes.h"
#include "display.h"
#include <util/delay.h>

void startGame();

#endif /* TETRIS_H_ */