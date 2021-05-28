#ifndef XPT2046_H_
#define XPT2046_H_

#include "xpt2046Types.h"
#include <stdbool.h>

void initXPT2046();
Coordinate readLatestCoordinate();
extern volatile bool actionReady;

#endif /* XPT2046_H_ */
