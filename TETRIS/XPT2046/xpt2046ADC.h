#ifndef XPT2046ADC_H_
#define XPT2046ADC_H_

#include "xpt2046Types.h"

#define ADC_MAXVAL 255
#define X_DIMENSION 239
#define Y_DIMENSION 319

// ADC related
Coordinate CoordFromADC(ADC_read reading);
float FractionFromADC(unsigned int ADC_val);
unsigned int DimensionFromFraction(float fraction, unsigned int maxDimension);

#endif /* XPT2046ADC_H_ */

