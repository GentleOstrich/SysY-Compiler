//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSTEXT_H
#define SYSY_COMPILER_MIPSTEXT_H


#include <string>
#include <vector>
#include "MipsBasicBlock.h"

class MipsText {
public:
    std::string name;

    std::vector<MipsBasicBlock *> mipsBasicBlocks;

    std::string translate();

    MipsText(const std::string &name);

    void addMipsBasicBlock(MipsBasicBlock *mipsBasicBlock);
};


#endif //SYSY_COMPILER_MIPSTEXT_H
