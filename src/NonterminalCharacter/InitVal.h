//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_INITVAL_H
#define SYSY_COMPILER_INITVAL_H
#include "Nonterminal.h"
#include <vector>

class InitVal : Nonterminal{
    Nonterminal *Exp;
    std::vector<Nonterminal*> InitVals;
    InitVal();
    int setExp(Nonterminal *Exp);
    int addInitVal(Nonterminal *InitVal);

};


#endif //SYSY_COMPILER_INITVAL_H
