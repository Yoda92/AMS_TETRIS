/*
 * shape.h
 *
 * Created: 29-04-2021 08:40:31
 *  Author: ander
 */ 


#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdlib.h>
#include "block.h"

typedef struct Shape{
	size_t rows;
	size_t columns;
	Block* matrix;
}Shape;

#endif /* SHAPE_H_ */