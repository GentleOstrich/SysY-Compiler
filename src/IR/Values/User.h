//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_USER_H
#define SYSY_COMPILER_USER_H

#include "Value.h"
#include <vector>

class User : public Value {
public:
    std::vector<Value> operands;

    User(const std::string &name, ValueType valueType);
};


#endif //SYSY_COMPILER_USER_H
