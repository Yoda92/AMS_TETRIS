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

	startGame();
    while (1) 
    {
		DisplayOn();
		_delay_ms(1000);
    }
	return 0;
}

