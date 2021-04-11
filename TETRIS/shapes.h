/*
 * shapes.h
 *
 * Created: 08-04-2021 08:57:48
 *  Author: ander
 */ 


#ifndef SHAPES_H_
#define SHAPES_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
	EMPTY,
	RED,
	GREEN,
	BLUE
} Block;

typedef struct Shape{
	size_t rows;
	size_t columns;
	Block* matrix;
}Shape;

typedef struct Vector{
	size_t x;
	size_t y;
}Vector;

const Shape shapes[1];

Block* createEmptyMatrix(size_t, size_t);
Shape createEmptyShape(size_t, size_t);
Shape createRandomShape();
void deleteShape(Shape*);
void flipRows(Shape*);
void transpose(Shape*);
void rotate(Shape*);
void prependRows(Shape*, size_t);
void shift(Shape*, Vector);
Shape copyShape(Shape*);
bool isCombinePossible(Shape*, Shape*);
Shape combineShapes(Shape*, Shape*);

#endif /* SHAPES_H_ */