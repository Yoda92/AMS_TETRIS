#ifndef BLOCKS_H_
#define BLOCKS_H_

#include <stdbool.h>
#include <stdlib.h>
#include "models/block.h"
#include "colors.h"

Block CombinesBlocks(Block a, Block b);
bool CanCombine(Block a, Block b);
Color GetRGBColor(Block block);

#endif /* BLOCKS_H_ */