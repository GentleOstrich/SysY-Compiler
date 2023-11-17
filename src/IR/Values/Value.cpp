//
// Created by lyh on 11/17/2023.
//

#include "Value.h"

Value::Value(const std::string &name, ValueType valueType) : name(name), valueType(valueType) {}

void Value::addUse(Use use) {
    this->useList.push_back(use);
}

