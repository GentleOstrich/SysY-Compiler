//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCDEF_H
#define SYSY_COMPILER_FUNCDEF_H
#include "FuncType.h"
#include "Ident.h"
#include "FuncFParams.h"
#include "Block.h"
#include <vector>

class FuncDef {
public:
    FuncType *funcType;
    Ident *ident;
    FuncFParams *funcFParams;
    Block *block;
    FuncDef();
    void setFuncType(FuncType *funcType);
    void setIdent(Ident* ident);
    void setFuncFParams(FuncFParams *funcFParams);
    void setBlock(Block *block);
};


#endif //SYSY_COMPILER_FUNCDEF_H
