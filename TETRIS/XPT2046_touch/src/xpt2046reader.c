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
unsigned int readX();
unsigned int readY();
unsigned int readZ();
void initInterrupt();


/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void initReader()
{
    initInterrupt();
    initSpi();
    readWriteByte(0xD0);
}

void onScreenPressed(unsigned int *X, unsigned int *Y, unsigned int *Z)
{
    *X = readX();
    *Y = readY();
    *Z = readZ();
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

unsigned int readX()
{
    return readTwoBytes(READ_X<<3);
}

unsigned int readY()
{
    return readTwoBytes(READ_Y<<3);
}

unsigned int readZ()
{
    return readTwoBytes(READ_Z<<3);
}

void initInterrupt()
{
    EIMSK = 0b00010000; //Activate intterupt 4.
    EICRA = 0b00000000;
    EICRB = 0b00000011; //rising edge activation of interrupt 4.
    sei();
}