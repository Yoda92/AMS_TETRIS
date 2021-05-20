/*
 * block.c
 *
 * Created: 15-04-2021 09:41:15
 *  Author: ander
 */ 
#include "blocks.h"

Block CombinesBlocks(Block first, Block second) {
	return first == EMPTY ? second : first;
}

bool CanCombine(Block first, Block second) {
	if (first == EMPTY || second == EMPTY) {
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
