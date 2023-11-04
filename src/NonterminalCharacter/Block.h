//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_BLOCK_H
#define SYSY_COMPILER_BLOCK_H

#include "BlockItem.h"
#include <vector>
class BlockItem;
class Block {
public:
    std::vector<BlockItem *> blockItems;
    Block();
    void addBlockItem(BlockItem *blockItem);
};


#endif //SYSY_COMPILER_BLOCK_H
