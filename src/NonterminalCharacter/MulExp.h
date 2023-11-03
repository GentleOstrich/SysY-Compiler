//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_MULEXP_H
#define SYSY_COMPILER_MULEXP_H

#include "Nonterminal.h"

class MulExp : Nonterminal{
public:
    Nonterminal *UnaryExp;
    Nonterminal *MulExp1;
    Nonterminal *UnaryExp1;

    MulExp();

    void setUnaryExp(Nonterminal *unaryExp);

    void setMulExp1(Nonterminal *mulExp1);

    void setUnaryExp1(Nonterminal *unaryExp1);
};


#endif //SYSY_COMPILER_MULEXP_H
