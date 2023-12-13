//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_BEQ_H
#define SYSY_COMPILER_BEQ_H


#include "MipsInstruction.h"

class Beq: public MipsInstruction {
public:
    int reg;
    std::string label;

    Beq(int reg, const std::string &label);

    std::string translate();
};


#endif //SYSY_COMPILER_BEQ_H
