//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_DECL_H
#define SYSY_COMPILER_DECL_H
#include "Nonterminal.h"

class Decl : Nonterminal{
public:
    Nonterminal *ConstDecl;
    Nonterminal *VarDecl;
    Decl();
    int setConstDecl(Nonterminal *ConstDecl);
    int setVarDecl(Nonterminal *VarDecl);
};


#endif //SYSY_COMPILER_DECL_H
