//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDECL_H
#define SYSY_COMPILER_CONSTDECL_H
#include "Btype.h"
#include "ConstDef.h"
#include <vector>

class ConstDecl {
public:
    Btype *btype;
    std::vector<ConstDef*> constDefs;
    ConstDecl();
    void setBtype(Btype *btype);
    void addConstDef(ConstDef *constDef);
};


#endif //SYSY_COMPILER_CONSTDECL_H
