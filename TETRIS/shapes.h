/*
 * shapes.h
 *
 * Created: 08-04-2021 08:57:48
 *  Author: ander
 */ 


#ifndef SHAPES_H_
#define SHAPES_H_

enum block {
	EMPTY,
	RED,
	GREEN,
	BLUE
};

typedef block shape[][];

shape transpose(shape);
shape rotate(shape);

#endif /* SHAPES_H_ */