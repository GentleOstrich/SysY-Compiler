//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_LOREXP_H
#define SYSY_COMPILER_LOREXP_H

#include "LAndExp.h"
#include "LOrExp.h"

class LOrExp {
public:
    LAndExp *lAndExp;
    LOrExp *lOrExp1;
    LAndExp *lAndExp1;
    LOrExp();

    void setLAndExp(LAndExp *lAndExp);

    void setLOrExp1(LOrExp *lOrExp1);

    void setLAndExp1(LAndExp *lAndExp1);
};


#endif //SYSY_COMPILER_LOREXP_H
