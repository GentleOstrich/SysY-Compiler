//
// Created by lyh on 11/19/2023.
//

#ifndef SYSY_COMPILER_INSTRUCTION_H
#define SYSY_COMPILER_INSTRUCTION_H

#include "../../User.h"
#include "InstructionType.h"

class BasicBlock;

class Instruction : public User {
public:
    BasicBlock *basicBlock;

    InstructionType instructionType;

    bool isPtr = false;

    std::vector<int> dims;

    Instruction(const std::string &name, ValueType valueType, BasicBlock *basicBlock, InstructionType instructionType);

    void translate() override;

    std::string getName() override;

    void addDim(int dim); // 

    std::string getType() override;

    std::string getContent() override;

};


#endif //SYSY_COMPILER_INSTRUCTION_H
