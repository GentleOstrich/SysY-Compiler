//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_JAL_H
#define SYSY_COMPILER_JAL_H


#include "MipsInstruction.h"

class Jal : public MipsInstruction{
public:
    std::string label;

    Jal(const std::string &label);

    std::string translate() override ;
};


#endif //SYSY_COMPILER_JAL_H
