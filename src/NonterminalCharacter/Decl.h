//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_DECL_H
#define SYSY_COMPILER_DECL_H
#include "ConstDecl.h"
#include "VarDecl.h"

class Decl {
public:
    ConstDecl *constDecl;
    VarDecl *varDecl;
    Decl();
    void setConstDecl(ConstDecl *constDecl);
    void setVarDecl(VarDecl *varDecl);
};


#endif //SYSY_COMPILER_DECL_H
