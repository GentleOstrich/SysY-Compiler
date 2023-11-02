//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_BLOCK_H
#define SYSY_COMPILER_BLOCK_H
#include "Nonterminal.h"
#include <vector>

class Block : Nonterminal{
    std::vector<Nonterminal *> BlockItems;
    Block();
    int addBlockItem(Nonterminal *BlockItem);
};


#endif //SYSY_COMPILER_BLOCK_H
