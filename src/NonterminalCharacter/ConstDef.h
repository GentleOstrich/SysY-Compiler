//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDEF_H
#define SYSY_COMPILER_CONSTDEF_H
#include "Nonterminal.h"
#include "vector"

class ConstDef : Nonterminal{
public:
    Nonterminal *Ident;
    std::vector<Nonterminal *> ConstExps;
    Nonterminal *ConstInitVal;
    ConstDef();
    int setIdent(Nonterminal *Ident);

};


#endif //SYSY_COMPILER_CONSTDEF_H
