//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FORSTMT_H
#define SYSY_COMPILER_FORSTMT_H
#include "LVal.h"
#include "Exp.h"
#include <vector>

class ForStmt {
public:
    LVal *lVal;
    Exp *exp;
    ForStmt();

    void setLVal(LVal *lVal);

    void setExp(Exp *exp);
};


#endif //SYSY_COMPILER_FORSTMT_H
