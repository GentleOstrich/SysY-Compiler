//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_EXP_H
#define SYSY_COMPILER_EXP_H
#include "Nonterminal.h"
#include <vector>

class Exp : Nonterminal {
public:
    Nonterminal *AddExp;
    Exp();

    void setAddExp(Nonterminal *addExp);
};


#endif //SYSY_COMPILER_EXP_H
