//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_UNARYEXP_H
#define SYSY_COMPILER_UNARYEXP_H

#include "Nonterminal.h"
#include <vector>

class UnaryExp : Nonterminal {
public:
    Nonterminal *PrimaryExp;
    Nonterminal *Ident;
    std::vector<Nonterminal *> FuncRParamss;
    Nonterminal *UnaryOp;
    Nonterminal *UnaryExp1;

    UnaryExp();

    void setPrimaryExp(Nonterminal *primaryExp);

    void setIdent(Nonterminal *ident);

    void addFuncRParams(Nonterminal *FuncRParams);

    void setUnaryOp(Nonterminal *unaryOp);

    void setUnaryExp1(Nonterminal *unaryExp1);
};


#endif //SYSY_COMPILER_UNARYEXP_H
