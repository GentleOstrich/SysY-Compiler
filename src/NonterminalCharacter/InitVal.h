//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_INITVAL_H
#define SYSY_COMPILER_INITVAL_H
#include "Exp.h"
#include "InitVal.h"
#include <vector>

class InitVal{
public:
    Exp *exp;
    std::vector<InitVal*> initVals;
    InitVal();
    void setExp(Exp *exp);
    void addInitVal(InitVal *initVal);
};


#endif //SYSY_COMPILER_INITVAL_H
