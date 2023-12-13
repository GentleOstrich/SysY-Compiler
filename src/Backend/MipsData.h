//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSDATA_H
#define SYSY_COMPILER_MIPSDATA_H


#include <string>

class MipsData {
public:
    std::string name;
    int type; // 0-.word 1-.asciiz
    std::string val;

    std::string translate();

    MipsData(const std::string &name, int type, const std::string &val);

};


#endif //SYSY_COMPILER_MIPSDATA_H
