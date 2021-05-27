#ifndef COORDINATEMAPPER_H_
#define COORDINATEMAPPER_H_

#include "xpt2046Types.h"
#include "../models/direction.h"

typedef enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE,
	DROP_TO_BOTTOM
} PlayerAction;

PlayerAction actionFromCoordinate(struct Coordinate coord);

Direction getDirectionFromAction(PlayerAction action);

#endif /* COORDINATEMAPPER_H_ */