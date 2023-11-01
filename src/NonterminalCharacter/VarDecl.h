//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDECL_H
#define SYSY_COMPILER_VARDECL_H
#include "Nonterminal.h"
#include <vector>
class VarDecl : Nonterminal{
public:
    Nonterminal *BType;
    std::vector<Nonterminal*> VarDefs;
    VarDecl();
    int setBType(Nonterminal *BType);
    int addVarDef(Nonterminal *VarDef);

};


#endif //SYSY_COMPILER_VARDECL_H
