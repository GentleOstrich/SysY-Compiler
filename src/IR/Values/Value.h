//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_VALUE_H
#define SYSY_COMPILER_VALUE_H

#include <string>
#include <vector>
#include "../Use.h"
#include "../ValueType.h"

class Value {
public:
    std::string name;
    ValueType valueType;
    std::vector<Use> useList;
    int valNumber = -1;
    Value(const std::string &name, ValueType valueType);
    void addUse(Use use);

};


#endif //SYSY_COMPILER_VALUE_H
