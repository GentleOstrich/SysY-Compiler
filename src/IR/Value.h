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
    std::vector<Use*> uses;
    int ty = 32;
    Value(std::string name, ValueType valueType);

    void addUse(Use* use);
    virtual void translate();
    virtual std::string getName();
    virtual std::string getType();
    virtual std::string getInit();
    virtual std::string getContent();
};


#endif //SYSY_COMPILER_VALUE_H
