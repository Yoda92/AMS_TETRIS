#ifndef XPT2046ADC_H_
#define XPT2046ADC_H_

#include "xpt2046Types.h"

#define ADC_MAXVAL 255
#define X_DIMENSION 240
#define Y_DIMENSION 320

// ADC related
Coordinate coordFromADC(ADC_read reading);
float fractionFromADC(unsigned int ADC_val);
unsigned int dimensionFromFraction(float fraction, unsigned int maxDimension);

#endif /* XPT2046ADC_H_ */

