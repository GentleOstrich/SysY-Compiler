//
// Created by lyh on 12/12/2023.
//

#include "Beq.h"

Beq::Beq(int reg, const std::string &label) : reg(reg), label(label) {}

std::string Beq::translate() {
    std::string code;

    code += "   beq $zero, ";
    std::string reg = "$" + std::to_string(this->reg);

    std::string label = "_L" + this->label.substr(1, this->label.size() - 1);

    code += reg + ", " + label;

    code += "\n";

    return code;
}
