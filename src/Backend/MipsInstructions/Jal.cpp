//
// Created by lyh on 12/13/2023.
//

#include "Jal.h"

std::string Jal::translate() {
    return "   jal " + this->label + "\n";
}

Jal::Jal(const std::string &label) : label(label) {}
