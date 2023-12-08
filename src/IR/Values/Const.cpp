//
// Created by lyh on 11/20/2023.
//

#include "Const.h"

Const::Const(const std::string &name, ValueType valueType, int val) : Value(name, valueType), val(val) {}

std::string Const::getName() {
    // 名字就是常数的值
    return std::to_string(this->val);
}

std::string Const::getType() {
    // 只会是i32或i1
    return "i" + std::to_string(ty);
}
