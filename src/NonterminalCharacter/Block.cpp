//
// Created by lyh on 2023/11/2.
//

#include "Block.h"

Block::Block() {

}

int Block::addBlockItem(Nonterminal *BlockItem) {
    this->BlockItems.push_back(BlockItem);
    return 0;
}
