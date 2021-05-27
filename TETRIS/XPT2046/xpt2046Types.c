#include "xpt2046Types.h"

int isCoordInRect(Coordinate coord, struct Rectangle rect)
{
    if (coord.x < rect.topLeftX ||
        coord.x > rect.bottomRightX ||
		coord.y > rect.topLeftY ||
        coord.y < rect.bottomRightY)
    {
        return 0;
    }
	
    return 1;
}