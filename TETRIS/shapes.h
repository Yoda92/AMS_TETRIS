/*
 * shapes.h
 *
 * Created: 08-04-2021 08:57:48
 *  Author: ander
 */ 


#ifndef SHAPES_H_
#define SHAPES_H_

#define DEFAULT_COUNT 7

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "blocks.h"
#include "models/shape.h"
#include "models/vector.h"
#include "models/direction.h"

const Shape defaultShapes[DEFAULT_COUNT];

void ShiftVector(Vector*, Direction);
Block* CreateEmptyMatrix(size_t, size_t);
Shape CreateEmptyShape(size_t, size_t);
Shape CreateRandomShape();
void DeleteShape(Shape*);
void FlipRows(Shape*);
void Transpose(Shape*);
void Rotate(Shape*);
void PrependRows(Shape*, size_t);
void AppendRows(Shape* shape, size_t amount);
void ShiftShape(Shape*, Vector);
Shape CopyShape(Shape*);
bool IsCombinePossible(Shape*, Shape*);
Shape CombineShapes(Shape*, Shape*);
void NormalizeShapes(Shape*, Shape*);
bool IsRowComplete(Shape* shape, size_t row);
void RemoveRow(Shape* shape, size_t row);

#endif /* SHAPES_H_ */