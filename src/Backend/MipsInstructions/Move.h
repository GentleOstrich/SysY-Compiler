//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_MOVE_H
#define SYSY_COMPILER_MOVE_H


#include "MipsInstruction.h"

class Move : public MipsInstruction {
public:
    int reg0 = 2;
    int reg1;

    Move(int reg0, int reg1);

    std::string translate() override ;

};


#endif //SYSY_COMPILER_MOVE_H
