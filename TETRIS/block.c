/*
 * block.c
 *
 * Created: 15-04-2021 09:41:15
 *  Author: ander
 */ 
#include "block.h"

Block combinesBlocks(Block first, Block second) {
	return first > second ? first : second;
}

bool canCombine(Block first, Block second) {
	if (first == EMPTY || second == EMPTY) {
		return true;
	} else {
		return false;
	}
}
