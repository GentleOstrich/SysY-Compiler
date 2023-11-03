//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_LANDEXP_H
#define SYSY_COMPILER_LANDEXP_H

#include "Nonterminal.h"

class LAndExp : Nonterminal {
public:
    Nonterminal *EqExp;
    Nonterminal *LAndExp1;
    Nonterminal *EqExp1;
    LAndExp();

    void setEqExp(Nonterminal *eqExp);

    void setLAndExp1(Nonterminal *lAndExp1);

    void setEqExp1(Nonterminal *eqExp1);
};


#endif //SYSY_COMPILER_LANDEXP_H
