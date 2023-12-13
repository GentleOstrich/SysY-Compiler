//
// Created by lyh on 12/12/2023.
//

#ifndef SYSY_COMPILER_MFHI_H
#define SYSY_COMPILER_MFHI_H


#include "MipsInstruction.h"

class Mfhi : public MipsInstruction {
public:
    int reg0;

    std::string translate();

    Mfhi(int reg0);


};


#endif //SYSY_COMPILER_MFHI_H
