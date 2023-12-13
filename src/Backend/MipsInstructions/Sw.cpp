//
// Created by lyh on 12/11/2023.
//

#include "Sw.h"

std::string Sw::translate() {
    std::string code;
    std::string reg = "$" + std::to_string(this->reg);
    code += "   sw " + reg + ", ";
    if (!glob.empty()) {
        code += glob.substr(1, glob.size() - 1);
    } else {
        code += std::to_string(this->offset) + "($sp)";
    }
    code += "\n";
    return code;
}

Sw::Sw(int reg, int offset) : reg(reg), offset(offset) {}
