//
// Created by lyh on 11/17/2023.
//

#include "BuildFactory.h"

BuildFactory::BuildFactory() {}

Module *BuildFactory::genIRModule() {
    auto *module = new Module();
    for (Node *child: compUnit->children) {
        if (child->nodeType == NodeType::Decl) {
            module->globalVars.push_back(genInstruction(child, nullptr, InstructionType::Alloca));
        } else if (child->nodeType == NodeType::FuncDef) {
            module->functions.push_back(genFunction(child, module));
        } else if (child->nodeType == NodeType::MainFuncDef) {
            module->functions.push_back(genFunction(child, module));
        }
    }
    return module;
}

Function *BuildFactory::genFunction(Node *node, Module *module) {
    Function *function = new Function(node->getWord(), ValueType::Function, module, 0);

    return function;
}

BasicBlock *BuildFactory::genBasicBlock(Node *node, Function *function) {
    BasicBlock *basicBlock = new BasicBlock(node->getWord(), ValueType::BasicBlock, function);

    return basicBlock;
}

Instruction *BuildFactory::genInstruction(Node *node, BasicBlock *basicBlock, InstructionType instructionType) {
    if (node->nodeType == NodeType::VarDef) {

    }


    return nullptr;
}

