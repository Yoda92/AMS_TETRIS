#include "blocks.h"

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

Block CombinesBlocks(Block a, Block b) {
	return a == EMPTY ? b : a;
}

bool CanCombine(Block a, Block b) {
	if (a == EMPTY || b == EMPTY) {
		return true;
	} else {
		return false;
	}
}

Color GetRGBColor(Block block) {
	switch(block){
		case EMPTY: {
			return rgbColors.black;
			break;
		}
		case RED: {
			return rgbColors.red;
			break;
		}
		case GREEN: {
			return rgbColors.green;
			break;
		}
		case BLUE: {
			return rgbColors.blue;
			break;
		}
		case LIGHTBLUE: {
			return rgbColors.lightblue;
			break;
		}
		case MAGENTA: {
			return rgbColors.magenta;
			break;
		}
		case YELLOW: {
			return rgbColors.yellow;
			break;
		}
		case ORANGE: {
			return rgbColors.orange;
			break;
		}
		default: {
			return rgbColors.white;
			break;
		}
	}
}
