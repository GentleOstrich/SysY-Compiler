//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_JR_H
#define SYSY_COMPILER_JR_H


#include "MipsInstruction.h"

class Jr : public MipsInstruction {
public:
    int reg = 31;

    std::string translate() override;

    Jr(int reg);

};


#endif //SYSY_COMPILER_JR_H
