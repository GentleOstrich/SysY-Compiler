//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_EXP_H
#define SYSY_COMPILER_EXP_H

#include <vector>
#include "AddExp.h"

class Exp {
public:
    AddExp *addExp;
    Exp();

    void setAddExp(AddExp *addExp);
};


#endif //SYSY_COMPILER_EXP_H
