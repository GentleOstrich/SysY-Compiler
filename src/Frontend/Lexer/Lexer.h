//
// Created by yh on 2023/9/18.
//

#ifndef SYSY_COMPILER_LEXER_H
#define SYSY_COMPILER_LEXER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "LexType.h"
#include "Token.h"

#define RESERVEWORDS_NUM 12

class Lexer {
private:
    int curPos = 0;
    std::string word;
    LexType lexType = LexType::NONE;
    int lineNum = 1;
    int lastLineNum = -1;
    int number = 114514;

    static int isReserveWord(const std::string &word);

public:
    int next();

    LexType nnext();

    LexType nnnext();

    Token getToken();

    [[nodiscard]] bool hasAUntilB(char A, char B) const;

    [[nodiscard]] int getLineNum() const;

    [[nodiscard]] int getNumber() const;

    [[nodiscard]] int getLastLineNum() const;
};


#endif //SYSY_COMPILER_LEXER_H
