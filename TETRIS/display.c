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
#include "shapes.h"
#include "tetris.h"

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

// Game height and width based on 20 rows and 10 columns
#define HEIGHT 320/20 // 16
#define WIDTH 240/15 // 16

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
	
	MemoryAccessControl(0b00001000);
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
void WritePixel(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	WriteData(((unsigned int)Red<<11) | ((unsigned int)Green<<5) | Blue);
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
	//WriteData(End>>8);              // Write MSB of end
	//WriteData(End);                 // Write LSB of end
}

// Fills rectangle with specified color
// (StartX,StartY) = Upper left corner. X horizontal (0-319) , Y vertical (0-239).
// Height (1-240) is vertical. Width (1-320) is horizontal.
// R-G-B = 5-6-5 bits.
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue)
{
	SetPageAddress(StartX, StartX + Width);           //Start X value and end value
	SetColumnAddress(StartY, StartY + Height);        //Start Y value and end value
	MemoryWrite();
	for (unsigned long i = 0; i < ((unsigned long)(Width+1) * (Height+1)); i++)
	{
		WritePixel(Red, Green, Blue);
	}
}

void renderDisplay(Shape shape) 
{
	for(size_t y=0; y < shape.rows; y++) {
		for(size_t x=0; x < shape.columns; x++) {
			switch(shape.matrix[(y * shape.columns) + x])
			{
				case EMPTY:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 0, 0, 0);
					break;
				case RED:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 255, 0, 0);
					break;
				case GREEN:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 0, 255, 0);
					break;
				case BLUE:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 0, 0, 255);
					break;
				case MAGENTA:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 255, 0, 255);
					break;
				case LIGHTBLUE:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 100, 100, 255);
					break;
				case YELLOW:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 0, 255, 255);
					break;
				case ORANGE:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 255, 100, 100);
					break;
				default:
					FillRectangle(x*WIDTH, y*HEIGHT, WIDTH, HEIGHT, 255, 255, 255);
			}
		}
	}
}

