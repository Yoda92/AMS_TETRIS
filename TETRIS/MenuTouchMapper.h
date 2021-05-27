struct Coordinate;

typedef enum {
	NEW_GAME,
	HIGH_SCORES
} MenuAction;

MenuAction menuActionFromCoordinate(struct Coordinate coord);