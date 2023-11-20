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
#include "SymbolManager/SymbolTable.h"
#include "Values/Const.h"
#include <string>
#include <vector>

extern CompUnit *compUnit;

class BuildFactory {
public:
    BuildFactory();

    Module *module;

    BasicBlock *curBasicBlock;

    Function *curFunction;

    Module *genIRModule();

    Function *genFunction(Node *node);

    BasicBlock *genBasicBlock(Node *node, Function *function);

    Instruction *genInstruction(Node *node, InstructionType instructionType, bool needReg);

    Const* genConst(Node *node, int val);

    GlobalVar* genGlobalVar(Node *node, int val, bool isConst);
};

#endif //SYSY_COMPILER_BUILDFACTORY_H
