#include "spi.h"
#include "avr/io.h"
#include "util/delay.h"

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


unsigned char readWriteByte(unsigned char writeThis)
{
    unsigned char buf = writeThis;
    setChipSelect(LOW);
    setClock(LOW);
    // For each bit in byte
    for (unsigned char i = 0; i < 8; i++)
    {
        setMasterOutValue(getMSB(buf));
        buf << 1;
        _delay_us(1);
        risingClock();
        buf = setLSB(buf, getMasterInValue());
        _delay_us(1);
        fallingClock();
    }
    setChipSelect(HIGH);
    return buf;
}

/****************************************************************************************************/
/***************************************** Private Methods ******************************************/
/****************************************************************************************************/
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
    if (MASTER_IN_PORT & (1 << MASTER_IN_PIN))
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
    if (byte & (1 << 7))
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
        byte &= ~(1);
    }
    else if (state == HIGH)
    {
        byte |= 1;
    }
    return byte;
}