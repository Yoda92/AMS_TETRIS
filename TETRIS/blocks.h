/*
 * block.h
 *
 * Created: 15-04-2021 09:11:31
 *  Author: ander
 */ 


#ifndef BLOCKS_H_
#define BLOCKS_H_

#include <stdbool.h>
#include <stdlib.h>
#include "models/block.h"
#include "colors.h"

Block CombinesBlocks(Block, Block);
bool CanCombine(Block, Block);
Color GetRGBColor(Block);

#endif /* BLOCKS_H_ */