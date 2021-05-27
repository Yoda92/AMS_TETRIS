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
#include "XPT2046/CoordinateMapper.h"

#define F_CPU 16000000


int main(void)
{
	RunTetris();
	return 0;
}
