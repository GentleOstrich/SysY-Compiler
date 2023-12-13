//
// Created by lyh on 12/11/2023.
//

#include "MipsText.h"

std::string MipsText::translate() {
    std::string code;
    code += this->name + ":\n";
    for (auto *child : this->mipsBasicBlocks) {
        code += child->translate();
    }
    code += "\n";
    return code;
}

MipsText::MipsText(const std::string &name) : name(name) {}

void MipsText::addMipsBasicBlock(MipsBasicBlock *mipsBasicBlock) {
    this->mipsBasicBlocks.push_back(mipsBasicBlock);
}
