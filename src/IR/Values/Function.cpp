//
// Created by lyh on 11/17/2023.
//

#include "Function.h"
#include "BasicBlock.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

Function::Function(const std::string &name, ValueType valueType, Module *module, int cnt) : Value(name, valueType),
                                                                                            module(module), cnt(cnt) {}

void Function::translate() {
    c_ofs << "define dso_local i32 @" << this->name << "() {" << std::endl;
    for (auto*child:this->basicBlocks) {
        child->translate();
    }
    c_ofs << "}" << std::endl;
}

void Function::addBasicBlock(BasicBlock *basicBlock) {
    this->basicBlocks.push_back(basicBlock);
}

int Function::allocReg() {
    int t = r;
    r++;
    return t;
}
