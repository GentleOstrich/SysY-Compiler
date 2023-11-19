//
// Created by lyh on 11/19/2023.
//

#include "Instruction.h"

Instruction::Instruction(const std::string &name, ValueType valueType, BasicBlock *basicBlock,
                         InstructionType instructionType) : User(name, valueType), basicBlock(basicBlock),
                                                            instructionType(instructionType) {}
