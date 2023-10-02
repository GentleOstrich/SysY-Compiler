//
// Created by yh on 2023/9/18.
//

#ifndef SYSY_COMPILER_LEXER_H
#define SYSY_COMPILER_LEXER_H

#include <string>
#include <vector>
#include "LexType.h"

#define RESERVEWORDS_NUM 12
#define Token pair<LexType, string>

using namespace std;

class Lexer {
private:
    int curPos = 0;
    string word = "";
    LexType lexType = LexType::NONE;
    int lineNum = 1;
    int number;

    int isReserveWord(const string &word);

public:
    int next();

    LexType nnext();

    LexType nnnext();

    Token getToken();
};


#endif //SYSY_COMPILER_LEXER_H
