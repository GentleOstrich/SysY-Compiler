//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSBASICBLOCK_H
#define SYSY_COMPILER_MIPSBASICBLOCK_H


#include <string>
#include <vector>
#include "MipsInstructions/MipsInstruction.h"

class MipsBasicBlock {
public:
    std::string name;

    std::vector<MipsInstruction *> mipsInstructions;

    MipsBasicBlock(const std::string &name);

    std::string translate();

    void addIns(MipsInstruction *ins);

};


#endif //SYSY_COMPILER_MIPSBASICBLOCK_H
