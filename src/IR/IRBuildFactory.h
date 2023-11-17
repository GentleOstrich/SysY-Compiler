//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_IRBUILDFACTORY_H
#define SYSY_COMPILER_IRBUILDFACTORY_H


#include "Values/BasicBlock.h"
#include "Values/Function.h"
#include "IRModule.h"
#include <string>


class IRBuildFactory {
public:
    BasicBlock buildBasicBlock(Function parentFunc);
    Function buildFUnction(std::string name, std::string type, IRModule module);


};


#endif //SYSY_COMPILER_IRBUILDFACTORY_H
