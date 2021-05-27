#include "xpt2046ADC.h"
#include <math.h>
#include "xpt2046Types.h"






// ADC related
struct Coordinate coordFromADC(struct ADC_read reading)
{
    struct Coordinate coord;
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

