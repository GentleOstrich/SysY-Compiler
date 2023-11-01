//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTINITVAL_H
#define SYSY_COMPILER_CONSTINITVAL_H
#include "Nonterminal.h"
#include <vector>
class ConstInitVal : Nonterminal{
public:
    Nonterminal *ConstExp;
    std::vector<Nonterminal*> ConstInitVals;
    ConstInitVal();
    int setConstExp(Nonterminal *ConstExp);
    int addConstInitVal(Nonterminal *ConstInitVal);
};


#endif //SYSY_COMPILER_CONSTINITVAL_H
