#include "tetris.h"

volatile bool inputEnabled;
volatile bool inputReceived;
volatile Direction nextMove;

typedef enum {
	INIT,
	READY_FOR_INPUT,
	UPDATE_GRAPHICS,
	TRY_PUSH_DOWN,
	CREATE_NEW_SHAPE,
	GAME_OVER
} TetrisState;

/****************************************************************************************************/
/***************************************** Private Methods ******************************************/
/****************************************************************************************************/

Direction GetTouchDirection();

Direction GetTouchDirection() {
	unsigned char x = getTouchCoordinates();
	inputReceived = false;
	return x > 125 ? RIGHT : LEFT;
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
	bool _canMove = !IsShapeOutOfBounds(&nextShape) && IsCombinePossible(&nextShape, &game->pile);
	DeleteShape(&nextShape);
	return _canMove;
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

void UpdateGraphics(TetrisGame* game) {
	Shape shape = CopyShape(&game->shape);
	ShiftShape(&shape, game->vector);
	Shape combinedShape = CombineShapes(&game->pile, &shape);
	RenderGame(&combinedShape, game->score);
	DeleteShape(&combinedShape);
	DeleteShape(&shape);
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
	StartTimer(0.75);
	while(!IsTimerComplete) {
		cli();
		if (nextMove != NOOP && CanMove(game, nextMove)) {
			Move(game, nextMove);
			UpdateGraphics(game);
			nextMove = NOOP;
		}
		sei();
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
	for(int i = 0; i < game->pile.rows; i++) {
		if(IsRowComplete(&game->pile, i)) {
			RemoveRow(&game->pile, i);
			removedRows++;
		}
	}
	PrependRows(&game->pile, removedRows);
	game->score += removedRows;
}

void DeleteGame(TetrisGame* game) {
	DeleteShape(&game->pile);
	DeleteShape(&game->shape);
}

/****************************************************************************************************/
/***************************************** Interrupt Methods ******************************************/
/****************************************************************************************************/

ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	nextMove = GetTouchDirection();
	EIFR |= 0b00010000; // Set interrupt 4 flag
	EIMSK |= 0b00010000; // Enable interrupt 4
}

/****************************************************************************************************/
/***************************************** Public Methods ******************************************/
/****************************************************************************************************/

void RunTetris() {
	TetrisState nextState = INIT;
	TetrisGame game;
	while(nextState != GAME_OVER) {
		switch(nextState) {
			case INIT: {
				InitTetrisGraphics();
				game = InitTetrisGame();
				initReader();
				nextState = UPDATE_GRAPHICS;
				break;
			}
			case UPDATE_GRAPHICS: {
				UpdateGraphics(&game);
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
					nextState = UPDATE_GRAPHICS;
					} else {
					nextState = CREATE_NEW_SHAPE;
				}
				break;				
			}
			case CREATE_NEW_SHAPE: {
				Shape nextShape = CreateRandomShape();
				if (CanCreateNewShape(&game, &nextShape)) {
					SetNewShape(&game, &nextShape);
					RemoveCompleteRows(&game);
					nextState = UPDATE_GRAPHICS;
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
	UpdateGraphics(&game);
	DeleteGame(&game);
	DisplayGameOver();
	_delay_ms(2000);
}