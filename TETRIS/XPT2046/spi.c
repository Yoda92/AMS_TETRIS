#include "spi.h"
#include "avr/io.h"
#include <avr/cpufunc.h>

//Hard coded for spi mode 0

#define MASTER_OUT_DIRECTION_REG DDRG
#define MASTER_OUT_PORT PORTG
#define MASTER_OUT_PIN 5

#define MASTER_IN_DIRECTION_REG DDRE
#define MASTER_IN_PORT PORTE
#define MASTER_IN_PIN 5

#define CLOCK_PORT_DIRECTION_REG DDRH
#define CLOCK_PORT PORTH
#define CLOCK_PIN 3

#define CHIP_SELECT_DIRECTION_REG DDRE
#define CHIP_SELECT_PORT PORTE
#define CHIP_SELECT_PIN 3

#define LOW 0
#define HIGH 1

/****************************************************************************************************/
/***************************************** Private Methods ******************************************/
/****************************************************************************************************/

void SetChipSelect(unsigned char state);
void SetClock(unsigned char state);
void RisingClock();
void FallingClock();
void SetMasterOutValue(unsigned char state);
unsigned char GetMasterInValue();
unsigned char GetMSB(unsigned char byte);
unsigned char SetLSB(unsigned char byte, unsigned char state);

// Takes high or low
void SetChipSelect(unsigned char state)
{
    if (state == LOW)
    {
        CHIP_SELECT_PORT &= ~(1 << CHIP_SELECT_PIN);
    }
    else if (state == HIGH)
    {
        CHIP_SELECT_PORT |= (1 << CHIP_SELECT_PIN);
    }
}

void SetClock(unsigned char state)
{
    if (state == LOW)
    {
        CLOCK_PORT &= ~(1 << CLOCK_PIN);
    }
    else if (state == HIGH)
    {
        CLOCK_PORT |= (1 << CLOCK_PIN);
    }
}

void RisingClock()
{
    SetClock(HIGH);
}
void FallingClock()
{
    SetClock(LOW);
}

// Takes high or low
void SetMasterOutValue(unsigned char state)
{
    if (state == LOW)
    {
        MASTER_OUT_PORT &= ~(1 << MASTER_OUT_PIN);
    }
    else if (state == HIGH)
    {
        MASTER_OUT_PORT |= (1 << MASTER_OUT_PIN);
    }
}

// Returns high or low
unsigned char GetMasterInValue()
{
    if (PINE & (1 << MASTER_IN_PIN))
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}

unsigned char GetMSB(unsigned char byte)
{
    if (byte & 0b10000000)
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}

unsigned char SetLSB(unsigned char byte, unsigned char state)
{
    if (state == LOW)
    {
        byte &= (unsigned char)~(0b00000001);
    }
    else if (state == HIGH)
    {
        byte |= 1;
    }
    return byte;
}

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void initSpi()
{
    //Set as input
    MASTER_IN_DIRECTION_REG &= ~(1<<MASTER_IN_PIN);
    //Set as output
    MASTER_OUT_DIRECTION_REG |= (1<<MASTER_OUT_PIN);
    CLOCK_PORT_DIRECTION_REG |= (1<<CLOCK_PIN);
    CHIP_SELECT_DIRECTION_REG |= (1<<CHIP_SELECT_PIN);
}

unsigned char ReadWriteByte(unsigned char command)
{
	SetMasterOutValue(0);
    int buffer = command;
    SetClock(LOW);
    SetChipSelect(LOW);
    // For each bit in byte
    for (unsigned char i = 0; i < 8; i++)           
    {
        SetMasterOutValue(GetMSB(buffer));
        buffer = buffer << 1;
		_NOP();
        RisingClock();
		_NOP();
        FallingClock();
		_NOP();
        buffer = SetLSB(buffer, GetMasterInValue());
		_NOP();
    }
    return (unsigned char)buffer;
}

unsigned char ReadWriteLastByte(unsigned char command){
    unsigned char result = ReadWriteByte(command);
    SetChipSelect(HIGH);
    return result;
}

unsigned char ReadSimplex(unsigned char command)
{
	char buffer = 0;
	SetMasterOutValue(0);
	SetClock(LOW);
    SetChipSelect(LOW);
    // For each bit in byte
    for (unsigned char i = 0; i < 8; i++)           
    {
        SetMasterOutValue(GetMSB(command << i));
        _NOP();
        SetClock(HIGH);
        _NOP();
        SetClock(LOW);
    }
	_NOP();
	_NOP();
	for (unsigned char i = 0; i < 8; i++)
	{
		SetClock(HIGH);
		_NOP();
		SetClock(LOW);
		_NOP();
		buffer |= GetMasterInValue() << (unsigned char)(7 - i);
		_NOP();
	}
	
    SetChipSelect(HIGH);
    return buffer;
}