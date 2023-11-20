//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_VALUE_H
#define SYSY_COMPILER_VALUE_H

#include <string>
#include <vector>
#include "Values/ValueType.h"
#include "Use.h"

class Value {
public:
    std::string name;
    ValueType valueType;
    //int valNumber = -1;
    std::vector<Use*> uses;
    Value(std::string name, ValueType valueType);

    void addUse(Use* use);
    virtual void translate();
    virtual std::string getName();
};


#endif //SYSY_COMPILER_VALUE_H
