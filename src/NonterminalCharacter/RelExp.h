//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_RELEXP_H
#define SYSY_COMPILER_RELEXP_H

#include "Nonterminal.h"


class RelExp : Nonterminal {
public:
    Nonterminal *AddExp;
    Nonterminal *RelExp1;
    Nonterminal *AddExp1;
    RelExp();

    void setAddExp(Nonterminal *addExp);

    void setRelExp1(Nonterminal *relExp1);

    void setAddExp1(Nonterminal *addExp1);
};


#endif //SYSY_COMPILER_RELEXP_H
