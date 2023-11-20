//
// Created by lyh on 11/17/2023.
//

#include "BuildFactory.h"

BuildFactory::BuildFactory() {
    this->module = new Module();
}

Module *BuildFactory::genIRModule() {
    return module;
}

Function *BuildFactory::genFunction(Node *node) {
    auto *function = new Function(node->getWord(), ValueType::Function, this->module, 0);
    // 函数的参数数量先设置为0
    this->curFunction = function;
    this->module->addFunction(function);
    curBasicBlock = genBasicBlock(node, curFunction);
    return function;
}

BasicBlock *BuildFactory::genBasicBlock(Node *node, Function *function) {
    auto *basicBlock = new BasicBlock(node->getWord(), ValueType::BasicBlock, this->curFunction);
    this->curFunction->addBasicBlock(basicBlock);
    return basicBlock;
}

Instruction *BuildFactory::genInstruction(Node *node, InstructionType instructionType, bool needReg) {
    int reg = (needReg) ? curFunction->allocReg() : -1;
    auto *instruction = new Instruction(std::to_string(reg), ValueType::Instruction,
                                        this->curBasicBlock, instructionType);
    this->curBasicBlock->addInstruction(instruction);
    return instruction;
    if (instructionType == InstructionType::Alloca) {
        auto *instruction = new Instruction("%" + std::to_string(curFunction->allocReg()), ValueType::Instruction,
                                            this->curBasicBlock, InstructionType::Alloca);
        this->curBasicBlock->addInstruction(instruction);
        return instruction;
    } else if (instructionType == InstructionType::Ret) {
        auto *instruction = new Instruction(node->getWord(), ValueType::Instruction, this->curBasicBlock,
                                            InstructionType::Ret);
        this->curBasicBlock->addInstruction(instruction);
        return instruction;
    } else if (instructionType == InstructionType::Add) {
        auto *instruction = new Instruction("%" + std::to_string(curFunction->allocReg()), ValueType::Instruction,
                                            this->curBasicBlock, InstructionType::Add);
        this->curBasicBlock->addInstruction(instruction);
        return instruction;
    }
    return nullptr;
}

Const *BuildFactory::genConst(Node *node, int val) {
    return new Const("", ValueType::Const, val);
}

GlobalVar *BuildFactory::genGlobalVar(Node *node, int val, bool isConst) {
    auto* globalVar = new GlobalVar(node->getWord(), ValueType::Global, this->module, isConst, val);
    this->module->addGlobalVar(globalVar);
    return globalVar;
}



