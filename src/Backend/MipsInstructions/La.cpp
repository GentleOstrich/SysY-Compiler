//
// Created by lyh on 12/15/2023.
//

#include "La.h"

La::La(int reg, const std::string &name) : reg(reg), name(name) {}

std::string La::translate() {
    std::string code;

    code += "   la ";
    code += "$" + std::to_string(this->reg);
    code += ", ";
    code += name;
    code += "\n";

    return code;
}
