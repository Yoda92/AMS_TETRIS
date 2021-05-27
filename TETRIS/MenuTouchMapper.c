#include "MenuTouchMapper.h"

struct Rectangle newGameButton = {
    .topLeftX = 24,
    .topLeftY = 80 + 64,
    .bottomRightX = 192 + 24,
    .bottomRightY = 80
};

struct Rectangle highScoresButton = {
    .topLeftX = 24,
    .topLeftY = 168 + 64,
    .bottomRightX = 192 + 24,
    .bottomRightY = 168
};

#include "graphics.h"

MenuAction menuActionFromCoordinate(Coordinate coord)
{
    if (isCoordInRect(coord, newGameButton))
    {
        return NEW_GAME;
    }
    if (isCoordInRect(coord, highScoresButton))
    {
        return HIGH_SCORES;
    }
	
	return -1;
}
