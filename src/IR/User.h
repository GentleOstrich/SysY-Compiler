//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_USER_H
#define SYSY_COMPILER_USER_H

#include "Value.h"
#include <vector>
#include <memory>

class User : public Value {
public:
    int opNum; // 操作数数量

    std::vector<Use*> operands;

    User(const std::string &name, ValueType valueType);

    void addOperand(Use* use);

};


#endif //SYSY_COMPILER_USER_H
