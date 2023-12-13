//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_J_H
#define SYSY_COMPILER_J_H


#include "MipsInstruction.h"

class J : public MipsInstruction {
public:
    std::string label;

    std::string translate() override ;

    J(const std::string &label);
};


#endif //SYSY_COMPILER_J_H
