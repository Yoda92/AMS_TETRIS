#ifndef COORDINATEMAPPER_H_
#define COORDINATEMAPPER_H_

#include "../XPT2046/xpt2046Types.h"
#include "../models/direction.h"

typedef enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE,
	DROP_TO_BOTTOM
} PlayerAction;

PlayerAction TetrisActionFromCoordinate(Coordinate coord);
Direction GetDirectionFromAction(PlayerAction action);

#endif /* COORDINATEMAPPER_H_ */