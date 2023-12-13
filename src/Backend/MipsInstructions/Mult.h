//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MULT_H
#define SYSY_COMPILER_MULT_H


#include "MipsInstruction.h"

class Mult : public MipsInstruction {
public:
    int reg1;
    int reg2;

    std::string translate() override ;

    Mult(int reg1, int reg2);


};


#endif //SYSY_COMPILER_MULT_H
