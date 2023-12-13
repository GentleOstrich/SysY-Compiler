//
// Created by lyh on 12/11/2023.
//

#include "Li.h"

std::string Li::translate() {
    std::string code;

    std::string reg = "$" + std::to_string(this->reg);

    code += "   li " + reg + ", " + std::to_string(this->val);

    code += "\n";

    return code;
}

Li::Li(int reg, int val) : reg(reg), val(val) {}
