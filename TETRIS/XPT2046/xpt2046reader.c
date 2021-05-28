#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include "spi.h"
#include "xpt2046reader.h"

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

unsigned char ReadX();
unsigned char ReadY();
void InitInterrupt();

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void InitReader()
{
    InitInterrupt();
    initSpi();
}

ADC_read GetRawADCCoordates(){
    ADC_read reading;
    reading.x = ReadX();
    reading.y = ReadY();
    return reading;
}

/****************************************************************************************************/
/***************************************** Private Methods ******************************************/
/****************************************************************************************************/

unsigned char Read(unsigned char command)
{
    //Send command and perform dummy write in order to read result.
    ReadWriteByte(command);
    _NOP();
    _NOP();
    return ReadWriteLastByte((unsigned char)0b00000000);
}

unsigned char ReadX()
{
    return Read((unsigned char)0b11011000);
}

unsigned char ReadY()
{
    return Read((unsigned char)0b10011000);
}

void InitInterrupt()
{
    EIMSK = 0b00010000; //Activate intterupt 4.
    EICRA = 0b00000000;
    EICRB = 0b00000010; //falling edge activation of interrupt 4.
}

unsigned char SimplexRead(){
    return ReadSimplex(0b11011000);
}