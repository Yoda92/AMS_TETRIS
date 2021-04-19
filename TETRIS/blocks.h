/*
 * block.h
 *
 * Created: 15-04-2021 09:11:31
 *  Author: ander
 */ 


#ifndef BLOCK_H_
#define BLOCK_H_

#include <stdbool.h>

typedef enum {
	EMPTY,
	RED,
	GREEN,
	BLUE, 
	LIGHTBLUE, 
	MAGENTA,
	YELLOW,
	ORANGE
} Block;

Block CombinesBlocks(Block, Block);
bool CanCombine(Block, Block);

#endif /* BLOCK_H_ */