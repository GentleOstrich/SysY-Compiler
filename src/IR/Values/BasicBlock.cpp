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
            return; // 每个基本块的结尾的ret或br之后就不再有指令了
        }
    }
    // 一直没有ret或br的话输出void
    c_ofs << "    " << "ret void" << std::endl;
}

void BasicBlock::addInstruction(Instruction *instruction) {
    this->instructions.push_back(instruction);
}

std::string BasicBlock::getName() {
    return "%" + this->name;
}
