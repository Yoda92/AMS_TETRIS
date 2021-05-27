#include "XPT2046/xpt2046Types.h"
#include "MenuTouchMapper.h"

struct Rectangle newGameButton = {
    .topLeftX = 24,
    .topLeftY = 80,
    .bottomRightX = 192 - 24,
    .bottomRightY = 80 - 64};

struct Rectangle highScoresButton = {
    .topLeftX = 24,
    .topLeftY = 168,
    .bottomRightX = 192 - 24,
    .bottomRightY = 168 - 64};

MenuAction menuActionFromCoordinate(struct Coordinate coord)
{
    if (isCoordInRect(coord, newGameButton))
    {
        return NEW_GAME;
    }
    if (isCoordInRect(coord, highScoresButton))
    {
        return HIGH_SCORES;
    }
}
