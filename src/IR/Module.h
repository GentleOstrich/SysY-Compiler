//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_MODULE_H
#define SYSY_COMPILER_MODULE_H
#include <vector>
#include "Values/Function.h"
#include "Values/Instructions/Instruction.h"

class Module {
public:
    std::vector<Function*> functions;
    std::vector<Instruction*> globalVars;
};


#endif //SYSY_COMPILER_MODULE_H
