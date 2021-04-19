/*
 * block.c
 *
 * Created: 15-04-2021 09:41:15
 *  Author: ander
 */ 
#include "blocks.h"

Block CombinesBlocks(Block first, Block second) {
	return first > second ? first : second;
}

bool CanCombine(Block first, Block second) {
	if (first == EMPTY || second == EMPTY) {
		return true;
	} else {
		return false;
	}
}
