//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_VALUE_H
#define SYSY_COMPILER_VALUE_H

#include <string>
#include <vector>
#include <memory>
#include "../ValueType.h"
#include "../Use.h"

class Value {
public:
    std::string name;
    ValueType valueType;
    int valNumber = -1;
    std::vector<std::unique_ptr<Use>> uses;
    Value(std::string name, ValueType valueType);
};


#endif //SYSY_COMPILER_VALUE_H
