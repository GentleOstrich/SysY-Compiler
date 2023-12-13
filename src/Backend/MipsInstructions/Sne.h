//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_SNE_H
#define SYSY_COMPILER_SNE_H


#include "MipsInstruction.h"

class Sne: public MipsInstruction {
public:
    int reg0;
    int reg1;
    int reg2;

    Sne(int reg0, int reg1, int reg2);

    std::string translate() override ;
};


#endif //SYSY_COMPILER_SNE_H
