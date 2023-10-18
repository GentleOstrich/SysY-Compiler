//
// Created by lyh on 10/12/2023.
//

#ifndef SYSY_COMPILER_ERROR_H
#define SYSY_COMPILER_ERROR_H

#include "../SymbolManager/Symbol.h"
#include "../SymbolManager/Func.h"
#include <string>
#include <vector>

class ErrorCheck {
public:
    int bCheck(string word, bool fun);
    int cCheck(string word, bool fun);
    int dCheck(int lineNum, string word, int num);
    int eCheck();
    vector<int> getParamList(string word);
    int getType(string word);
    int getFuncRet(string word);
    int fCheck();
    int gCheck();
    int hCheck(string word);
    int lCheck();
    int mCheck();
};


#endif //SYSY_COMPILER_ERROR_H
