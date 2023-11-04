//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_RELEXP_H
#define SYSY_COMPILER_RELEXP_H
#include "AddExp.h"
#include "RelExp.h"

class RelExp  {
public:
    AddExp *addExp;
    RelExp *relExp1;
    AddExp *addExp1;
    RelExp();

    void setAddExp(AddExp *addExp);

    void setRelExp1(RelExp *relExp1);

    void setAddExp1(AddExp *addExp1);
};


#endif //SYSY_COMPILER_RELEXP_H
