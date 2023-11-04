//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_LANDEXP_H
#define SYSY_COMPILER_LANDEXP_H

#include "EqExp.h"
#include "LAndExp.h"

class LAndExp {
public:
    EqExp *eqExp;
    LAndExp *lAndExp1;
    EqExp *eqExp1;
    LAndExp();

    void setEqExp(EqExp *eqExp);

    void setLAndExp1(LAndExp *lAndExp1);

    void setEqExp1(EqExp *eqExp1);
};


#endif //SYSY_COMPILER_LANDEXP_H
