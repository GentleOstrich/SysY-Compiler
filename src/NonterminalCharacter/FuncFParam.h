//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FUNCFPARAM_H
#define SYSY_COMPILER_FUNCFPARAM_H
#include "Nonterminal.h"
#include <vector>

class FuncFParam : Nonterminal {
public:
    Nonterminal *Btype;
    Nonterminal *Ident;
    std::vector<Nonterminal *> ConstExps;
    FuncFParam();
    int setBtype(Nonterminal *Btype);
    int setIdent(Nonterminal *Ident);
    int addConstExp(Nonterminal *ConstExp);
};


#endif //SYSY_COMPILER_FUNCFPARAM_H
