/*
 * graphics.h
 *
 * Created: 22-04-2021 09:06:41
 *  Author: ander
 */ 


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "display.h"
#include <string.h>
#include <stdio.h>
#include "shapes.h"
#include "models/color.h"
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
void GraphicsInit();
void RenderGame(Shape*, size_t);
void RenderScore(size_t);
void RenderTetris(Shape*);
void RenderBackground();
void RenderText(char* text, size_t StartX, size_t StartY, size_t size);

#endif /* GRAPHICS_H_ */