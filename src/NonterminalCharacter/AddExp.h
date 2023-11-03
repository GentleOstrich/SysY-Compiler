//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_ADDEXP_H
#define SYSY_COMPILER_ADDEXP_H

#include "MulExp.h"

class AddExp {
public:
    MulExp *mulExp;
    AddExp *addExp1;
    MulExp *mulExp1;
    AddExp();

    void setMulExp(MulExp *mulExp);

    void setAddExp1(AddExp *addExp1);

    void setMulExp1(MulExp *mulExp1);
};


#endif //SYSY_COMPILER_ADDEXP_H
