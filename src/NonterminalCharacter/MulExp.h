//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_MULEXP_H
#define SYSY_COMPILER_MULEXP_H

#include "UnaryExp.h"
#include "MulExp.h"

class MulExp {
public:
    UnaryExp *unaryExp;
    MulExp *mulExp1;
    UnaryExp *unaryExp1;

    MulExp();

    void setUnaryExp(UnaryExp *unaryExp);

    void setMulExp1(MulExp *mulExp1);

    void setUnaryExp1(UnaryExp *unaryExp1);
};


#endif //SYSY_COMPILER_MULEXP_H
