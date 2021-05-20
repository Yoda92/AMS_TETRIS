/*
* tetris.c
*
* Created: 11-04-2021 15:37:13
*  Author: ander
*/

#include "tetris.h"

ISR(TIMER5_OVF_vect)
{
	TCCR5B=0b00000000;
	inputEnabled = false;
}

ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	EIFR |= 0b00010000; // Set interrupt 4 flag
	nextMove = RIGHT;
	EIMSK |= 0b00010000; // Enable interrupt 4
}

void Move(TetrisGame* game, Direction direction) {
	ShiftVector(&game->vector, direction);
}

bool IsShapeOutOfBounds(Shape* shape) {
	return (shape->columns > MAX_COLUMNS || shape->rows > MAX_ROWS);
}

bool CanMove(TetrisGame* game, Direction direction) {
	Shape nextShape = CopyShape(&game->shape);
	Vector nextVector = { .x = game->vector.x, .y = game->vector.y};
	ShiftVector(&nextVector, direction);
	ShiftShape(&nextShape, nextVector);
	bool _canMoveDown = !IsShapeOutOfBounds(&nextShape) && IsCombinePossible(&nextShape, &game->pile);
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
	ShiftShape(&_newShape, CreateDefaultVector(game));
	bool _canCreateNewShape = IsCombinePossible(&_newShape, &game->pile);
	DeleteShape(&_newShape);
	return _canCreateNewShape;
}

void SetNewShape(TetrisGame* game, Shape* newShape) {
	Shape shape = CopyShape(&game->shape);
	ShiftShape(&shape, game->vector);
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
	ShiftShape(&shape, game->vector);
	Shape combinedShape = CombineShapes(&game->pile, &shape);
	RenderGame(&combinedShape, game->score);
	DeleteShape(&combinedShape);
	DeleteShape(&shape);
}

void StartTimer() {
	TCCR5A=0b00000000;
	TCCR5B=0b00000100;
	TCNT5=30000;
	TIMSK5=0b00000001;	
}

void InitTouchInterrupt()
{
	DDRE &= 0b11101111;
	EIMSK |= 0b00010000; //Activate interrupt 4.
	EICRA = 0b00000000;
	EICRB = 0b00000010; //rising edge activation of interrupt 4.
}

void WaitForInput(TetrisGame* game) {
	sei();
	StartTimer();
	inputEnabled = true;
	while(inputEnabled) {
		if (nextMove != NOOP && CanMove(game, nextMove)) {
			cli();
			Move(game, nextMove);
			SendToDisplay(game);
			nextMove = NOOP;
			sei();
		}
	}
	cli();
	nextMove = NOOP;
}

TetrisGame InitTetrisGame() {
	nextMove = NOOP;
	Shape shape = CreateRandomShape();
	Vector vector = {
		.x = ((double) (MAX_COLUMNS - shape.columns) / 2),
		.y = 0
	};
	TetrisGame tetrisGame = {
		.pile = CreateEmptyShape(MAX_ROWS, MAX_COLUMNS),
		.shape = shape,
		.vector = vector,
		.score = 0
	};
	
	return tetrisGame;
}

void RemoveCompleteRows(TetrisGame* game) {
	size_t removedRows = 0;
	for(int i = 0; i < game->shape.rows; i++) {
		if(IsRowComplete(&game->pile, game->vector.y + i)) {
			RemoveRow(&game->pile, game->vector.y + i);
			removedRows++;
		}
	}
	PrependRows(&game->pile, removedRows);
}

void RunTetris() {
	TetrisState nextState = INIT;
	TetrisGame game;
	while(nextState != GAME_OVER) {
		switch(nextState) {
			case INIT: {
				GraphicsInit();
				game = InitTetrisGame();
				InitTouchInterrupt();
				nextState = UPDATE_DISPLAY;
				break;
			}
			case UPDATE_DISPLAY: {
				SendToDisplay(&game);
				nextState = READY_FOR_INPUT;
				break;
			}
			case READY_FOR_INPUT: {
				WaitForInput(&game);
				nextState = TRY_PUSH_DOWN;
				break;
			}
			case TRY_PUSH_DOWN: {
				if (CanMove(&game, DOWN)) {
					Move(&game, DOWN);
					nextState = UPDATE_DISPLAY;
					} else {
					nextState = CREATE_NEW_SHAPE;
				}
				RemoveCompleteRows(&game);
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
	SendToDisplay(&game);
	DisplayGameOver();
}