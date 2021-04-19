/*
* tetris.c
*
* Created: 11-04-2021 15:37:13
*  Author: ander
*/

#include "tetris.h"

void MoveDown(TetrisGame* game) {
	game->vector.y = game->vector.y + 1;
}

bool IsShapeOutOfBounds(Shape* shape) {
	return (shape->columns > MAX_COLUMNS || shape->rows > MAX_ROWS);
}

bool CanMoveDown(TetrisGame* game) {
	Shape nextShape = CopyShape(&game->shape);
	Vector downMovement = {
		.x = game->vector.x,
		.y = game->vector.y + 1
	};	
	Shift(&nextShape, downMovement);
	bool _canMoveDown = IsCombinePossible(&nextShape, &game->pile) && !IsShapeOutOfBounds(&nextShape);
	DeleteShape(&nextShape);
	return _canMoveDown;
}

Vector CreateDefaultVector(TetrisGame* game) {
	Vector vector = {
		.x = ((double) (MAX_COLUMNS - game->shape.columns) / 2),
		.y = 0
	};
	return vector;
}

bool CanCreateNewShape(TetrisGame* game, Shape* newShape) {
	Shape _newShape = CopyShape(newShape);
	Shift(&_newShape, CreateDefaultVector(game));
	bool _canCreateNewShape = IsCombinePossible(&_newShape, &game->pile);
	DeleteShape(&_newShape);
	return _canCreateNewShape;
}

void SetNewShape(TetrisGame* game, Shape* newShape) {
	Shape shape = CopyShape(&game->shape);
	Shift(&shape, game->vector);
	Shape combinedShape = CombineShapes(&game->pile, &shape);
	DeleteShape(&shape);
	DeleteShape(&game->pile);
	DeleteShape(&game->shape);
	game->pile = combinedShape;
	game->shape = *newShape;
	game->vector = CreateDefaultVector(game);	
}

void SendToDisplay(TetrisGame* game) {
	Shape shape = CopyShape(&game->shape);
	Shift(&shape, game->vector);
	Shape combinedShape = CombineShapes(&game->pile, &shape);
	Rotate(&combinedShape);
	renderDisplay(combinedShape);
	DeleteShape(&combinedShape);
	DeleteShape(&shape);
}

void Wait() {
	// TODO: Dont use constant wait time, but start timer instead.
	_delay_ms(TICK);
}

TetrisGame InitTetrisGame() {
	Shape shape = CreateRandomShape();
	Vector vector = {
		.x = ((double) (MAX_COLUMNS - shape.columns) / 2),
		.y = 0
	};
	TetrisGame tetrisGame = {
		.pile = CreateEmptyShape(MAX_ROWS, MAX_COLUMNS),
		.shape = shape,
		.vector = vector
	};
	
	return tetrisGame;
}

void RunTetris() {
	TetrisState nextState = INIT;
	TetrisGame game;
	while(nextState != GAME_OVER) {
		switch(nextState) {
			case INIT: {
				DisplayInit();
				game = InitTetrisGame();
				nextState = UPDATE_DISPLAY;
				break;
			}
			case UPDATE_DISPLAY: {
				SendToDisplay(&game);
				nextState = WAIT;
				break;
			}
			case WAIT: {
				Wait();
				nextState = MOVE_DOWN;
				break;
			}
			case MOVE_DOWN: {
				if (CanMoveDown(&game)) {
					MoveDown(&game);
					nextState = UPDATE_DISPLAY;
					} else {
					nextState = CREATE_NEW_SHAPE;
				}
				break;				
			}
			case CREATE_NEW_SHAPE: {
				Shape nextShape = CreateRandomShape();
				if (CanCreateNewShape(&game, &nextShape)) {
					SetNewShape(&game, &nextShape);
					nextState = UPDATE_DISPLAY;
					} else {
					DeleteShape(&nextShape);
					nextState = GAME_OVER;
				}
				break;				
			}
			default: {
				nextState = INIT;
				break;
			}
		}
	}
}