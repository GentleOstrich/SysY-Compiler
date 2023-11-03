//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCFPARAMS_H
#define SYSY_COMPILER_FUNCFPARAMS_H
#include "FuncFParam.h"
#include <vector>

class FuncFParams {
public:
    std::vector<FuncFParam *> funcFParams;
    FuncFParams();
    void addFuncFParam(FuncFParam *funcFParam);
};


#endif //SYSY_COMPILER_FUNCFPARAMS_H
