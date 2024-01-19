//
// Created by yh on 2023/10/11.
//

#ifndef SYSY_COMPILER_SYMBOL_H
#define SYSY_COMPILER_SYMBOL_H

#include <unordered_map>
#include <string>
#include <vector>
#include "../Value.h"

class Symbol
{
public:
    std::string word;
    Value* value;

    Symbol(const std::string &word, Value *value);
};

#endif // SYSY_COMPILER_SYMBOL_H
