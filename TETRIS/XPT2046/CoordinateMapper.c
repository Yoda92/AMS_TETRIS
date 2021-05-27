
#include "CoordinateMapper.h"
#include "xpt2046Types.h"

#define ONE_THIRD_X 80
#define MIDDLE_X 120
#define TWO_THIRDS_X 160
#define MAX_X 240

#define MIDDLE_Y 160
#define MAX_Y 320

// Bottom left third of the screen
struct Rectangle moveLeftArea = (struct Rectangle){
    .topLeft = (struct Coordinate){.x = 0, .y = MIDDLE_Y},
    .bottomRight = (struct Coordinate){.x = ONE_THIRD_X, .y = MAX_Y}};

// Bottom right third of the screen
struct Rectangle moveRightArea = (struct Rectangle){
    .topLeft = (struct Coordinate){.x = TWO_THIRDS_X, .y = MIDDLE_Y},
    .bottomRight = (struct Coordinate){.x = MAX_X, .y = MAX_Y}};

// Bottom middle third of the screen
struct Rectangle dropToBottomArea = (struct Rectangle){
    .topLeft = (struct Coordinate){.x = ONE_THIRD_X, .y = MIDDLE_Y},
    .bottomRight = (struct Coordinate){.x = TWO_THIRDS_X, .y = MAX_Y}};

// Top left half of the screen
struct Rectangle rotateLeftArea = (struct Rectangle){
    .topLeft = (struct Coordinate){.x = 0, .y = 0},
    .bottomRight = (struct Coordinate){.x = MIDDLE_X, .y = MIDDLE_Y}};

// Top right half of the screen
struct Rectangle rotateRightArea = (struct Rectangle){
    .topLeft = (struct Coordinate){.x = MIDDLE_X, .y = 0},
    .bottomRight = (struct Coordinate){.x = MAX_X, .y = MIDDLE_Y}};

PlayerAction ActionFromCoordinate(struct Coordinate coord){
    if (isCoordInRect(coord,moveLeftArea)){return MOVE_LEFT;}
    if (isCoordInRect(coord,moveRightArea)){return MOVE_RIGHT;}
    if (isCoordInRect(coord,dropToBottomArea)){return DROP_TO_BOTTOM;}
    if (isCoordInRect(coord,rotateLeftArea)){return ROTATE_LEFT;}
    if (isCoordInRect(coord,rotateRightArea)){return ROTATE_RIGHT;}
}

int isCoordInRect(struct Coordinate coord, struct Rectangle rect)
{
    // Check if coord exeeds bounds of rect.
    if (coord.x <= rect.topLeft.x ||
        coord.y <= rect.topLeft.y ||
        coord.x > rect.bottomRight.x ||
        coord.y > rect.bottomRight.y)
    {
        return 0;
    }
    return 1;
}