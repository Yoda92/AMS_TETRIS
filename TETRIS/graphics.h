#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string.h>
#include <stdio.h>
#include "ILI9341/ILI9341.h"
#include "shapes.h"
#include "colors.h"
#include "assets/font8x8_basic.h"

#define TETRIS_HEIGHT 270
#define SCORE_HEIGHT 50
#define BLOCK_COUNT_HEIGHT 18
#define BLOCK_COUNT_WIDTH 16
#define BLOCK_HEIGHT TETRIS_HEIGHT / BLOCK_COUNT_HEIGHT
#define BLOCK_WIDTH SCREEN_WIDTH / BLOCK_COUNT_WIDTH

Shape referenceShape;
size_t referenceScore;

void DisplayGameOver();
void RenderBackground();
void InitGraphics();
void InitTetrisGraphics();
void RenderGame(Shape* shape, size_t score);
void RenderText(char* text, size_t StartX, size_t StartY, size_t size, Color textColor, Color backgroundColor);

#endif /* GRAPHICS_H_ */