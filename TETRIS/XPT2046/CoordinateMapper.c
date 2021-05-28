#include "CoordinateMapper.h"

#define ONE_THIRD_X 80
#define MIDDLE_X 120
#define TWO_THIRDS_X 160
#define MAX_X 240

#define MIDDLE_Y 160
#define MAX_Y 320

// Bottom left third of the screen
Rectangle moveLeftArea = {
    .topLeftX = 0,
    .topLeftY = MIDDLE_Y,
    .bottomRightX = ONE_THIRD_X,
    .bottomRightY = MAX_Y};

// Bottom right third of the screen
Rectangle moveRightArea = {
    .topLeftX = TWO_THIRDS_X,
    .topLeftY = MIDDLE_Y,
    .bottomRightX = MAX_X,
    .bottomRightY = MAX_Y};

// Bottom middle third of the screen
Rectangle moveDownArea = {
    .topLeftX = ONE_THIRD_X,
    .topLeftY = MIDDLE_Y,
    .bottomRightX = TWO_THIRDS_X,
    .bottomRightY = MAX_Y};


// Top half of the screen
Rectangle rotateArea = {
    .topLeftX = 0,
    .topLeftY = 0,
    .bottomRightX = MAX_X,
    .bottomRightY = MIDDLE_Y};

PlayerAction actionFromCoordinate(Coordinate coord)
{
    if (isCoordInRect(coord, moveLeftArea))
    {
        return MOVE_LEFT;
    }
    if (isCoordInRect(coord, moveRightArea))
    {
        return MOVE_RIGHT;
    }
    if (isCoordInRect(coord, moveDownArea))
    {
        return DROP_TO_BOTTOM;
    }
    if (isCoordInRect(coord, rotateArea))
    {
        return ROTATE;
    }
    return -1;
}



Direction getDirectionFromAction(PlayerAction action)
{
    switch (action)
    {
    case MOVE_LEFT:
        return LEFT;

    case MOVE_RIGHT:
        return RIGHT;

    case DROP_TO_BOTTOM:
        return DOWN;

    default:
        return NOOP;
    }
}