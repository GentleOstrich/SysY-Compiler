//
// Created by lyh on 11/20/2023.
//

#ifndef SYSY_COMPILER_CONST_H
#define SYSY_COMPILER_CONST_H


#include "../Value.h"

class Const : public Value {
public:
    int val;

    Const(const std::string &name, ValueType valueType, int val);

    std::string getName() override ;
};


#endif //SYSY_COMPILER_CONST_H
