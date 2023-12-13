//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSBUILDER_H
#define SYSY_COMPILER_MIPSBUILDER_H


#include "MipsModule.h"

class MipsBuilder {
public:
    MipsModule *mipsModule;

//    std::vector<>

    void translate();

    void genMipsData(std::string name, int type, std::string val);

    void genMipsText(std::string name);

    MipsBuilder();

    void genMipsBasicBlock(std::string name);

    void genInstruction(MipsInstruction* Ins);

};


#endif //SYSY_COMPILER_MIPSBUILDER_H
