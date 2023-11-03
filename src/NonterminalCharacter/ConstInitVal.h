//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTINITVAL_H
#define SYSY_COMPILER_CONSTINITVAL_H
#include "ConstExp.h"
#include "ConstInitVal.h"
#include <vector>

class ConstInitVal : Nonterminal{
public:
    ConstExp *constExp;
    std::vector<ConstInitVal*> constInitVals;
    ConstInitVal();
    void setConstExp(ConstExp *constExp);
    void addConstInitVal(ConstInitVal *constInitVal);
};


#endif //SYSY_COMPILER_CONSTINITVAL_H
