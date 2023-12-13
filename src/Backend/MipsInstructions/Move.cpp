//
// Created by lyh on 12/13/2023.
//

#include "Move.h"

Move::Move(int reg0, int reg1) : reg0(reg0), reg1(reg1) {}

std::string Move::translate() {
    std::string code;
    code += "   move ";
    std::string reg0 = "$" + std::to_string(this->reg0);
    std::string reg1 = "$" + std::to_string(this->reg1);
    code += reg0 + ", " + reg1;
    code += "\n";
    return code;

}
