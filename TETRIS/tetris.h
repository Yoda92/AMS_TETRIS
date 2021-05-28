#ifndef TETRIS_H_
#define TETRIS_H_

#define MAX_ROWS 18
#define MAX_COLUMNS 16
#define MAX_SCORE 255

#include "shapes.h"
#include "graphics.h"
#include "timer.h"
#include "models/tetris_game.h"
#include "models/direction.h"
#include "XPT2046/xpt2046.h"
#include "SD/SD_Driver.h"
#include <avr/interrupt.h>

void RunTetris();

#endif /* TETRIS_H_ */