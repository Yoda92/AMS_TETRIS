
struct Coordinate;
typedef enum {
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	DROP_TO_BOTTOM
} PlayerAction;

PlayerAction ActionFromCoordinate(struct Coordinate coord);