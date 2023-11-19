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
    int cnt;

    Function(const std::string &name, ValueType valueType, Module *module, int cnt);
};


#endif //SYSY_COMPILER_FUNCTION_H
