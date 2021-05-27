#include "../models/direction.h"


struct Coordinate;
typedef enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE,
	DROP_TO_BOTTOM
} PlayerAction;

PlayerAction actionFromCoordinate(struct Coordinate coord);

Direction getDirectionFromAction(PlayerAction action);