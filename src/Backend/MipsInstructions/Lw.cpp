//
// Created by lyh on 12/11/2023.
//

#include "Lw.h"

std::string Lw::translate() {
    std::string code;
    code += "   lw ";
    std::string reg = "$" + std::to_string(this->reg);
    code += reg + ", ";
    if (!glob.empty()) {
        code += glob.substr(1,glob.size()-1);
    } else {
        code += std::to_string(this->offset) + "($sp)";
    }
    code += "\n";
    return code;
}

Lw::Lw(int reg, int offset) : reg(reg), offset(offset) {}
