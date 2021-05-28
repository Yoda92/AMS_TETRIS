#ifndef XPT2046READER_H_
#define XPT2046READER_H_

#include "xpt2046Types.h"

//Uses the spi driver to read xpt2046

void initReader();
ADC_read getRawADCCoordates();
unsigned char simplexRead();

#endif /* XPT2046READER_H_ */