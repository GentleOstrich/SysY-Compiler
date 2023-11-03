//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_NUMBER_H
#define SYSY_COMPILER_NUMBER_H

#include "Nonterminal.h"


class Number : Nonterminal {
public:
    int IntConst;
    Number();

    void setIntConst(int intConst);
};


#endif //SYSY_COMPILER_NUMBER_H
