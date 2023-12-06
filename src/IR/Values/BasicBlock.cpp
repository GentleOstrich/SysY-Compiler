//
// Created by lyh on 11/17/2023.
//

#include "BasicBlock.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

BasicBlock::BasicBlock(const std::string &name, ValueType valueType, Function *function) : Value(name, valueType),
                                                                                           function(function) {}

void BasicBlock::translate() {
    for (auto *child : instructions) {
        child->translate();
        if (((Instruction *) child)->instructionType == InstructionType::Ret ||
            ((Instruction *) child)->instructionType == InstructionType::Br) {
            break;
        }
    }
}

void BasicBlock::addInstruction(Instruction *instruction) {
    this->instructions.push_back(instruction);
}

std::string BasicBlock::getName() {
    return "%" + this->name;
}
