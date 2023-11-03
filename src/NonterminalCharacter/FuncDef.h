//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCDEF_H
#define SYSY_COMPILER_FUNCDEF_H
#include "FuncType.h"
#include "Ident.h"
#include "FuncFParam.h"
#include "Block.h"
#include <vector>

class FuncDef : Nonterminal{
public:
    FuncType *funcType;
    Ident *ident;
    std::vector<FuncFParam*> funcFParams;
    Block *block;
    FuncDef();
    void setFuncType(FuncType *funcType);
    void setIdent(Ident* ident);
    void addFuncFParam(FuncFParam *funcFParam);
    void setBlock(Block *block);
};


#endif //SYSY_COMPILER_FUNCDEF_H
