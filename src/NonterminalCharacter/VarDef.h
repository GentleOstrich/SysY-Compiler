//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDEF_H
#define SYSY_COMPILER_VARDEF_H
#include "Ident.h"
#include "ConstExp.h"
#include "InitVal.h"
#include <vector>

class VarDef {
public:
    Ident *ident;
    std::vector<ConstExp*> constExps;
    InitVal *initVal;
    VarDef();
    void setIdent(Ident *ident);
    void addConstExp(ConstExp *constExp);
    void setInitVal(InitVal *initVal);
};


#endif //SYSY_COMPILER_VARDEF_H
