//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_DIV_H
#define SYSY_COMPILER_DIV_H


#include "MipsInstruction.h"

class Div : public MipsInstruction {
public:
    int reg0;
    int reg1;
    int reg2;

    std::string translate() override;

    Div(int reg0, int reg1, int reg2);

};


#endif //SYSY_COMPILER_DIV_H
