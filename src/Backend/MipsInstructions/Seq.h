//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_SEQ_H
#define SYSY_COMPILER_SEQ_H


#include "MipsInstruction.h"

class Seq : public MipsInstruction {
public:
    int reg0;
    int reg1;
    int reg2;

    Seq(int reg0, int reg1, int reg2);

    std::string translate() override ;
};


#endif //SYSY_COMPILER_SEQ_H
