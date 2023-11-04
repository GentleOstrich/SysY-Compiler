//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_FUNCRPARAMS_H
#define SYSY_COMPILER_FUNCRPARAMS_H

#include "Exp.h"
#include <vector>

class FuncRParams {
public:
    std::vector<Exp*>exps;
    FuncRParams();
    void addExp(Exp* exp);
};


#endif //SYSY_COMPILER_FUNCRPARAMS_H
