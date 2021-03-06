#include "menu.h"
#include "coordinateMappers/menuMapper.h"
#include "XPT2046/xpt2046.h"
#include "XPT2046/xpt2046Types.h"

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
	RenderBackground();
	RenderLogo();
	CreateButtons();
}

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

void RunMenu() {
	while (1) {
		InitMenu();
		sei();
		while (!actionReady) {}
		cli();
		Coordinate coordinates = ReadLatestCoordinate();
		MenuAction menuAction =  MenuActionFromCoordinate(coordinates);
		switch (menuAction)
		{
			case NEW_GAME:
			{
				RunTetris((coordinates.x * 5) + (coordinates.y * 5));
				break;	
			}
			
			case HIGH_SCORES:
			{
				HighScores();
				break;
			}
			
			default:
			{
				break;		
			}
		}
	}
}
