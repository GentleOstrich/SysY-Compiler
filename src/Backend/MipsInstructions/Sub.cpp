//
// Created by lyh on 12/11/2023.
//

#include "Sub.h"


Sub::Sub(int reg0, int reg1, int reg2) : reg0(reg0), reg1(reg1), reg2(reg2) {}

std::string Sub::translate() {
    std::string code;

    code += "   sub ";
    std::string reg0 = "$" + std::to_string(this->reg0);
    std::string reg1 = "$" + std::to_string(this->reg1);
    std::string reg2 = "$" + std::to_string(this->reg2);

    code += reg0 + ", " + reg1 + ", " + reg2;
    code += "\n";

    return code;
}
