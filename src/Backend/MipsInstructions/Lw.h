//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_LW_H
#define SYSY_COMPILER_LW_H


#include "MipsInstruction.h"

class Lw : public MipsInstruction {
public:
    int reg0;
    int offset;
    int reg1;
    std::string glob = "";

    std::string translate();

    Lw(int reg0, int offset, int reg1);
};


#endif //SYSY_COMPILER_LW_H
