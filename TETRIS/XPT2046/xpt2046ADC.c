#include "xpt2046ADC.h"
#include <math.h>

// ADC related
Coordinate coordFromADC(ADC_read reading)
{
    Coordinate coord;
    coord.x = dimensionFromFraction(fractionFromADC(reading.x),X_DIMENSION);
    coord.y = Y_DIMENSION - dimensionFromFraction(fractionFromADC(reading.y),Y_DIMENSION);
    return coord;
}

float fractionFromADC(unsigned int ADC_val)
{
    return ((float)ADC_val) / ((float)ADC_MAXVAL);
}

unsigned int dimensionFromFraction(float fraction, unsigned int maxDimension)
{
    return (unsigned int)round(fraction*(float)maxDimension);
}

