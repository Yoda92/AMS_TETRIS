#include "xpt2046.h"
#include <math.h>


#define TOUCH_INTERRUPT_PIN 0
#define CHIP_SELECT_PIN 0
#define MASTER_OUT_PIN 0
#define MASTER_IN_PIN 0
#define SPI_CLOCK_PIN 0

void init()
{

}


// ADC related
struct Coordinate coordFromADC(struct ADC_read reading)
{
    struct Coordinate coord;
    coord.x = dimensionFromFraction(fractionFromADC(reading.x),X_DIMENSION);
    coord.y = dimensionFromFraction(fractionFromADC(reading.y),Y_DIMENSION);
    return coord;
}

float fractionFromADC(unsigned int ADC_val)
{
    return (float)ADC_val / (float)ADC_MAXVAL;
}

unsigned int dimensionFromFraction(float fraction, unsigned int maxDimension)
{
    (unsigned int)round(fraction*(float)maxDimension);
}

// SPI related
struct ADC_read readADC()
{

}