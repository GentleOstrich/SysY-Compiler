//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_LI_H
#define SYSY_COMPILER_LI_H


#include "MipsInstruction.h"

class Li : public MipsInstruction {
public:
    int reg;
    int val;

    Li(int reg, int val);

    std::string translate() override;
};


#endif //SYSY_COMPILER_LI_H
