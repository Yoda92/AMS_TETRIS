/*
* tetris.c
*
* Created: 11-04-2021 15:37:13
*  Author: ander
*/

#include "tetris.h"

#define MAX_ROWS 20
#define MAX_COLUMNS 10

typedef struct GameState {
	Shape shape;
	Vector vector;
	Shape pile;
}GameState;

void clean() {
	// clean up
}

void moveDown(GameState* state) {
	state->vector.y++;
}

bool isShapeOutOfBounds(Shape* shape) {
	return (shape->columns > MAX_COLUMNS || shape->rows > MAX_ROWS);
}

void nextGameState(GameState* state) {
	Shape nextShape = copyShape(&state->shape);
	Vector downMovement = {
		.x = 0,
		.y = state->vector.y + 1
	};
	shift(&nextShape, downMovement);
	if (isCombinePossible(&nextShape, &state->pile) && !isShapeOutOfBounds(&nextShape)) {
		moveDown(state);
	} else {
		state->pile = combineShapes(&state->pile, &state->shape);
		deleteShape(&state->pile);
		deleteShape(&state->shape);
		state->shape = createRandomShape();
		Vector vector = {
			.x = ((double) (MAX_COLUMNS - state->shape.columns) / 2),
			.y = 0
		};	
		state->vector = vector;
	}
	clean();
}

void render() {
	// update screen
}

void wait() {
	// _delay_ms(TICK);
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
		render(&state);
		wait();
		nextGameState(&state);
	}
}