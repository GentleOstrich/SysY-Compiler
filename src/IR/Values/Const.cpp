//
// Created by lyh on 11/20/2023.
//

#include "Const.h"


Const::Const(const std::string &name, ValueType valueType, int val) : Value(name, valueType), val(val) {}

std::string Const::getName() {
    return std::to_string(this->val);
}
