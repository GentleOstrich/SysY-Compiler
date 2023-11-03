//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FUNCFPARAM_H
#define SYSY_COMPILER_FUNCFPARAM_H
#include "Btype.h"
#include "Ident.h"
#include "ConstExp.h"
#include <vector>

class FuncFParam {
public:
    Btype *btype;
    Ident *ident;
    std::vector<ConstExp*> constExps;
    FuncFParam();
    void setBtype(Btype *btype);
    void setIdent(Ident *ident);
    void addConstExp(ConstExp *constExp);
};


#endif //SYSY_COMPILER_FUNCFPARAM_H
