/*
* tetris.c
*
* Created: 11-04-2021 15:37:13
*  Author: ander
*/

#include "tetris.h"

#define MAX_ROWS 20
#define MAX_COLUMNS 15

typedef struct GameState {
	Shape shape;
	Vector vector;
	Shape pile;
}GameState;

void moveDown(GameState* state) {
	state->vector.y = state->vector.y + 1;
}

bool isShapeOutOfBounds(Shape* shape) {
	return (shape->columns > MAX_COLUMNS || shape->rows > MAX_ROWS);
}

void nextGameState(GameState* state) {
	Shape nextShape = copyShape(&state->shape);
	Vector downMovement = {
		.x = state->vector.x,
		.y = state->vector.y + 1
	};
	shift(&nextShape, downMovement);
	if (isCombinePossible(&nextShape, &state->pile) && !isShapeOutOfBounds(&nextShape)) {
		moveDown(state);
	} else {
		Shape currentShape = copyShape(&state->shape);
		shift(&currentShape, state->vector);
		Shape combinedShape = combineShapes(&state->pile, &currentShape);
		deleteShape(&currentShape);
		deleteShape(&state->pile);
		deleteShape(&state->shape);
		state->pile = combinedShape;
		state->shape = createRandomShape();
		Vector vector = {
			.x = ((double) (MAX_COLUMNS - state->shape.columns) / 2),
			.y = 0
		};	
		state->vector = vector;
	}
	deleteShape(&nextShape);
}

void sendToDisplay(GameState* state) {
	Shape currentShape = copyShape(&state->shape);
	shift(&currentShape, state->vector);
	Shape combinedShape = combineShapes(&state->pile, &currentShape);
	rotate(&combinedShape);
	renderDisplay(combinedShape);
	deleteShape(&combinedShape);
	deleteShape(&currentShape);
}

void wait() {
	// TODO: Dont use constant wait time, but start timer instead.
	_delay_ms(TICK);
}

GameState initGameState() {
	Shape shape = createRandomShape();
	Vector vector = {
		.x = ((double) (MAX_COLUMNS - shape.columns) / 2),
		.y = 0
	};
	GameState state = {
		.pile = createEmptyShape(MAX_ROWS, MAX_COLUMNS),
		.shape = shape,
		.vector = vector
	};
	
	return state;
}

void startGame() {
	GameState state = initGameState();
	while(1) {
		sendToDisplay(&state);
		wait();
		nextGameState(&state);
	}
}