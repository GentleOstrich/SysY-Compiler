//
// Created by lyh on 11/17/2023.
//

#include "BuildFactory.h"

BuildFactory::BuildFactory() {
    this->module = new Module();
    this->curBasicBlock = nullptr;
    this->curBasicBlock = nullptr;
}

Module *BuildFactory::genIRModule() {
    return module;
}

Function *BuildFactory::genFunction(Node *node) {
    auto *function = new Function(node->getWord(), ValueType::Function, this->module, 0);
    // 函数的参数数量先设置为0
    this->curFunction = function;
    this->module->addFunction(function);
    this->curBasicBlock = nullptr;
    return function;
}

BasicBlock *BuildFactory::genBasicBlock(Node *node) {
    int reg = curFunction->allocReg();
    auto *basicBlock = new BasicBlock(std::to_string(reg), ValueType::BasicBlock, this->curFunction);
    basicBlock->function = curFunction;
    this->curFunction->addBasicBlock(basicBlock);
    this->curBasicBlock = basicBlock;
    return basicBlock;
}

Instruction *BuildFactory::genInstruction(InstructionType instructionType, bool needReg) {
    int reg = (needReg) ? curFunction->allocReg() : -1;
    auto *instruction = new Instruction(std::to_string(reg), ValueType::Instruction,
                                        this->curBasicBlock, instructionType);
    this->curBasicBlock->addInstruction(instruction);
    return instruction;
}

Const *BuildFactory::genConst(int val) {
    return new Const("", ValueType::Const, val);
}

GlobalVar *BuildFactory::genGlobalVar(Node *node, bool isConst) {
    auto *globalVar = new GlobalVar(node->getWord(), ValueType::Global, this->module, isConst);
    this->module->addGlobalVar(globalVar);
    this->curBasicBlock = nullptr;
    return globalVar;
}

Function *BuildFactory::genFunction(std::string name, int paraNum) {
    // 为了建立库函数
    auto *function = new Function(name, ValueType::Function, this->module, paraNum);
    // 函数的参数数量先设置为0
    this->module->addFunction(function);
    return function;
}

Param *BuildFactory::genParam() {
    auto *param = new Param(std::to_string(curFunction->allocReg()), ValueType::Param, curFunction->paramPos());
    curFunction->addParam(param);
    return param;
}



