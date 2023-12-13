//
// Created by lyh on 12/12/2023.
//

#include "Mfhi.h"

Mfhi::Mfhi(int reg0) {
    this->reg0 = reg0;
}

std::string Mfhi::translate() {

    std::string code;

    std::string reg0 = "$" + std::to_string(this->reg0);
    code += "   ";
    code += "mfhi " + reg0;
    code += "\n";
    return code;

}
