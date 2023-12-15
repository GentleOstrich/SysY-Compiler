//
// Created by lyh on 12/11/2023.
//

#include "Lw.h"

std::string Lw::translate() {
    std::string code;
    code += "   lw ";
    std::string reg0 = "$" + std::to_string(this->reg0);
    std::string reg1 = "$" + std::to_string(this->reg1);
    code += reg0 + ", ";
    if (!glob.empty()) {
        code += glob.substr(1, glob.size() - 1);
    } else {
        code += std::to_string(this->offset) + "(" + reg1 + ")";
    }
    code += "\n";
    return code;
}

Lw::Lw(int reg0, int offset, int reg1) : reg0(reg0), offset(offset), reg1(reg1) {}
