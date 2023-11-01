//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_MAINFUNCDEF_H
#define SYSY_COMPILER_MAINFUNCDEF_H
#include "Nonterminal.h"

class MainFuncDef : Nonterminal {
public:
    Nonterminal *Block;
    MainFuncDef();
    int setBlock(Nonterminal *Block);
};


#endif //SYSY_COMPILER_MAINFUNCDEF_H
