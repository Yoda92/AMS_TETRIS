#include "menu.h"

/****************************************************************************************************/
/****************************************** Private Methods ******************************************/
/****************************************************************************************************/

void RenderLogo() {;
	char* tetris = "TETRIS";
	for (int i = 0; tetris[i] != '\0'; i++) {
		RenderText(&tetris[i], 24 + i * 8 * 4 , 24, 4, rgbColors.yellow, rgbColors.black);
	}
}

void CreateButtons() {
	FillRectangle(24, 80, 192, 64, rgbColors.teal);
	RenderText("New Game", 56, 104, 2, rgbColors.white, rgbColors.teal);
	FillRectangle(24, 168, 192, 64, rgbColors.teal);
	RenderText("High scores", 32, 192, 2, rgbColors.white, rgbColors.teal);
}

void InitMenu() {
	InitGraphics();
	RenderBackground();
	RenderLogo();
	CreateButtons();
}

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void RunMenu() {
	InitMenu();
	// Todo fix
	while(1)
	{
		if (false) {
			RunTetris();
		}
	}
}
