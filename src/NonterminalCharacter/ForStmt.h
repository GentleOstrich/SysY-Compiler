//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FORSTMT_H
#define SYSY_COMPILER_FORSTMT_H
#include "Nonterminal.h"
#include <vector>

class ForStmt : Nonterminal{
public:
    Nonterminal *LVal;
    Nonterminal *Exp;
    ForStmt();

    void setLVal(Nonterminal *lVal);

    void setExp(Nonterminal *exp);
};


#endif //SYSY_COMPILER_FORSTMT_H
