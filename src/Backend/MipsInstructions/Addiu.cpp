//
// Created by lyh on 12/13/2023.
//

#include "Addiu.h"

Addiu::Addiu(int reg0, int reg1, int numm) : reg0(reg0), reg1(reg1), numm(numm) {}

std::string Addiu::translate() {
    std::string code;
    code += "   ";
    code += "addiu ";
    code += "$" + std::to_string(this->reg0) + ", $" + std::to_string(this->reg1) + ", " +  std::to_string(this->numm);
    code += "\n";


    return code;
}
