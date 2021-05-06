/*
 * block.c
 *
 * Created: 15-04-2021 09:41:15
 *  Author: ander
 */ 
#include "blocks.h"

const Color black = { .red = 0, .green = 0, .blue = 0  };
const Color red = { .red = 255, .green = 0, .blue = 0  };
const Color green = { .red = 0, .green = 255, .blue = 0  };
const Color blue = { .red = 0, .green = 0, .blue = 255  };
const Color lightblue = { .red = 0, .green = 255, .blue = 255  };
const Color magenta = { .red = 255, .green = 0, .blue = 255  };
const Color yellow = { .red = 255, .green = 255, .blue = 0  };
const Color orange = { .red = 200, .green = 100, .blue = 100  };
const Color white = { .red = 255, .green = 255, .blue = 255  };

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
			return black;
			break;
		}
		case RED: {
			return red;
			break;
		}
		case GREEN: {
			return green;
			break;
		}
		case BLUE: {
			return blue;
			break;
		}
		case LIGHTBLUE: {
			return lightblue;
			break;
		}
		case MAGENTA: {
			return magenta;
			break;
		}
		case YELLOW: {
			return yellow;
			break;
		}
		case ORANGE: {
			return orange;
			break;
		}
		default: {
			return white;
			break;
		}
	}
}
