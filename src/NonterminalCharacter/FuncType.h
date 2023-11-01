//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCTYPE_H
#define SYSY_COMPILER_FUNCTYPE_H
#include "Nonterminal.h"
#include <string>

class FuncType : Nonterminal{
public:
    std::string word;
    FuncType(std::string word);

};


#endif //SYSY_COMPILER_FUNCTYPE_H
