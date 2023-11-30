//
// Created by lyh on 11/20/2023.
//

#include "GlobalVar.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

void GlobalVar::translate() {
    std::string code;
    if (this->isConst) {
        code += this->getName() + " = dso_local constant " + getType() + " " + getInit();
    } else {
        code += this->getName() + " = dso_local global " + getType() + " " + getInit();
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
    for (auto dim: dims) {
        code += "[" + std::to_string(dim) + " x ";
    }
    code += "i" + std::to_string(ty);
    for (int i = 0; i < dims.size(); ++i) {
        code += "]";
    }
    return code;
}

std::string GlobalVar::getInit() {
    std::string code;
    if (!operands.empty()) {
        if (dims.empty()) {
            code += "i32 " + operands[0]->value->getName();
        } else {
            if (dims.size() == 1) {
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
            } else if (dims.size() == 2) {
                std::string subType = "[" + std::to_string(dims[1]) + " x " + "i32" + "]";
                code += "[";
                bool checkAllZero = true;
                bool allzero = true;
                for (int i = 0; i < operands.size(); ++i) {
                    if (i % dims[0] == 0) {
                        code += subType + " " + "[";
                        checkAllZero = true;
                        allzero = true;
                    }
                    if (checkAllZero) {
                        for (int j = i; j < i + dims[1]; ++j) {
                            if (operands[j]->value->getName() != "0") {
                                allzero = false;
                                break;
                            }
                        }
                        checkAllZero = false;
                    }
                    if (allzero) {
                        code = code.substr(0, code.size() - 1);
                        code += "zeroinitializer, ";
                        i = i + dims[1] - 1;
                    } else {
                        code += "i32 " + operands[i]->value->getName() + ", ";
                        if ((i + 1) % dims[0] == 0) {
                            code = code.substr(0, code.size() - 2);
                            code += "], ";
                        }
                    }
                }
                code = code.substr(0, code.size() - 2);
                code += "]";
            } else {
                std::cout << "inValid Dim!" << std::endl;
            }
        }
    } else {
        if (dims.empty()) {
            code += "i32 0";
        } else {
            if (dims.size() == 1) {
                code += "zeroinitializer";
            } else if (dims.size() == 2) {
                std::string subType = "[" + std::to_string(dims[1]) + " x " + "i32" + "]";
                code += "[";
                int len = dims[0] * dims[1];
                for (int i = 0; i < len; ++i) {
                    if (i % dims[0] == 0) {
                        code += subType + " ";
                    }
                    code = code.substr(0, code.size() - 1);
                    code += " zeroinitializer, ";
                    i = i + dims[1] - 1;
                }
                code = code.substr(0, code.size() - 2);
                code += "]";
            } else {
                std::cout << "inValid Dim!" << std::endl;
            }
        }
    }
    return code;
}







