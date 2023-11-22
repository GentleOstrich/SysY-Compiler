//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_BASICBLOCK_H
#define SYSY_COMPILER_BASICBLOCK_H
#include "../Value.h"
#include "Instructions/Instruction.h"
#include "Function.h"

class BasicBlock : public Value {
public:
    std::vector<Instruction*> instructions;

    Function* function;

    BasicBlock(const std::string &name, ValueType valueType, Function *function);

    void addInstruction(Instruction* instruction);

    void translate() override;

    std::string getName() override ;


};


#endif //SYSY_COMPILER_BASICBLOCK_H
