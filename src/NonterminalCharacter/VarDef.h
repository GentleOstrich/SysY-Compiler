//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDEF_H
#define SYSY_COMPILER_VARDEF_H
#include "Nonterminal.h"
#include <vector>

class VarDef : Nonterminal{
public:
    Nonterminal *Ident;
    std::vector<Nonterminal*> ConstExps;
    VarDef();
    int setIdent(Nonterminal *Ident);
    int addConstExp(Nonterminal *ConstExp);
};


#endif //SYSY_COMPILER_VARDEF_H
