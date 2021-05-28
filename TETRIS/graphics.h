#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string.h>
#include <stdio.h>
#include "ILI9341/ILI9341.h"
#include "shapes.h"
#include "colors.h"
#include "assets/font8x8_basic.h"

void DisplayGameOver();
void RenderBackground();
void InitGraphics();
void InitTetrisGraphics();
void RenderGame(Shape* shape, size_t score);
void RenderText(char* text, size_t StartX, size_t StartY, size_t size, Color textColor, Color backgroundColor);

#endif /* GRAPHICS_H_ */