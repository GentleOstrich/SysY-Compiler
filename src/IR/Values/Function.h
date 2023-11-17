//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_FUNCTION_H
#define SYSY_COMPILER_FUNCTION_H

#include "Value.h"
#include "BasicBlock.h"

class Function : Value {
public:
    std::vector<std::unique_ptr<BasicBlock>> basicBlocks;
};


#endif //SYSY_COMPILER_FUNCTION_H
