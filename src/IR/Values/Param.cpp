//
// Created by lyh on 11/19/2023.
//

#include <iostream>
#include "Param.h"

Param::Param(const std::string &name, ValueType valueType, int pos) : Value(name, valueType), pos(pos) {}

std::string Param::getName() {
    return "%" + this->name;
}

void Param::addDim(int dim) {
    dims.push_back(dim);
}

std::string Param::getType() {
    std::string code;
    if (dims.empty()) { // 一个数
        code += "i" + std::to_string(ty);
    } else if (dims.size() == 1) { // 一维 a[]
        code += "i" + std::to_string(ty) + "*";
    } else if (dims.size() == 2) { // 二维 a[][2]
        code += "[" + std::to_string(dims[1]) + " x " + "i" + std::to_string(ty) + "]" + "*";
    } else { // 超过二维
        std::cout << "invalid dim" << std::endl;
    }
    return code;
}
