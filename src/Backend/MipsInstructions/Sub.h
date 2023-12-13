//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_SUB_H
#define SYSY_COMPILER_SUB_H


#include "MipsInstruction.h"

class Sub : public MipsInstruction{
public:
    int reg0;
    int reg1;
    int reg2;

    std::string translate() override ;

    Sub(int reg0, int reg1, int reg2);


};


#endif //SYSY_COMPILER_SUB_H
