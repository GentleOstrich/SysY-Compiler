//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_SGT_H
#define SYSY_COMPILER_SGT_H


#include "MipsInstruction.h"

class Sgt : public MipsInstruction {
public:
    int reg0;
    int reg1;
    int reg2;

    Sgt(int reg0, int reg1, int reg2);

    std::string translate() override;
};


#endif //SYSY_COMPILER_SGT_H
