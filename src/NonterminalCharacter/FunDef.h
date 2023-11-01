//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNDEF_H
#define SYSY_COMPILER_FUNDEF_H
#include "Nonterminal.h"
#include <vector>

class FunDef : Nonterminal{
public:
    Nonterminal *FuncType;
    Nonterminal *Ident;
    std::vector<Nonterminal *> FuncFParams;
    Nonterminal *Block;
    FunDef();
    int setFuncType(Nonterminal *FuncType);
    int setIdent(Nonterminal* Ident);
    int addFuncFParam(Nonterminal *FuncFParam);
    int setBlock(Nonterminal *Block);
};


#endif //SYSY_COMPILER_FUNDEF_H
