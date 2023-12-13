//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_SLE_H
#define SYSY_COMPILER_SLE_H


#include "MipsInstruction.h"

class Sle : public MipsInstruction {

public:
    int reg0;
    int reg1;
    int reg2;

    Sle(int reg0, int reg1, int reg2);


    std::string translate() override;
};


#endif //SYSY_COMPILER_SLE_H
