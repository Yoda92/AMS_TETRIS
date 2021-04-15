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
	// Initialize the display
	DisplayInit();
	//// All pixels white (background)
	//FillRectangle(0,0,320,240,31,63,31);
	//// Draw red parts of danish flag
	//FillRectangle(0,140,100,100,31,0,0);
	//FillRectangle(0,0,100,100,31,0,0);
	//FillRectangle(140,0,320-140,100,31,0,0);
	//FillRectangle(140,140,320-140,100,31,0,0);
	
	Shape foo = createRandomShape();
	
	rotate(&foo);
	
	renderDisplay(foo);

	startGame();
    while (1) 
    {
		DisplayOn();
		_delay_ms(1000);
    }
	return 0;
}

