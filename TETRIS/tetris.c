/*
* tetris.c
*
* Created: 11-04-2021 15:37:13
*  Author: ander
*/

#include "tetris.h"
#include "XPT2046/xpt2046tetris.h"

ISR(TIMER5_OVF_vect)
{
	//StartGameStepTimer triggers this
	TCCR5B = 0b00000000;
	inputEnabled = false;
}

void Move(TetrisGame *game, Direction direction)
{
	ShiftVector(&game->vector, direction);
}

bool IsShapeOutOfBounds(Shape *shape)
{
	return (shape->columns > MAX_COLUMNS || shape->rows > MAX_ROWS);
}

bool CanMove(TetrisGame *game, Direction direction)
{
	Shape nextShape = CopyShape(&game->shape);
	Vector nextVector = {.x = game->vector.x, .y = game->vector.y};
	ShiftVector(&nextVector, direction);
	ShiftShape(&nextShape, nextVector);
	bool _canMoveDown = !IsShapeOutOfBounds(&nextShape) && IsCombinePossible(&nextShape, &game->pile);
	DeleteShape(&nextShape);
	return _canMoveDown;
}

bool canRotate(TetrisGame *game)
{
	Shape nextShape = CopyShape(&game->shape);
	Rotate(&nextShape);
	bool _canRotate = !IsShapeOutOfBounds(&nextShape) && IsCombinePossible(&nextShape, &game->pile);
	DeleteShape(&nextShape);
	return _canRotate;
}

Vector CreateDefaultVector(TetrisGame *game)
{
	Vector vector = {
		.x = ((double)(MAX_COLUMNS - game->shape.columns) / 2),
		.y = 0};
	return vector;
}

bool CanCreateNewShape(TetrisGame *game, Shape *newShape)
{
	Shape _newShape = CopyShape(newShape);
	ShiftShape(&_newShape, CreateDefaultVector(game));
	bool _canCreateNewShape = IsCombinePossible(&_newShape, &game->pile);
	DeleteShape(&_newShape);
	return _canCreateNewShape;
}

void SetNewShape(TetrisGame *game, Shape *newShape)
{
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

void SendToDisplay(TetrisGame *game)
{
	Shape shape = CopyShape(&game->shape);
	ShiftShape(&shape, game->vector);
	Shape combinedShape = CombineShapes(&game->pile, &shape);
	RenderGame(&combinedShape, game->score);
	DeleteShape(&combinedShape);
	DeleteShape(&shape);
}

void StartGameStepTimer()
{
	TCCR5A = 0b00000000;
	TCCR5B = 0b00000100;
	TCNT5 = 30000;
	TIMSK5 = 0b00000001;
}

void WaitForInput(TetrisGame *game)
{
	sei();
	StartGameStepTimer();
	inputEnabled = true;
	while (inputEnabled)
	{
		if (actionReady)
		{
			PlayerAction action = readLatestPlayerAction();
			cli();
			switch (action)
			{
			case ROTATE:
			{
				if (canRotate(game))
				{
					Rotate(&(game->shape));
					SendToDisplay(game);
				}
				break;
			}
			default: 
			{
				Direction nextDirection = getDirectionFromAction(action);
				if (CanMove(game, nextDirection))
				{
					Move(game, nextDirection);
					SendToDisplay(game);
				}
				break;
			}
			}

			sei();
		}
	}
	cli();
}

TetrisGame InitTetrisGame()
{
	nextMove = NOOP;
	Shape shape = CreateRandomShape();
	Vector vector = {
		.x = ((double)(MAX_COLUMNS - shape.columns) / 2),
		.y = 0};
	TetrisGame tetrisGame = {
		.pile = CreateEmptyShape(MAX_ROWS, MAX_COLUMNS),
		.shape = shape,
		.vector = vector,
		.score = 0};

	return tetrisGame;
}

void RemoveCompleteRows(TetrisGame *game)
{
	size_t removedRows = 0;
	for (int i = 0; i < game->pile.rows; i++)
	{
		if (IsRowComplete(&game->pile, i))
		{
			RemoveRow(&game->pile, i);
			removedRows++;
		}
	}
	PrependRows(&game->pile, removedRows);
	game->score += removedRows;
}

void RunTetris()
{
	TetrisState nextState = INIT;
	TetrisGame game;
	while (nextState != GAME_OVER)
	{
		switch (nextState)
		{
		case INIT:
		{
			GraphicsInit();
			game = InitTetrisGame();
			initXPT2046Tetris();
			nextState = UPDATE_DISPLAY;
			break;
		}
		case UPDATE_DISPLAY:
		{
			SendToDisplay(&game);
			nextState = READY_FOR_INPUT;
			break;
		}
		case READY_FOR_INPUT:
		{
			WaitForInput(&game);
			nextState = TRY_PUSH_DOWN;
			break;
		}
		case TRY_PUSH_DOWN:
		{
			if (CanMove(&game, DOWN))
			{
				Move(&game, DOWN);
				nextState = UPDATE_DISPLAY;
			}
			else
			{
				nextState = CREATE_NEW_SHAPE;
			}
			break;
		}
		case CREATE_NEW_SHAPE:
		{
			Shape nextShape = CreateRandomShape();
			if (CanCreateNewShape(&game, &nextShape))
			{
				SetNewShape(&game, &nextShape);
				RemoveCompleteRows(&game);
				nextState = UPDATE_DISPLAY;
			}
			else
			{
				DeleteShape(&nextShape);
				nextState = GAME_OVER;
			}
			break;
		}
		default:
		{
			nextState = INIT;
			break;
		}
		}
	}
	SendToDisplay(&game);
	DisplayGameOver();
}