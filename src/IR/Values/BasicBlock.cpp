//
// Created by lyh on 11/17/2023.
//

#include "BasicBlock.h"


BasicBlock::BasicBlock(const std::string &name, ValueType valueType, Function *function) : Value(name, valueType),
                                                                                                 function(function) {}

void BasicBlock::translate() {
    for (auto* child : instructions) {
        child->translate();
    }
}

void BasicBlock::addInstruction(Instruction *instruction) {
    this->instructions.push_back(instruction);
}
