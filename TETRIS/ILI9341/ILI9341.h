/*
 * ILI9341.h
 *
 * Created: 14-05-2021 09:05:41
 *  Author: ander
 */ 


#ifndef ILI9341_H_
#define ILI9341_H_

#include <stdio.h>
#include "../models/color.h"

// Game height and width based on 20 rows and 10 columns
#define SCREEN_HEIGHT 320
#define SCREEN_WIDTH 240

void DisplayInit();
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormat(unsigned char parameter);
void WritePixel(Color color);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width,
unsigned int Height, Color color);
void DrawBitmap(unsigned char[8]);
void DrawTest(unsigned char[], size_t width, size_t height);
void DrawText(char bitmap[], unsigned int StartX, unsigned int StartY, size_t factor, Color, Color);

#endif /* ILI9341_H_ */