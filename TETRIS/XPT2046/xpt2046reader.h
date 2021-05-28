#ifndef XPT2046READER_H_
#define XPT2046READER_H_

#include "xpt2046Types.h"

//Uses the spi driver to read xpt2046

void InitReader();
ADC_read GetRawADCCoordates();
unsigned char SimplexRead();

#endif /* XPT2046READER_H_ */