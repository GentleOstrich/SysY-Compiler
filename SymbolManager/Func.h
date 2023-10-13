//
// Created by lyh on 10/13/2023.
//

#ifndef SYSY_COMPILER_FUNC_H
#define SYSY_COMPILER_FUNC_H

#endif //SYSY_COMPILER_FUNC_H

#include <vector>
#include "Symbol.h"

class Func: Symbol{
public:
    int retype;
    int paraNum;
    vector<int> paramTypeList;
    Func(int id, int type, const string &word, bool con, int retype, int paramNum, int paraNum);
};