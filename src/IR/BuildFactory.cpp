//
// Created by lyh on 11/17/2023.
//

#include "BuildFactory.h"

BuildFactory::BuildFactory() {}

Module *BuildFactory::genIRModule()
{
    Module *module = new Module();
    for (Node *child : compUnit->children)
    {
        if (child->nodeType == NodeType::Decl)
        {
            module->globalVars.push_back(genInstruction(child, nullptr, InstructionType::Alloca));
        }
        else if (child->nodeType == NodeType::FuncDef)
        {
            module->functions.push_back(genFunction(child, module));
        }
        else if (child->nodeType == NodeType::MainFuncDef)
        {
            module->functions.push_back(genFunction(child, module));
        }
    }
    return module;
}

Function *BuildFactory::genFunction(Node *decl, Module *module)
{
    Function *functinon = new Function(decl->getWord(), ValueType::Function, module, 0);

    return functinon;
}

BasicBlock *BuildFactory::genBasicBlock(Node *decl, Function* function)
{
    BasicBlock *basicBlock = new BasicBlock(decl->getWord(), ValueType::BasicBlock, function);

    return basicBlock;
}

Instruction *BuildFactory::genInstruction(Node *node, BasicBlock* basicBlock, InstructionType instructionType) {

    return nullptr;
}


// Function *BuildFactory::genInstruction()
//{
//     return nullptr;
// }
