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

void setChipSelect(unsigned char state);
void setClock(unsigned char state);
void risingClock();
void fallingClock();
void setMasterOutValue(unsigned char state);
unsigned char getMasterInValue();
unsigned char getMSB(unsigned char byte);
unsigned char setLSB(unsigned char byte, unsigned char state);

// Takes high or low
void setChipSelect(unsigned char state)
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

void setClock(unsigned char state)
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

void risingClock()
{
    setClock(HIGH);
}
void fallingClock()
{
    setClock(LOW);
}

// Takes high or low
void setMasterOutValue(unsigned char state)
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
unsigned char getMasterInValue()
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

unsigned char getMSB(unsigned char byte)
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

unsigned char setLSB(unsigned char byte, unsigned char state)
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


unsigned char readWriteByte(unsigned char command)
{
	setMasterOutValue(0);
    int buffer = command;
    setClock(LOW);
    setChipSelect(LOW);
    // For each bit in byte
    for (unsigned char i = 0; i < 8; i++)           
    {
        setMasterOutValue(getMSB(buffer));
        buffer = buffer << 1;
		_NOP();
        risingClock();
		_NOP();
        fallingClock();
		_NOP();
        buffer = setLSB(buffer, getMasterInValue());
		_NOP();
    }
    return (unsigned char)buffer;
}

unsigned char readWriteLastByte(unsigned char command){
    unsigned char result = readWriteByte(command);
    setChipSelect(HIGH);
    return result;
}



unsigned char readSimplex(unsigned char command)
{
	char buffer = 0;
	setMasterOutValue(0);
	setClock(LOW);
    setChipSelect(LOW);
    // For each bit in byte
    for (unsigned char i = 0; i < 8; i++)           
    {
        setMasterOutValue(getMSB(command << i));
        _NOP();
        setClock(HIGH);
        _NOP();
        setClock(LOW);
    }
	_NOP();
	_NOP();
	for (unsigned char i = 0; i < 8; i++)
	{
		setClock(HIGH);
		_NOP();
		setClock(LOW);
		_NOP();
		buffer |= getMasterInValue() << (unsigned char)(7 - i);
		_NOP();
	}
	
    setChipSelect(HIGH);
    return buffer;
}