//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_PRIMARYEXP_H
#define SYSY_COMPILER_PRIMARYEXP_H
#include "Exp.h"
#include "LVal.h"
#include "Number.h"
#include <vector>

class PrimaryExp {
public:
    Exp* exp;
    LVal* lVal;
    Number* number;
    PrimaryExp();

    void setExp(Exp *exp);

    void setLVal(LVal *lVal);

    void setNumber(Number *number);

};


#endif //SYSY_COMPILER_PRIMARYEXP_H
