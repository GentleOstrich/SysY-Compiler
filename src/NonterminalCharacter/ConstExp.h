//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_CONSTEXP_H
#define SYSY_COMPILER_CONSTEXP_H
#include "AddExp.h"

class ConstExp {
public:
    AddExp *addExp;
    ConstExp();

    void setAddExp(AddExp *addExp);
};


#endif //SYSY_COMPILER_CONSTEXP_H
