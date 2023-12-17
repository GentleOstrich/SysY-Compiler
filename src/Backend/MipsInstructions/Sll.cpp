//
// Created by lyh on 2023/12/17.
//

#include "Sll.h"

Sll::Sll(int reg0, int reg1, int num) : reg0(reg0), reg1(reg1), num(num) {}

std::string Sll::translate() {
    std::string code;

    code += "   sll ";
    code += "$" + std::to_string(reg0);
    code += ", ";
    code += "$" + std::to_string(reg1);
    code += ", ";
    code += std::to_string(num);
    code += "\n";

    return code;
}
