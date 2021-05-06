/*
 * graphics.c
 *
 * Created: 22-04-2021 09:06:28
 *  Author: ander
 */ 

#include "graphics.h"

const Color backgroundColor = { .red = 0, .green = 0, .blue = 0 };
const Color textColor = { .red = 255, .green = 255, .blue = 255 };
const Color textBackgroundColor = { .red = 50, .green = 50, .blue = 125 };
Shape referenceShape;
size_t referenceScore;

void GraphicsInit() {
	DisplayInit();
	RenderBackground();
	RenderScore(0);
	referenceShape = CreateEmptyShape(BLOCK_COUNT_HEIGHT, BLOCK_COUNT_WIDTH);
}

void RenderGame(Shape* shape, size_t score) {
	if (score != referenceScore) {
		RenderScore(score);
	}
	RenderTetris(shape);
}

char ReverseBits(char bits) {
	char reverseBits = 0b00000000;
	for(int i = 0; i < 8; i++) {
		reverseBits |= ((bits >> i) & 1) << (7 - i);
	}	
	return reverseBits;
}

void RenderText(char* text, size_t StartX, size_t StartY, size_t size) {
	for(int i = 0; i < strlen(text); i++) {
		int asciiChar = (int) text[i];
		char* character = font8x8_basic[asciiChar];
		char swappedCharacter[8];
		for(int y = 0; y < 8; y++) {
			swappedCharacter[y] = ReverseBits(character[y]);
		}
		DrawText(swappedCharacter, i * 8 * size + StartX, StartY, size, textColor, textBackgroundColor);
	}
}

void RenderBackground() {
	FillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundColor);
	FillRectangle(0, 0, SCREEN_WIDTH, SCORE_HEIGHT, textBackgroundColor);
}

void RenderScore(size_t score) {
	FillRectangle(0, 5, SCREEN_WIDTH, SCORE_HEIGHT - 10, textBackgroundColor);	
	char _score[12];
	sprintf(_score, "%d", score);
	RenderText(_score, SCREEN_WIDTH - strlen(_score) * 5 * 8, 5, 5);
	referenceScore = score;
}

void RenderTetris(Shape* shape)
{
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			if (shape->matrix[(y * shape->columns) + x] != referenceShape.matrix[(y * shape->columns) + x]) {
				FillRectangle(x*BLOCK_WIDTH, y*BLOCK_HEIGHT + SCORE_HEIGHT + 1, BLOCK_WIDTH, BLOCK_HEIGHT, GetRGBColor(shape->matrix[(y * shape->columns) + x]));
			}
		}
	}
	DeleteShape(&referenceShape);
	referenceShape = CopyShape(shape);
}