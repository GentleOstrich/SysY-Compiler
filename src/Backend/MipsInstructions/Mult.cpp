//
// Created by lyh on 12/11/2023.
//

#include "Mult.h"


Mult::Mult(int reg1, int reg2) : reg1(reg1), reg2(reg2) {}

std::string Mult::translate() {
    std::string code;

    code += "   mult ";
    std::string reg1 = "$" + std::to_string(this->reg1);
    std::string reg2 = "$" + std::to_string(this->reg2);

    code += reg1 + ", " + reg2;
    code += "\n";

    return code;
}
