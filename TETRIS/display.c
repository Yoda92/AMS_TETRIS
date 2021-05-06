/*
 * display.c
 *
 * Created: 15/04/2021 09.03.27
 *  Author: bbend
 */ 
#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "display.h"

// Data port definitions:
#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

// Control port definitions:
#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7  //"DC" signal is at the shield called RS
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0

// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// ILI 9341 data sheet, page 238
void WriteCommand(unsigned int command)
{
	DATA_PORT_LOW = command;
	// Set pins low
	DC_PORT &= ~(1 << DC_BIT);
	CS_PORT &= ~(1 << CS_BIT);
	WR_PORT &= ~(1 << WR_BIT);
	// min 15 ns
	_NOP();
	WR_PORT |= (1 << WR_BIT);
}

// ILI 9341 data sheet, page 238
void WriteData(unsigned int data)
{
	// set pins on bus
	DATA_PORT_HIGH = data >> 8;
	DATA_PORT_LOW = data;

	DC_PORT |= (1 << DC_BIT);
	CS_PORT &= ~(1 << CS_BIT);
	WR_PORT &= ~(1 << WR_BIT);
	// min 15 ns
	_NOP();
	WR_PORT |= (1 << WR_BIT);
	_NOP();
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
	// Control pins outputs
	DDRG |= 0b00000111;
	DDRD |= 0b10000000;
	// Data pins outputs
	DDRA = 0xFF;
	DDRC = 0xFF;
	// Control pins high
	WR_PORT |= 0b00000111;
	DC_PORT |= 0b10000000;
	
	// RST low
	RST_PORT &= ~(1 << RST_BIT);
	_delay_ms(500);
	
	// RST high
	RST_PORT |= (1 << RST_BIT);
	_delay_ms(500);
	
	SleepOut();
	DisplayOn();
	
	MemoryAccessControl(0b01001000);
	InterfacePixelFormat(0b00000101);
}

void DisplayOff()
{
	WriteCommand(0x28);
}

void DisplayOn()
{
	WriteCommand(0x29);
}

void SleepOut()
{
	WriteCommand(0x11);
}

void MemoryAccessControl(unsigned char parameter)
{
	WriteCommand(0x36);
	WriteData(parameter);
}

void InterfacePixelFormat(unsigned char parameter)
{
	WriteCommand(0x3A);
	WriteData(parameter);
}

void MemoryWrite()
{
	WriteCommand(0x2C);
}

// Red 0-31, Green 0-63, Blue 0-31
void WritePixel(Color color)
{
	WriteData(((unsigned int)color.red<<11) | ((unsigned int)color.green<<5) | color.blue);
}

// Set Column Address (0-239), Start > End
void SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2A);
	WriteData(Start>>8);            // Write MSB of start
	WriteData(Start);               // Write LSB of start
	WriteData(End>>8);              // Write MSB of end
	WriteData(End);                 // Write LSB of end
}

// Set Page Address (0-319), Start > End
void SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2B);
	WriteData(Start>>8);              // Write MSB of start
	WriteData(Start);				  // Write LSB of start
	WriteData(End>>8);              // Write MSB of end
	WriteData(End);                 // Write LSB of end
}

// Fills rectangle with specified color
// (StartX,StartY) = Upper left corner. X horizontal (0-319) , Y vertical (0-239).
// Height (1-240) is vertical. Width (1-320) is horizontal.
// R-G-B = 5-6-5 bits.
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, Color color)
{
	SetPageAddress(StartY, StartY + Height);           //Start X value and end value
	SetColumnAddress(StartX, StartX + Width);        //Start Y value and end value
	MemoryWrite();
	for (unsigned long i = 0; i < ((unsigned long)(Width+1) * (Height+1)); i++)
	{
		WritePixel(color);
	}
}

void DrawText(char bitmap[8], unsigned int StartX, unsigned int StartY, size_t scale, Color textColor, Color backgroundColor) {
	size_t scaledWidth = (8 * scale);
	size_t scaledHeigth = (8 * scale);
	SetPageAddress(StartY, StartY + scaledHeigth - 1);
	SetColumnAddress(StartX, StartX + scaledWidth - 1);
	MemoryWrite();
	for(size_t i = 0; i < scaledHeigth; i++) {
		for(size_t y = 0; y < scaledWidth; y++) {
			if (0b10000000 >> ((y / scale) % 8) & bitmap[i / scale]) {
				WritePixel(textColor);
				} else {
				WritePixel(backgroundColor);
			}
		}
	}	
}

//void DrawTest(unsigned char bitmap[], size_t width, size_t height) {
	//SetPageAddress(0, height - 1);
	//SetColumnAddress(0, width - 1);
	//MemoryWrite();
	//for(size_t i = 0; i < height; i++) {
		//for(size_t y = 0; y < width; y++) {
			//if (0b10000000 >> (y % 8) & bitmap[i]) {
				//WritePixel(0, 0, 0);
				//} else {
				//WritePixel(255, 255, 255);
			//}			
		//}
	//}
//}
//
//void DrawBitmap(unsigned char bitmap[]) {
	//size_t width = bitmap[0];
	//size_t height = bitmap[1];
	//size_t rowByteOffset = 8 - (width % 8);
	//size_t currentIndex;
	//size_t skip;
	//SetPageAddress(0, height - 1);
	//SetColumnAddress(0, width - 1);
	//MemoryWrite();
	//for(size_t i = 0; i < height; i++) {
		//skip = rowByteOffset * i;
		//for(size_t y = 0; y < width; y++) {
			//currentIndex = i * width + y + skip;
			//if ((0b10000000 >> ((currentIndex) % 8)) & bitmap[3 + (currentIndex >> 3)]) {
				//WritePixel(0, 0, 0);
				//} else {
				//WritePixel(255, 255, 255);
			//}		
		//}
	//}
//}

