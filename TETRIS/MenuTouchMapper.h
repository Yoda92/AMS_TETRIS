#ifndef MENUTOUCHMAPPER_H_
#define MENUTOUCHMAPPER_H_

#include "XPT2046/xpt2046Types.h"

typedef enum {
	NEW_GAME,
	HIGH_SCORES
} MenuAction;

MenuAction menuActionFromCoordinate(Coordinate coord);

#endif /* MENUTOUCHMAPPER_H_ */
