//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_MODULE_H
#define SYSY_COMPILER_MODULE_H
#include <vector>
#include "Values/Function.h"
#include "Values/Instructions/Instruction.h"
#include "Values/GlobalVar.h"

class Module {
public:
    std::vector<Function*> functions;
    std::vector<GlobalVar*> globalVars;
    void addFunction(Function* function) {
        this->functions.push_back(function);
    }
    void addGlobalVar(GlobalVar* globalVar) {
        this->globalVars.push_back(globalVar);
    }
    void output() {
        for (auto* child : globalVars) {
            child->translate();
        }
        for (auto* child : functions) {
            child->translate();
        }
    }
};


#endif //SYSY_COMPILER_MODULE_H
