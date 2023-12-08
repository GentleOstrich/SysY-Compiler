//
// Created by lyh on 11/20/2023.
//

#include "GlobalVar.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

void GlobalVar::translate() {
    std::string code;
    if (dims.empty()) {
        if (this->isConst) {
            code += this->getName() + " = dso_local constant " + getInit();
        } else {
            code += this->getName() + " = dso_local global " + getInit();
        }
    } else {
        if (this->isConst) {
            code += this->getName() + " = dso_local constant " + getContent() + " " + getInit();
        } else {
            code += this->getName() + " = dso_local global " + getContent() + " " + getInit();
        }
    }
    c_ofs << code << std::endl;
}


std::string GlobalVar::getName() {
    return "@" + this->name;
}

GlobalVar::GlobalVar(const std::string &name, ValueType valueType, Module *module, bool isConst) : User(name,
                                                                                                        valueType),
                                                                                                   module(module),
                                                                                                   isConst(isConst) {}

void GlobalVar::addDim(int dim) {
    dims.push_back(dim);
}

std::string GlobalVar::getType() {
    std::string code;
    code += getContent();
    code += "*";
    return code;
}

std::string GlobalVar::getInit() {
    std::string code;
    if (!operands.empty()) { // 有初始数字
        if (dims.empty()) { // 没有维度
            code += "i32 " + operands[0]->value->getName();
        } else {
            if (dims.size() == 1) { // 一维
                code += "[";
                bool allzero = true;
                for (auto *use: operands) {
                    code += "i32 " + use->value->getName() + ", ";
                    if (allzero && use->value->getName() != "0") {
                        allzero = false;
                    }
                }
                if (allzero) {
                    code.clear();
                    code += "zeroinitializer";
                } else {
                    code = code.substr(0, code.size() - 2);
                    code += "]";
                }
            } else if (dims.size() == 2) { // 二维 [[3 x i32] [xxx, xxx, xxx], ....]
                std::string subType = "[" + std::to_string(dims[1]) + " x " + "i32" + "]";
                code += "[";
                bool checkAllZero = true; // 需要检查全0
                bool allZero = true; // 是全0
                for (int i = 0; i < operands.size(); ++i) {
                    if (i % dims[1] == 0) {
                        code += subType + " " + "[";
                        checkAllZero = true;
                        allZero = true;
                    }
                    if (checkAllZero) {
                        for (int j = i; j < i + dims[1]; ++j) {
                            if (operands[j]->value->getName() != "0") {
                                allZero = false;
                                break;
                            }
                        }
                        checkAllZero = false;
                    }
                    if (allZero) {
                        code = code.substr(0, code.size() - 1);
                        code += "zeroinitializer, ";
                        i = i + dims[1] - 1;
                    } else {
                        code += "i32 " + operands[i]->value->getName() + ", ";
                        if ((i + 1) % dims[1] == 0) {
                            code = code.substr(0, code.size() - 2);
                            code += "], ";
                        }
                    }
                }
                code = code.substr(0, code.size() - 2);
                code += "]";
            } else { // 维度超过二维
                std::cout << "inValid Dim!" << std::endl;
            }
        }
    } else { // 没有初始数字
        if (dims.empty()) { // 没有维度
            code += "i32 0";
        } else {
            if (dims.size() == 1) { // 一维
                code += "zeroinitializer";
            } else if (dims.size() == 2) { // 二维 [[3 x i32] [xxx, xxx, xxx], ....]
                std::string subType = "[" + std::to_string(dims[1]) + " x " + "i32" + "]"; //
                code += "[";
                int len = dims[0] * dims[1]; // 数字的个数
                for (int i = 0; i < len; ++i) {
                    if (i % dims[1] == 0) {
                        code += subType + " ";
                    }
                    code = code.substr(0, code.size() - 1);
                    code += " zeroinitializer, ";
                    i = i + dims[1] - 1;
                }
                code = code.substr(0, code.size() - 2);
                code += "]";
            } else { // 维度超过二维
                std::cout << "inValid Dim!" << std::endl;
            }
        }
    }
    return code;
}

std::string GlobalVar::getContent() {
    std::string code;
    for (auto dim: dims) {
        if (dim > 0) // 只有在函数里dim会等于0
            code += "[" + std::to_string(dim) + " x ";
    }
    code += "i" + std::to_string(ty);
    for (int dim: dims) {
        if (dim > 0) // 只有在函数里dim会等于0
            code += "]";
    }
    for (auto dim : dims) {
        if (dim == 0) { // 表示存的是指针
            code += "*";
        }
    }
    return code;
}







