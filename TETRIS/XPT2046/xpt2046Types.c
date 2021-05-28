#include "xpt2046Types.h"

int IsCoordInRect(Coordinate coord, Rectangle rect)
{
    if (coord.x < rect.topLeftX ||
		coord.y < rect.topLeftY ||
        coord.x >= rect.bottomRightX ||
        coord.y >= rect.bottomRightY)
    {
        return 0;
    }
	
    return 1;
}