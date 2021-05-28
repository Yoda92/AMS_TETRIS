#include "menuMapper.h"

Rectangle newGameButton = {
    .topLeftX = 24,
    .topLeftY = 80 ,
    .bottomRightX = 192 + 24,
    .bottomRightY = 80 + 64
};

Rectangle highScoresButton = {
    .topLeftX = 24,
    .topLeftY = 168,
    .bottomRightX = 192 + 24,
    .bottomRightY = 168 + 64
};

MenuAction MenuActionFromCoordinate(Coordinate coord)
{
    if (IsCoordInRect(coord, newGameButton))
    {
        return NEW_GAME;
    }
    if (IsCoordInRect(coord, highScoresButton))
    {
        return HIGH_SCORES;
    }
	
	return -1;
}
