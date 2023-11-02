//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_COND_H
#define SYSY_COMPILER_COND_H
#include "Nonterminal.h"

class Cond : Nonterminal{
public:
    Nonterminal *LOrExp;
    Cond();
    void setLOrExp(Nonterminal *lOrExp);
};


#endif //SYSY_COMPILER_COND_H
