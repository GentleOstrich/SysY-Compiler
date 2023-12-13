//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_ADDIU_H
#define SYSY_COMPILER_ADDIU_H


#include "MipsInstruction.h"

class Addiu : public  MipsInstruction{
public:
    int reg0;
    int reg1;
    int numm;

    Addiu(int reg0, int reg1, int numm);

    std::string translate() override ;
};


#endif //SYSY_COMPILER_ADDIU_H
