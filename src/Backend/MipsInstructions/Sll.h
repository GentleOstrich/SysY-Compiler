//
// Created by lyh on 2023/12/17.
//

#ifndef SYSY_COMPILER_SLL_H
#define SYSY_COMPILER_SLL_H


#include "MipsInstruction.h"

class Sll : public MipsInstruction {
public:
    int reg0;
    int reg1;
    int num;

    Sll(int reg0, int reg1, int num);

    std::string translate() override;

};


#endif //SYSY_COMPILER_SLL_H
