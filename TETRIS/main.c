/*
 * TETRIS.c
 *
 * Created: 08-04-2021 08:29:22
 * Author : ander
 */ 

#include <avr/io.h>
#include "tetris.h"
#include "display.h"
#include "shapes.h"

int main(void)
{
	RunTetris();
	return 0;
}

