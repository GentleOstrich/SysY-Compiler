//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDEF_H
#define SYSY_COMPILER_CONSTDEF_H
#include "Ident.h"
#include "ConstExp.h"
#include "ConstInitVal.h"
#include "vector"

class ConstDef {
public:
    Ident *ident;
    std::vector<ConstExp*> constExps;
    ConstInitVal *constInitVal;
    ConstDef();
    void setIdent(Ident *ident);

    void addConstExps(ConstExp *constExp);

    void setConstInitVal(ConstInitVal *constInitVal);
};


#endif //SYSY_COMPILER_CONSTDEF_H
