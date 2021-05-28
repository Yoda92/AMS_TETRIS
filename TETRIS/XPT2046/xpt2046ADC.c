#include "xpt2046ADC.h"
#include <math.h>

// ADC related
Coordinate CoordFromADC(ADC_read reading)
{
    Coordinate coord;
    coord.x = DimensionFromFraction(FractionFromADC(reading.x),X_DIMENSION);
    coord.y = Y_DIMENSION - DimensionFromFraction(FractionFromADC(reading.y),Y_DIMENSION);
    return coord;
}

float FractionFromADC(unsigned int ADC_val)
{
    return ((float)ADC_val) / ((float)ADC_MAXVAL);
}

unsigned int DimensionFromFraction(float fraction, unsigned int maxDimension)
{
    return (unsigned int)round(fraction*(float)maxDimension);
}

