//
// Created by lyh on 12/12/2023.
//

#include "J.h"

J::J(const std::string &label) : label(label) {}

std::string J::translate() {

    std::string code;

    code += "   ";
    std::string label = "_L" + this->label.substr(1, this->label.size() - 1);
    code += "j " + label + "\n";

    return code;
}
