//
// Created by lyh on 12/11/2023.
//

#include "Sw.h"

std::string Sw::translate() {
    std::string code;
    std::string reg0 = "$" + std::to_string(this->reg0);
    std::string reg1 = "$" + std::to_string(this->reg1);
    code += "   sw " + reg0 + ", ";
    if (!glob.empty()) {
        code += glob.substr(1, glob.size() - 1);
    } else {
        code += std::to_string(this->offset) + "(" + reg1 + ")";
    }
    code += "\n";
    return code;
}

Sw::Sw(int reg0, int offset, int reg1) : reg0(reg0), offset(offset), reg1(reg1) {}
