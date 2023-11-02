//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_LVAL_H
#define SYSY_COMPILER_LVAL_H
#include "Nonterminal.h"
#include <vector>

class LVal : Nonterminal {
public:
    Nonterminal *Ident;
    std::vector<Nonterminal *> Exps;
    LVal();
    int setIdent(Nonterminal *Ident);
    int addExp(Nonterminal *Exp);
};


#endif //SYSY_COMPILER_LVAL_H
