//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_COND_H
#define SYSY_COMPILER_COND_H
#include "LOrExp.h"

class Cond : Nonterminal{
public:
    LOrExp *lOrExp;
    Cond();
    void setLOrExp(LOrExp *lOrExp);
};


#endif //SYSY_COMPILER_COND_H
