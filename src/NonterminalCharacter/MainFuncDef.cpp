//
// Created by lyh on 2023/11/1.
//

#include "MainFuncDef.h"

MainFuncDef::MainFuncDef() {
    this->Block = nullptr;
}

int MainFuncDef::setBlock(Nonterminal *Block) {
    this->Block = Block;
    return 0;
}
