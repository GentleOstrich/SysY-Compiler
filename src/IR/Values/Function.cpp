//
// Created by lyh on 11/17/2023.
//

#include "Function.h"
#include "BasicBlock.h"
#include "Param.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

Function::Function(const std::string &name, ValueType valueType, Module *module, int cnt) : User(name, valueType),
                                                                                            module(module), cnt(cnt) {}

void Function::translate() {
    if (this->name != "getint" && this->name != "putint" && this->name != "putch" && this->name != "putstr") {
        std::string ret;
        if (this->ret == 0) {
            ret = "void";
        } else {
            ret = "i32";
        }
        c_ofs << "define dso_local " + ret + " @" << this->name << "(";
        if (!this->params.empty()) {
            std::string code;
            for (auto *child:this->params) {
                code += std::to_string(child->ty) + " " + child->getName() + " ";
            }
            c_ofs << code;
        }
        c_ofs << ")";
        if (!this->basicBlocks.empty()) {
            c_ofs << "{" << std::endl;
            for (int i = 0; i < basicBlocks.size(); ++i) {
                if (basicBlocks.size() > 1 && basicBlocks[i]->getName() != "%0") {
                    c_ofs << basicBlocks[i]->getName().substr(1, basicBlocks[i]->getName().length()) << ":" << std::endl;
                }
                basicBlocks[i]->translate();
                if (basicBlocks.size() > 1 && i != basicBlocks.size() - 1){
                    c_ofs << std::endl;
                }
            }
            c_ofs << "}" << std::endl;
        } else {
            c_ofs << std::endl;
        }
    }
}

void Function::addBasicBlock(BasicBlock *basicBlock) {
    this->basicBlocks.push_back(basicBlock);
}

int Function::allocReg() {
    int t = r;
    r++;
    return t;
}

std::string Function::getName() {
    return "@" + this->name;
}

int Function::paramPos() {
    int t = opNum;
    opNum++;
    return t;
}

void Function::addParam(Param *param) {
    this->params.push_back(param);
}
