//
// Created by lyh on 12/12/2023.
//

#include "Mflo.h"

Mflo::Mflo(int reg0) : reg0(reg0) {}

std::string Mflo::translate() {
    std::string code;

    std::string reg0 = "$" + std::to_string(this->reg0);
    code += "   ";
    code += "mflo " + reg0;
    code += "\n";
    return code;
}
