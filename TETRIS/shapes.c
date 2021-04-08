/*
* shapes.c
*
* Created: 08-04-2021 08:30:13
*  Author: ander
*/

shape shapes[] = {
	{
		{
			EMPTY, EMPTY, RED, EMPTY, EMPTY
		},
		{
			RED, RED, RED, RED, RED
		}
	},
	{
		{
			GREEN, EMPTY, EMPTY, EMPTY, EMPTY
		},
		{
			GREEN, GREEN, GREEN, GREEN, GREEN
		}
	}
}

shape transpose(shape input) {
	shape transposedShape = shape[][];
	for(size_t y=0; y < sizeof input[0]; y++) {
		for(size_t x=0; x < sizeof input[0][0]; x++) {
			transposedShape
		}
	}
}

shape rotate(shape input) {
	return input;
};
