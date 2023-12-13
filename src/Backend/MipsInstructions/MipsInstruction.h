//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSINSTRUCTION_H
#define SYSY_COMPILER_MIPSINSTRUCTION_H

#include <string>

class MipsInstruction {
public:
    virtual std::string translate();

};


#endif //SYSY_COMPILER_MIPSINSTRUCTION_H
