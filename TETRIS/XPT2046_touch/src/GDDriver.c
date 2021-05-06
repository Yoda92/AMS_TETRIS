/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  Henning Hargaard, February 14, 2019
************************************************************/  
#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "GDDriver.h"

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

void setCommandMode();
void setDataMode();
void writePulse();
void setCS(unsigned char isHigh);
void setLowerDataBits(unsigned char dataByte);
void setUpperDataBits(unsigned char dataByte);
void setCS(unsigned char isHigh);
void setReset(unsigned char isHigh);



void writePulse()
{
  WR_PORT &= ~(1<<WR_BIT);
  _NOP();
  WR_PORT |= (1<<WR_BIT);
  _NOP();
}

void setLowerDataBits(unsigned char dataByte){
  PORTC = dataByte;
}

void setUpperDataBits(unsigned char dataByte){
  PORTA = dataByte;
}

void WriteCommand(unsigned char command)
{
  setCommandMode();
  setCS(0);
  setLowerDataBits(command);
  writePulse();
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

void setDataMode()
{
  // Set DCX 1 for data mode
  DC_PORT |= (1<<DC_BIT);
}

void setCommandMode()
{
  // Set DCX 0 for command mode
    DC_PORT &= ~(1<<DC_BIT);
}



// ILI 9341 data sheet, page 238
void WriteData(unsigned int data)
{
  setLowerDataBits(data);
  setUpperDataBits(data>>8);
  setCS(0);
  setDataMode();
  writePulse();
}

void setReset(unsigned char isHigh)
{
  if (isHigh)
  {
    RST_PORT |= (1<<RST_BIT);
  }
   else
   {
     RST_PORT &= ~(1<<RST_BIT);
   }
}



void setCS(unsigned char isHigh)
{
  if (isHigh)
  {
    CS_PORT |= (1<<CS_BIT);
  }
   else
   {
     CS_PORT &= ~(1<<CS_BIT);
   }
}


// Initializes (resets) the display
void DisplayInit()
{
  DDRG |= 0b00000111;
  DDRD |= 0b10000000;
  DDRA = 0xFF; // Data
  DDRC = 0xFF; // Data

  PORTG |= 0b00000111;
  PORTD |= 0b10000000;

  setReset(0);
  _delay_ms(500);
  setReset(1);
  _delay_ms(130);
  SleepOut();
  DisplayOn();
  MemoryAccessControl(0b00001000);
  InterfacePixelFormat(0b01010101);
}


void MemoryAccessControl(unsigned char parameter)
{
  WriteCommand(0x36);
  // 0b00001000 for BGR mode
  WriteData(parameter); 
}

void InterfacePixelFormat(unsigned char parameter)
{
  WriteCommand(0x3A);
  // 0b01010101 for 16 bit interface
  WriteData(parameter);
}

void MemoryWrite()
{
  WriteCommand(0x2C);
}


// Red 0-31, Green 0-63, Blue 0-31
void WritePixel(unsigned char red, unsigned char green, unsigned char blue)
{
  unsigned int wordRed = ((unsigned int)red)<<11;
  unsigned int wordGreen = ((unsigned int)green)<<5;
  unsigned int wordBlue = blue;
  unsigned int twoBytesRGB;
  twoBytesRGB = wordRed | wordGreen | wordBlue;
  WriteData(twoBytesRGB);
}



// Set Column Address (0-239), Start > End
void SetColumnAddress(unsigned int start, unsigned int end)
{
  WriteCommand(0x2a);
  WriteData(start>>8);
  WriteData(start);
  WriteData(end>>8);
  WriteData(end);
}

// Set Page Address (0-319), Start > End
void SetPageAddress(unsigned int start, unsigned int end)
{
  WriteCommand(0x2b);
  WriteData(start>>8);
  WriteData(start);
  WriteData(end>>8);
  WriteData(end);
}

// Fills rectangle with specified color
// (StartX,StartY) = Upper left corner. X horizontal (0-319) , Y vertical (0-239).
// Height (1-240) is vertical. Width (1-320) is horizontal.
// R-G-B = 5-6-5 bits.
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue)
{
  SetColumnAddress(StartY, StartY+Height);
  SetPageAddress(StartX,StartX+Width);
  MemoryWrite();
  unsigned long numPix = ((unsigned long)Height+1)*((unsigned long)Width+1);
  for (unsigned long i=0; i < numPix ; i++){
    WritePixel(Red,Green,Blue);
  }
}




