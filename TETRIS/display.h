/*
 * display.h
 *
 * Created: 15/04/2021 09.03.40
 *  Author: bbend
 */ 
#include "shapes.h"

void DisplayInit();
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormat(unsigned char parameter);
void WritePixel(unsigned char Red, unsigned char Blue, unsigned char Green);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width,
unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue);
void renderDisplay(Shape state);


