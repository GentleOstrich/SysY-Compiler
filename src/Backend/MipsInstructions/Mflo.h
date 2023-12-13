//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_MFLO_H
#define SYSY_COMPILER_MFLO_H


#include "MipsInstruction.h"

class Mflo : public MipsInstruction {
public:
    int reg0;

    std::string translate();

    Mflo(int reg0);

};


#endif //SYSY_COMPILER_MFLO_H
