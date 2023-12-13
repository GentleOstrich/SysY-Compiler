//
// Created by lyh on 12/11/2023.
//

#include "MipsBasicBlock.h"

MipsBasicBlock::MipsBasicBlock(const std::string &name) : name(name) {}

std::string MipsBasicBlock::translate() {
    std::string code;
    code += "_L" + this->name.substr(1, this->name.size() - 1) + ":\n";
    for (auto *child : this->mipsInstructions) {
        code += child->translate();
    }
    return code;
}

void MipsBasicBlock::addIns(MipsInstruction *ins) {
    this->mipsInstructions.push_back(ins);
}
