#ifndef ILI9341_H_
#define ILI9341_H_

#define F_CPU 16000000
#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

#include <stdio.h>
#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include "../models/color.h"

void IL19341Init();
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, Color color);
void DrawBitmap(char bitmap[], unsigned int StartX, unsigned int StartY, size_t factor, Color, Color);

#endif /* ILI9341_H_ */