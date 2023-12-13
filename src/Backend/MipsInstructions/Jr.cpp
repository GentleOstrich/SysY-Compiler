//
// Created by lyh on 12/13/2023.
//

#include "Jr.h"

std::string Jr::translate() {
    std::string code;
    code += "   jr ";
    code += "$" + std::to_string(this->reg);
    code += "\n";
    return code;
}

Jr::Jr(int reg) : reg(reg) {}
