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
#include "Values/Param.h"
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

    Function *genFunction(std::string name, int paramNum);

    BasicBlock *genBasicBlock();

    Instruction *genInstruction(InstructionType instructionType, bool needReg);

    Const *genConst(int val);

    GlobalVar *genGlobalVar(Node *node, bool isConst);

    Param *genParam();

    void removeIns();
};

#endif //SYSY_COMPILER_BUILDFACTORY_H
