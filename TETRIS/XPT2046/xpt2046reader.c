#include <avr/io.h>
#include "spi.h"
#include <avr/interrupt.h>


#define READ_X 0x91
#define READ_Y 0xD1
#define READ_Z 0xC1

#define START_BIT = 7
#define CHANNEL_SELECT_MSB 6
#define MODE_BIT 3
#define SINGLE_ENDED_OR_DIFFERENTIAL_REF_BIT 2
#define POWER_DOWN_MODE_MSB 1

#define D_IRQ_PORT PORTE
#define D_IRQ_PIN 4 //INT4

unsigned int readTwoBytes(unsigned char command);
unsigned char readX();
unsigned char readY();
void initInterrupt();


/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void initReader()
{
    initInterrupt();
    initSpi();
    // readWriteByte(0xD0);
}

unsigned char getTouchCoordinates()
{
    return readX();
}

/****************************************************************************************************/
/***************************************** Private Methods ******************************************/
/****************************************************************************************************/

unsigned int readTwoBytes(unsigned char command)
{
    //Read two bytes
    readWriteByte(command);
    unsigned int MSByte = (unsigned int)readWriteByte(0);
    unsigned int LSByte = (unsigned int)readWriteByte(0);
    unsigned int combined = (MSByte << 8) & LSByte;
    return combined;
}

unsigned char readInput(char command) {
	return readWriteByte(command);
}

unsigned char readX()
{
    return readInput(0b11011000);
}

unsigned char readY()
{
    return readTwoBytes(0b10011000);
}

void initInterrupt()
{
    EIMSK = 0b00010000; //Activate intterupt 4.
    EICRA = 0b00000000;
    EICRB = 0b00000010; //falling edge activation of interrupt 4.
}