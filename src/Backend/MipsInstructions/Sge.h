//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_SGE_H
#define SYSY_COMPILER_SGE_H


#include "MipsInstruction.h"

class Sge : public MipsInstruction {
public:
    int reg0;
    int reg1;
    int reg2;


    Sge(int reg0, int reg1, int reg2);

    std::string translate() override;

};


#endif //SYSY_COMPILER_SGE_H
