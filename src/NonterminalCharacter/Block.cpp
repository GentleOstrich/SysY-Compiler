//
// Created by lyh on 2023/11/2.
//

#include "Block.h"

Block::Block() {

}

void Block::addBlockItem(BlockItem *blockItem) {
    this->blockItems.push_back(blockItem);
}
