#include "xpt2046Types.h"
int isCoordInRect(struct Coordinate coord, struct Rectangle rect)
{
    // Check if coord exeeds bounds of rect.
    if (coord.x <= rect.topLeftX ||
        coord.y <= rect.topLeftY ||
        coord.x > rect.bottomRightX ||
        coord.y > rect.bottomRightY)
    {
        return 0;
    }
    return 1;
}