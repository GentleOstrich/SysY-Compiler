//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_SW_H
#define SYSY_COMPILER_SW_H


#include "MipsInstruction.h"

class Sw : public MipsInstruction {
public:
    int reg;
    int offset;

    std::string translate() override ;

    std::string glob;

    Sw(int reg, int offset);
};


#endif //SYSY_COMPILER_SW_H
