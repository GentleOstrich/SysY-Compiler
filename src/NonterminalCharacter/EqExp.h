//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_EQEXP_H
#define SYSY_COMPILER_EQEXP_H

#include "RelExp.h"
#include "EqExp.h"

class EqExp {
public:
    RelExp *relExp;
    EqExp *eqExp1;
    RelExp *relExp1;
    EqExp();

    void setRelExp(RelExp *relExp);

    void setEqExp1(EqExp *eqExp1);

    void setRelExp1(RelExp *relExp1);
};


#endif //SYSY_COMPILER_EQEXP_H
