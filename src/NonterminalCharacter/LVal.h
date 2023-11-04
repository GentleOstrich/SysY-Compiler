//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_LVAL_H
#define SYSY_COMPILER_LVAL_H
#include "Ident.h"
#include "Exp.h"
#include <vector>
class Exp;
class LVal {
public:
    Ident *ident;
    std::vector<Exp*> exps;
    LVal();
    void setIdent(Ident *ident);
    void addExp(Exp *exp);
};


#endif //SYSY_COMPILER_LVAL_H
