/*
 * TETRIS.c
 *
 * Created: 08-04-2021 08:29:22
 * Author : ander
 */

#include "tetris.h"
#include "util/delay.h"
#include "XPT2046/xpt2046reader.h"
#include "XPT2046/xpt2046ADC.h"
#include "XPT2046/xpt2046Types.h"

#define F_CPU 16000000

volatile struct ADC_read raw;
volatile unsigned char x = 0;
/*
ISR(INT4_vect)
{
	EIMSK &= 0b11101111; // Disable interrupt 4
	raw = getRawADCCoordates();
	x = simplexRead();
	EIFR |= 0b00010000;	 // Set interrupt 4 flag
	EIMSK |= 0b00010000; // Enable interrupt 4
}
*/
int main(void)
{
	//sei();
	raw.x = 0;
	raw.y = 0;
		GraphicsInit();
	initReader();

	while (1)
	{
		RenderScore((size_t)simplexRead());
		//struct Coordinate coord = coordFromADC(raw);
		//FillRectangle(coord.x, coord.y, 5, 5, rgbColors.blue);
		_delay_ms(500);
		//struct Coordinate coord = coordFromADC(raw);
	}
	RunTetris();
	return 0;
}
