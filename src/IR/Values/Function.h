//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_FUNCTION_H
#define SYSY_COMPILER_FUNCTION_H

#include "../User.h"
class BasicBlock;
class Module;
class Param;

class Function : public User {
public:
    Module* module;
    std::vector<BasicBlock*> basicBlocks;
    std::vector<Param*> params;
    int cnt = 0; // 参数的数量
    int r = 0; // 临时寄存器号
    int ret = 0; // 0 void 1 int
    Function(const std::string &name, ValueType valueType, Module *module, int cnt);

    void addBasicBlock(BasicBlock* basicBlock);
    void addParam(Param* param);
    int allocReg();
    int paramPos();
    void translate() override;
    std::string getName() override;

};


#endif //SYSY_COMPILER_FUNCTION_H
