//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_BASICBLOCK_H
#define SYSY_COMPILER_BASICBLOCK_H
#include "Value.h"


class BasicBlock : Value {
public:
    std::vector<std::unique_ptr<Value>> instructions;

};


#endif //SYSY_COMPILER_BASICBLOCK_H
