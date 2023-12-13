//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_SYSCALL_H
#define SYSY_COMPILER_SYSCALL_H


#include "MipsInstruction.h"

class Syscall : public MipsInstruction {
public:
    Syscall();
    std::string translate() override ;
};


#endif //SYSY_COMPILER_SYSCALL_H
