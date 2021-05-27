#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include "ILI9341.h"

#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0

/****************************************************************************************************/
/****************************************** Private Methods ******************************************/
/****************************************************************************************************/

void WriteCommand(unsigned int command)
{
	DATA_PORT_LOW = command;
	DC_PORT &= ~(1 << DC_BIT);
	CS_PORT &= ~(1 << CS_BIT);
	WR_PORT &= ~(1 << WR_BIT);
	_NOP();
	WR_PORT |= (1 << WR_BIT);
}

void WriteData(unsigned int data)
{
	DATA_PORT_HIGH = data >> 8;
	DATA_PORT_LOW = data;

	DC_PORT |= (1 << DC_BIT);
	CS_PORT &= ~(1 << CS_BIT);
	WR_PORT &= ~(1 << WR_BIT);
	_NOP();
	WR_PORT |= (1 << WR_BIT);
	_NOP();
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

void WritePixel(Color color)
{
	WriteData(((unsigned int)color.red<<11) | ((unsigned int)color.green<<5) | color.blue);
}

void SetColumnAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2A);
	WriteData(Start>>8);            // Write MSB of start
	WriteData(Start);               // Write LSB of start
	WriteData(End>>8);              // Write MSB of end
	WriteData(End);                 // Write LSB of end
}

void SetPageAddress(unsigned int Start, unsigned int End)
{
	WriteCommand(0x2B);
	WriteData(Start>>8);              // Write MSB of start
	WriteData(Start);				  // Write LSB of start
	WriteData(End>>8);              // Write MSB of end
	WriteData(End);                 // Write LSB of end
}

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void IL19341Init()
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

void DrawBitmap(char bitmap[8], unsigned int StartX, unsigned int StartY, size_t scale, Color textColor, Color backgroundColor) {
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