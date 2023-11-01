//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCFPARAMS_H
#define SYSY_COMPILER_FUNCFPARAMS_H
#include "Nonterminal.h"
#include <vector>

class FuncFParams : Nonterminal{
public:
    std::vector<Nonterminal *> FuncFParam;
    FuncFParams();
    int addFuncFParam(Nonterminal *FuncFParam);
};


#endif //SYSY_COMPILER_FUNCFPARAMS_H
