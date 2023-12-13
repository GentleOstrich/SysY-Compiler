//
// Created by lyh on 12/11/2023.
//

#include "MipsData.h"

std::string MipsData::translate() {
    std::string code;
    code += "   ";
    code += this->name + ": ";
    if (this->type == 0) {
        code += ".word " + this->val;
    } else {
        code += ".asciiz " + this->val;
    }
    code += "\n";
    return code;
}

MipsData::MipsData(const std::string &name, int type, const std::string &val) : name(name), type(type), val(val) {}
