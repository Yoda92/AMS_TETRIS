/*
 * colors.h
 *
 * Created: 14-05-2021 10:25:59
 *  Author: ander
 */ 


#ifndef COLORS_H_
#define COLORS_H_

#include "models/color.h"

typedef struct RGBColors {
	Color black;
	Color red;
	Color green;
	Color blue;
	Color lightblue;
	Color magenta;
	Color yellow;
	Color orange;
	Color white;
	Color teal;
} RGBColors;

const RGBColors rgbColors;

#endif /* COLORS_H_ */