//
// Created by yh on 2023/10/11.
//

#ifndef SYSY_COMPILER_SYMBOL_H
#define SYSY_COMPILER_SYMBOL_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Func.h"

class Symbol
{
public:
    std::string word;
    int type; // 0->a, 1->a[], 2->a[][], -1->func
    bool con; // 1->const, 0->var
    int val;
    int ty = -1;
    bool global = false;
    bool param = false;
    Func *func;
    Symbol(int type, const std::string &word, bool con, Func *func);
};

#endif // SYSY_COMPILER_SYMBOL_H
