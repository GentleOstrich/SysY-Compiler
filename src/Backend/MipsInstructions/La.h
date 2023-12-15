//
// Created by lyh on 12/15/2023.
//

#ifndef SYSY_COMPILER_LA_H
#define SYSY_COMPILER_LA_H


#include "MipsInstruction.h"

class La : public MipsInstruction {
public:
    int reg;
    std::string name;
    std::string translate() override ;

    La(int reg, const std::string &name);
};


#endif //SYSY_COMPILER_LA_H
