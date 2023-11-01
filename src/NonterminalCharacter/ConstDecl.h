//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDECL_H
#define SYSY_COMPILER_CONSTDECL_H
#include "Nonterminal.h"
#include <vector>

class ConstDecl : Nonterminal{
public:
    Nonterminal *Btype;
    std::vector<Nonterminal *> ConstDefs;
    ConstDecl();
    int setBtype(Nonterminal *Btype);
    int addConstDef(Nonterminal *ConstDef);
};


#endif //SYSY_COMPILER_CONSTDECL_H
