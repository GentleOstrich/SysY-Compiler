//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_BUILDFACTORY_H
#define SYSY_COMPILER_BUILDFACTORY_H

#include "Module.h"
#include "../Frontend/NonterminalCharacter/CompUnit.h"
#include "../Frontend/NonterminalCharacter/Nonterminals.h"
#include "Values/Function.h"
#include "Values/BasicBlock.h"
#include "Values/ValueType.h"
#include <string>
#include <vector>

extern CompUnit *compUnit;

class BuildFactory
{
public:
    int symbolTable = 0;

    BuildFactory();

    Module *genIRModule();

    Function *genFunction(Node* decl, Module* irModule);

    BasicBlock *genBasicBlock(Node *decl, Function* function);

    Instruction *genInstruction(Node* decl, BasicBlock* basicBlock, InstructionType instructionType);
};

#endif //SYSY_COMPILER_BUILDFACTORY_H
