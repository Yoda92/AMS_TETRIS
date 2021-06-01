#include "graphics.h"

#define TETRIS_HEIGHT 270
#define SCORE_HEIGHT 50
#define BLOCK_COUNT_HEIGHT 18
#define BLOCK_COUNT_WIDTH 16
#define BLOCK_HEIGHT TETRIS_HEIGHT / BLOCK_COUNT_HEIGHT
#define BLOCK_WIDTH SCREEN_WIDTH / BLOCK_COUNT_WIDTH

Shape referenceShape;
size_t referenceScore;

/****************************************************************************************************/
/****************************************** Private Methods ******************************************/
/****************************************************************************************************/

char ReverseBits(char bits);
void RenderScore(size_t score);
void RenderTetris(Shape* shape);
void RenderScoreBackground();

char ReverseBits(char bits) {
	char reverseBits = 0b00000000;
	for(int i = 0; i < 8; i++) {
		reverseBits |= ((bits >> i) & 1) << (7 - i);
	}
	return reverseBits;
}

void RenderScoreBackground() {
	FillRectangle(0, 0, SCREEN_WIDTH, SCORE_HEIGHT, rgbColors.teal);
}

void RenderScore(size_t score) {
	FillRectangle(0, 5, SCREEN_WIDTH, SCORE_HEIGHT - 10, rgbColors.teal);
	char _score[12];
	sprintf(_score, "%d", score);
	RenderText(_score, SCREEN_WIDTH - strlen(_score) * 5 * 8, 5, 5, rgbColors.white, rgbColors.teal);
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

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void RenderBackground() {
	FillRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, rgbColors.black);
}

void InitGraphics() {
	IL19341Init();
}

void InitTetrisGraphics() {
	RenderBackground();
	RenderScoreBackground();
	RenderScore(0);
	referenceShape = CreateEmptyShape(BLOCK_COUNT_HEIGHT, BLOCK_COUNT_WIDTH);
}

void DestroyTetrisGraphics() {
	DeleteShape(&referenceShape);
}

void DisplayGameOver() {
	RenderBackground();
	RenderText("GAME OVER", 12, 148, 3, rgbColors.white, rgbColors.black);
	RenderText("Tap screen to return.", 40, 190, 1, rgbColors.yellow, rgbColors.black);
}

void RenderGame(Shape* shape, size_t score) {
	if (score != referenceScore) {
		RenderScore(score);
	}
	RenderTetris(shape);
}

void RenderText(char* text, size_t StartX, size_t StartY, size_t size, Color textColor, Color backgroundColor) {
	for(int i = 0; i < strlen(text); i++) {
		int asciiChar = (int) text[i];
		char* character = font8x8_basic[asciiChar];
		char swappedCharacter[8];
		for(int y = 0; y < 8; y++) {
			swappedCharacter[y] = ReverseBits(character[y]);
		}
		DrawBitmap(swappedCharacter, i * 8 * size + StartX, StartY, size, textColor, backgroundColor);
	}
}