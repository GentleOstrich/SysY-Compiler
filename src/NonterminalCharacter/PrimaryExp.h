//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_PRIMARYEXP_H
#define SYSY_COMPILER_PRIMARYEXP_H
#include "Nonterminal.h"
#include <vector>

class PrimaryExp {
public:
    Nonterminal* Exp;
    Nonterminal* LVal;
    Nonterminal* Number;
    PrimaryExp();

    void setExp(Nonterminal *exp);

    void setLVal(Nonterminal *lVal);

    void setNumber(Nonterminal *number);

};


#endif //SYSY_COMPILER_PRIMARYEXP_H
