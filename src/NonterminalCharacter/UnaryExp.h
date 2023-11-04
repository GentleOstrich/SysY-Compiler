//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_UNARYEXP_H
#define SYSY_COMPILER_UNARYEXP_H

#include "PrimaryExp.h"
#include "Ident.h"
#include "FuncRParams.h"
#include "UnaryExp.h"
#include "UnaryOp.h"
#include <vector>

class UnaryExp {
public:
    PrimaryExp *primaryExp;
    Ident *ident;
    std::vector<FuncRParams *> funcRParamss;
    UnaryOp *unaryOp;
    UnaryExp *unaryExp1;

    UnaryExp();

    void setPrimaryExp(PrimaryExp *primaryExp);

    void setIdent(Ident *ident);

    void addFuncRParams(FuncRParams *funcRParams);

    void setUnaryOp(UnaryOp *unaryOp);

    void setUnaryExp1(UnaryExp *unaryExp1);
};


#endif //SYSY_COMPILER_UNARYEXP_H
