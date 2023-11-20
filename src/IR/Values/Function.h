//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_FUNCTION_H
#define SYSY_COMPILER_FUNCTION_H

#include "../Value.h"
class BasicBlock;
class Module;

class Function : public Value {
public:
    Module* module;
    std::vector<BasicBlock*> basicBlocks;
    int cnt; // 参数的数量
    int r = 1; // 临时寄存器号
    Function(const std::string &name, ValueType valueType, Module *module, int cnt);

    void addBasicBlock(BasicBlock* basicBlock);
    int allocReg();
    void translate() override;
};


#endif //SYSY_COMPILER_FUNCTION_H
