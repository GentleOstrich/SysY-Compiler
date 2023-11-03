//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_UNARYOP_H
#define SYSY_COMPILER_UNARYOP_H

#include "Nonterminal.h"


class UnaryOp : Nonterminal {
public:
    char op; // + - !
    UnaryOp();
    void setOp(char op);
};


#endif //SYSY_COMPILER_UNARYOP_H
