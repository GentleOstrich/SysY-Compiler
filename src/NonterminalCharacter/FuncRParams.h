//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_FUNCRPARAMS_H
#define SYSY_COMPILER_FUNCRPARAMS_H

#include "Nonterminal.h"
#include <vector>

class FuncRParams : Nonterminal {
public:
    std::vector<Nonterminal *>Exps;
    FuncRParams();
    void addExp(Nonterminal *Exp);
};


#endif //SYSY_COMPILER_FUNCRPARAMS_H
