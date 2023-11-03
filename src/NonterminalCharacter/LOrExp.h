//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_LOREXP_H
#define SYSY_COMPILER_LOREXP_H

#include "Nonterminal.h"

class LOrExp : Nonterminal {
public:
    Nonterminal *LAndExp;
    Nonterminal *LOrExp1;
    Nonterminal *LAndExp1;
    LOrExp();

    void setLAndExp(Nonterminal *lAndExp);

    void setLOrExp1(Nonterminal *lOrExp1);

    void setLAndExp1(Nonterminal *lAndExp1);
};


#endif //SYSY_COMPILER_LOREXP_H
